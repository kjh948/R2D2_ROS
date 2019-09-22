import requests
from bs4 import BeautifulSoup

# Ref: https://stackoverflow.com/questions/47928608/how-to-use-beautifulsoup-to-parse-google-search-results-in-python
def query(question, max_len=30):
    r = requests.get("https://www.google.com/search?q=" + question)
    html_doc = r.text
    '''
    soup = BeautifulSoup(html_doc, 'html.parser')
    for s in soup.find_all(id="rhs_block"):
        print(s.text.encode('utf-8'))
        print('\n')
    '''
    soup = BeautifulSoup(r.text, 'lxml')
    answer_list = soup.find_all(class_='g')
    for g in answer_list:
        print(g.text)
        print('-----')
    try:
        if len(answer_list[0].text)>max_len:
            return answer_list[0].text[0:max_len-1]
        else:
            return answer_list[0].text
    except:
        return ""

if __name__ == "__main__":
    while 1:
        answer = query(raw_input("What would you like to search: "))
        print('## Final Answer:  ' + answer)