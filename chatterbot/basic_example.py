# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

from chatterbot import ChatBot

# Create a new chat bot named Charlie
chatbot = ChatBot(
    'Charlie',
    trainer='chatterbot.trainers.ListTrainer'
)

chatbot.train([
    "안녕하세요",
    "뽀로로 영화 보고 싶어요",
    "그건 영화로 하고 있는데요",
    "그럼 우리 영화관에 가요",
    "영화 예약이 필요하네요",
    "제가 준비할께요"
])

# Get a response to the input text 'How are you?'
response = chatbot.get_response('영화관에 가요')

print(response)
