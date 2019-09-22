# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

from chatterbot import ChatBot
import yaml
import io

file_name='./corpus/ai.yml'
file_name2='./corpus/ai2.yml'
with io.open(file_name, encoding='utf-8') as data_file:
    ai = yaml.load(data_file)

with io.open(file_name2, 'w', encoding='utf-8') as data_file2:
    yaml.dump(ai,data_file2,allow_unicode=True)

