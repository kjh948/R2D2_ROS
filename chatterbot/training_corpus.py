# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

from chatterbot import ChatBot
import logging
from chatterbot.response_selection import get_random_response
import ext_corpus as ec
import smi2corpus

# Enable info level logging
logging.basicConfig(level=logging.INFO)

#corpus_list = ec.csv2list()
#corpus_list.append(smi2corpus.smi2list())

'''
corpus_list = smi2corpus.smi2list()

chatbot = ChatBot(
    'Example Bot',
    trainer='chatterbot.trainers.ListTrainer',
    response_selection_method=get_random_response,

)

# Start by training our bot with the ChatterBot corpus data
chatbot.train(
    corpus_list
)
while True:
    query = raw_input("Tell me : ")
    response = chatbot.get_response(query)
    print("Bot: " + response.text)
    #print(response)

'''
'''
This is an example showing how to train a chat bot using the
ChatterBot Corpus of conversation dialog.
'''
chatbot = ChatBot(
    'Example Bot',
    trainer='chatterbot.trainers.ChatterBotCorpusTrainer',
    #tie_breaking_method="random_response"
    response_selection_method=get_random_response

)

# Start by training our bot with the ChatterBot corpus data
chatbot.train(
    './corpus/'
)
while True:
    query = raw_input("Tell me : ")
    response = chatbot.get_response(query)
    print("Bot: " + response.text)
    #print(response)
