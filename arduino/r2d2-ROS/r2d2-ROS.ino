#if (ARDUINO >= 100)
    #include <Arduino.h>
#else
    #include <WProgram.h>
#endif

#include "ros.h"
#include "ros/time.h"
//header file for publishing velocities for odom
#include "lino_msgs/Velocities.h"
//header file for cmd_subscribing to "cmd_vel"
#include "geometry_msgs/Twist.h"
//header file for pid server
#include "lino_msgs/PID.h"
//header file for imu
#include "lino_msgs/Imu.h"

#include "std_msgs/String.h"



#include "lino_base_config.h"
//#include "Motor.h"
//#include "Kinematics.h"
#include "PID.h"
#include "Imu.h"

#include "motor.h"
#include "piezo.h"
#include "dome.h"
#include "led.h"
#include "ps2x.h"
#include "knock.h"


#define IMU_PUBLISH_RATE 10 //hz
#define VEL_PUBLISH_RATE 10 //hz
#define COMMAND_RATE 30 //hz
#define DEBUG_RATE 5

float g_req_linear_vel_x = 0;
float g_req_linear_vel_y = 0;
float g_req_angular_vel_z = 0;

float g_motor_scale = 100;

unsigned long g_prev_command_time = 0;

//callback function prototypes
void commandCallback(const geometry_msgs::Twist& cmd_msg);
void PIDCallback(const lino_msgs::PID& pid);

ros::NodeHandle nh;

ros::Subscriber<geometry_msgs::Twist> cmd_sub("cmd_vel", commandCallback);
ros::Subscriber<lino_msgs::PID> pid_sub("pid", PIDCallback);

ros::Subscriber<std_msgs::String> cmd_sub("cmd_io", commandIOCallback);



lino_msgs::Imu raw_imu_msg;
ros::Publisher raw_imu_pub("raw_imu", &raw_imu_msg);

lino_msgs::Velocities raw_vel_msg;
ros::Publisher raw_vel_pub("raw_vel", &raw_vel_msg);


lino_msgs::Imu raw_imu_msg;
ros::Publisher raw_imu_pub("raw_imu", &raw_imu_msg);



void setup()
{
    //Serial.begin(115200);
    //Serial.print("LINOBASE INIT\n");

    
    //steering_servo.attach(STEERING_PIN);
    //steering_servo.write(90);


      initMotors();
  initPiezo();
  initDome();
  initLed();
  initPS2X();

    nh.initNode();
    nh.getHardware()->setBaud(57600);
    nh.subscribe(pid_sub);
    nh.subscribe(cmd_sub);
    nh.advertise(raw_imu_pub);

    while (!nh.connected())
    {
        nh.spinOnce();
    }
    nh.loginfo("LINOBASE CONNECTED");
    
    //Serial.print("LINOBASE CONNECTED\n");
    
    delay(1);
}

void loop()
{
    static unsigned long prev_control_time = 0;
    static unsigned long publish_vel_time = 0;
    static unsigned long prev_imu_time = 0;
    static unsigned long prev_debug_time = 0;
    static bool imu_is_initialized;

    //this block drives the robot based on defined rate
    if ((millis() - prev_control_time) >= (1000 / COMMAND_RATE))
    {
        moveBase();
        prev_control_time = millis();
    }

    //this block stops the motor when no command is received
    if ((millis() - g_prev_command_time) >= 400)
    {
        stopBase();
    }

    //this block publishes velocity based on defined rate
    if ((millis() - publish_vel_time) >= (1000 / VEL_PUBLISH_RATE))
    {
        //nh.loginfo("Vel published");
        publishVelocities();
        publish_vel_time = millis();
    }

    //this block publishes the IMU data based on defined rate
    if ((millis() - prev_imu_time) >= (1000 / IMU_PUBLISH_RATE))
    {
        //sanity check if the IMU is connected
        if (!imu_is_initialized)
        {
            imu_is_initialized = initIMU();

            if(imu_is_initialized)
                nh.loginfo("IMU Initialized");
            else
                nh.logfatal("IMU failed to initialize. Check your IMU connection.");
        }
        else
        {
            publishIMU();
            //nh.loginfo("IMU Published");
        }
        prev_imu_time = millis();
    }

    //this block displays the encoder readings. change DEBUG to 0 if you don't want to display
    if(DEBUG)
    {
        if ((millis() - prev_debug_time) >= (1000 / DEBUG_RATE))
        {
            printDebug();
            prev_debug_time = millis();
            //Serial.print("DEBUG\n");
        }
    }
    //call all the callbacks waiting to be called
    nh.spinOnce();
}

