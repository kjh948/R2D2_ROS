# -*- coding: utf-8 -*-
from __future__ import print_function
import sys
reload(sys)
sys.setdefaultencoding('utf-8')


from samitizer import Smi

def smi2list(csv_file='corpus/frozen.smi'):
    smi = Smi(csv_file)
    plain_text = smi.convert('plain', lang='KRCC').replace('.', '').replace(',', '').replace('!', '')
    corpus_list = plain_text.split('\n')

    return corpus_list
if __name__ == "__main__":
    corpus = smi2list()
    print('total discouse: ', str(len(corpus)))

    try:
        print(corpus[500])
        print(corpus[501])
        print(corpus[502])
    except:
        pass