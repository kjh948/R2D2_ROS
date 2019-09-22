#!/usr/bin/env python

import rospy
from std_msgs.msg import String
from std_srvs.srv import *

import cv2
from imutils.video import VideoStream
from imutils.video import FPS
import numpy as np
import imutils
import time

import logging

logging.basicConfig(level=logging.INFO)

min_size = (15,15)
image_scale = 2
haar_scale = 1.2
min_neighbors = 5
haar_flags = 0

class r2d2Vision(object):
    def __init__(self, mode='face', path = 'resources/haarcascade_frontalface_alt2.xml'):
        self.model = cv2.CascadeClassifier(path)
        self.vs = VideoStream(src=0).start()
        #self.vs = cv2.VideoCapture(0)
        # self.vs.set(3, 320)
        # self.vs.set(4, 240)
        time.sleep(2.0)
        self.fps = FPS().start()
        self.isDetected = None

    def detect(self, frame):
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        fx = 0.5
        if fx != 1.0:
            gray = cv2.resize(gray, (0, 0), fx=fx, fy=fx)
        faces = self.model.detectMultiScale(
            gray,
            scaleFactor=1.1,
            minNeighbors=min_neighbors,
            minSize=min_size,
            flags=cv2.cv.CV_HAAR_SCALE_IMAGE
        )
        if faces is not None:
            for (x, y, w, h) in faces:
                sc = int(1/fx)
                cv2.rectangle(frame, (sc*x, sc*y), (sc*(x + w), sc*(y + h)), (0, 255, 0), 2)
        cv2.imshow("video", frame)
        self.fps.update()
        return faces

    def process(self, delay=0):
        t = cv2.getTickCount()
        time.sleep(delay)
        frame = self.vs.read()
        ret = self.detect(frame)
        return ret

    def loop(self, msg=None, delay=0):
        while 1:
            ret = self.process(delay)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break
            if len(ret)>0:
                self.isDetected = ret
                msg.put(ret)
            else:
                self.isDetected = None
                msg.put(None)

faceCmd = 'stop'

def faceCmdCallback(data):
    global faceCmd
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    faceCmd = data.data
    print faceCmd

if __name__ == "__main__":
    vis = r2d2Vision()

    rospy.init_node('visionFace')
    pub = rospy.Publisher('face', String)

    rospy.Subscriber("faceCmd", String, faceCmdCallback)

    rate = rospy.Rate(2)

    while not rospy.is_shutdown():
        if faceCmd == 'stop':
            continue
        ret = vis.process()
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        if len(ret) != 0:
            pub.publish('detected')
            rospy.loginfo('detected')
        rate.sleep()
    vis.fps.stop()
    print("[INFO] elapsed time: {:.2f}".format(vis.fps.elapsed()))
    print("[INFO] approx. FPS: {:.2f}".format(vis.fps.fps()))

    # do a bit of cleanup
    #cv2.destroyAllWindows()
    #vis.vs.stop()
'''
rostopic ho face
rqt_graph
rostopic b /faceCmd std_msgs/String 'start'
'''
