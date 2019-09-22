# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

import yaml
import io
from googletrans import Translator
import corpus
import os

translator = Translator()
corpus = corpus.Corpus()
    
file_name='/home/kjh948/chatterbot/chatterbot-corpus/chatterbot_corpus/data/english/ai.yml'
file_name2='ai_ko.yml'


dotted_path='/home/kjh948/workspace/chatterbot/chatterbot-corpus/chatterbot_corpus/data/english/'
list_corpus_files = corpus.list_corpus_files( dotted_path)

for yml_file in list_corpus_files:

    with io.open(yml_file, encoding='utf-8') as data_file:
        src = yaml.load(data_file)
    
    print('loading '+yml_file)
    for x in range(0,len(src['conversations'])):
        print(str(x) + ' in '+ str(len(src['conversations'])))
        for t in range(0,len(src['conversations'][x])):
            try:
                umt = translator.translate(src['conversations'][x][t],'ko').text
                print(src['conversations'][x][t],' -> ', umt)
                src['conversations'][x][t] = umt
            except:
                pass

    yml_file_out = yml_file.replace('english','korean')
    print('writing ' + yml_file_out)
    with io.open(yml_file_out, 'w', encoding='utf-8') as data_file2:
        yaml.dump(src,data_file2,allow_unicode=True)

