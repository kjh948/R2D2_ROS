# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf-8')


import csv
def csv2list(csv_file='corpus/pororo.csv'):
    corpus_list = []
    with open(csv_file, 'rt') as csvfile:
        utt = csv.reader(csvfile, delimiter=',')
        for row in utt:
            print row[2].encode('utf-8')
            entry = row[2].encode('utf-8').replace('.','').replace('|','').replace('!','').replace('?','')
            corpus_list.append(entry)
    return corpus_list
if __name__ == "__main__":
    csv_file = 'corpus/pororo.csv'
    corpus_list = csv2list(csv_file)
    #print corpus_list[0]
    #print corpus_list[1]
    print('total number of entry: '+str(len(corpus_list)))