void PIDCallback(const lino_msgs::PID& pid)
{
    //callback function every time PID constants are received from lino_pid for tuning
    //this callback receives pid object where P,I, and D constants are stored
    //motor1_pid.updateConstants(pid.p, pid.i, pid.d);
    //motor2_pid.updateConstants(pid.p, pid.i, pid.d);
    //motor3_pid.updateConstants(pid.p, pid.i, pid.d);
    //motor4_pid.updateConstants(pid.p, pid.i, pid.d);
}

void commandCallback(const geometry_msgs::Twist& cmd_msg)
{
    //callback function every time linear and angular speed is received from 'cmd_vel' topic
    //this callback function receives cmd_msg object where linear and angular speed are stored
    g_req_linear_vel_x = cmd_msg.linear.x;
    g_req_linear_vel_y = cmd_msg.linear.y;
    g_req_angular_vel_z = cmd_msg.angular.z;

    g_prev_command_time = millis();
}

void commandIOCallback(const std_msgs::String& cmd_msg)
{
  if(cmd_msg.data=="HEAD:3") domeSetPosHome(3);
  if(cmd_msg.data=="HEAD:0") domeSetPosHome(0);
  if(cmd_msg.data=="HEAD:-3") domeSetPosHome(-3);
  
}



void moveBase()
{
  float vel_l = g_motor_scale * (g_req_linear_vel_x - g_req_angular_vel_z);
  float vel_r = g_motor_scale * (g_req_linear_vel_x + g_req_angular_vel_z);
  motorL.setSpeed(vel_l);
  motorR.setSpeed(vel_r);
}

void stopBase()
{
    g_req_linear_vel_x = 0;
    g_req_linear_vel_y = 0;
    g_req_angular_vel_z = 0;
}

void publishVelocities()
{
  float vel_l = g_motor_scale * (g_req_linear_vel_x - g_req_angular_vel_z);
  float vel_r = g_motor_scale * (g_req_linear_vel_x + g_req_angular_vel_z);
  //pass velocities to publisher object
  raw_vel_msg.linear_x = (vel_l+vel_r)/2.0;
  raw_vel_msg.linear_y = 0.;
  raw_vel_msg.angular_z = (-vel_l+vel_r)/2.0;

  //publish raw_vel_msg object to ROS
  raw_vel_pub.publish(&raw_vel_msg);
}

void publishIMU()
{
    //pass accelerometer data to imu object
    raw_imu_msg.linear_acceleration = readAccelerometer();    

    //pass gyroscope data to imu object
    raw_imu_msg.angular_velocity = readGyroscope();

    //pass accelerometer data to imu object
    raw_imu_msg.magnetic_field = readMagnetometer();

    //publish raw_imu_msg object to ROS
    raw_imu_pub.publish(&raw_imu_msg);
}

float mapFloat(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void printDebug()
{
    /*char buffer[50];

    sprintf (buffer, "Encoder FrontLeft  : %ld", motor1_encoder.read());
    nh.loginfo(buffer);
    sprintf (buffer, "Encoder FrontRight : %ld", motor2_encoder.read());
    nh.loginfo(buffer);*/
}
