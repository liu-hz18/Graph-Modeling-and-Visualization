
import requests
import demjson
import difflib
import csv
import random
from tqdm import tqdm


def translate(word):
    # 有道词典 api
    url = 'http://fanyi.youdao.com/translate?smartresult=dict&smartresult=rule&smartresult=ugc&sessionFrom=null'
    # 传输的参数，其中 i 为需要翻译的内容
    key = {
        'from': 'EN',
        'TO': 'ZH',
        'i': word,
        "doctype": "json",
        "version": "2.1",
        "keyfrom": "fanyi.web",
        "ue": "UTF-8",
        "action": "FY_BY_REALTIME",
        "typoResult": "false"
    }
    # key 这个字典为发送给有道词典服务器的内容
    response = requests.post(url, data=key)
    # 判断服务器是否相应成功
    try:
        if response.status_code == 200:
            # 然后相应的结果
            result = demjson.decode(response.text)['translateResult'][0][0]['tgt']
            # print(result)
            return result
        else:
            # print("error!")
            return "暂无"  # 相应失败就返回空
    except:
        return "暂无"


def corr_of_2string(str1, str2):
    return difflib.SequenceMatcher(None, str1, str2).quick_ratio()


def read_csv_to_dict_list(csv_file, parseline, max_number=500, trans=False):
    print("[Python]: Reading csv file...")
    with open(csv_file, 'r', newline='', errors='ignore') as f:
        csvinfo = csv.DictReader(f)
        info_dict_list = [parseline(dict(row), trans) for i, row in tqdm(enumerate(csvinfo), desc='[Python]') if i < max_number]
    info_dict_list = sorted(info_dict_list, key=lambda v: random.random())
    return info_dict_list


def save_info_list(node_set, info_dict_list, file):
    with open(file, 'w', encoding='utf-8') as f:
        for node in node_set:
            f.write(str(info_dict_list[node]) + '\n')


def rewrite_nodejs(info_file, jsfile, tojsline, tojsfile, part):
    print("[Python]: Writing js file...")
    with open(info_file, 'r', encoding='utf-8') as f:
        info_list = [demjson.decode(line.strip()) for line in f.readlines()]
    with open(jsfile, 'r', encoding='utf-8') as f:
        movies = [demjson.decode(line.strip().strip(',')) for line in f.readlines()[1:-1]]
    alist = [dict(id_dict, **info_list[id_dict['id']]) for id_dict in movies]
    # print(alist)
    with open(tojsfile, 'w', encoding='utf-8') as f:
        f.write("var nodes = [\n")
        for adict in alist:
            f.write(tojsline(adict, part))
        f.write("];\n")