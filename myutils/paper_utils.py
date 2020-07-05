
from .utils import translate, read_csv_to_dict_list
from .graph_utils import stat


def load_paper(name, max_number=500, trans=False):
    info_dict_list = read_csv_to_dict_list('./data/论文/papers.csv', parse_paper_line, max_number, trans)
    mat, size = stat(info_dict_list, corr_of_2papers, max_number=max_number, name=name)
    return mat, size, info_dict_list


def parse_paper_line(line_dict, trans=False):
    a_dict = {
        'conference': line_dict['Conference'].strip(),
        'year': line_dict['Year'].strip(),
        'title': line_dict['Paper Title'].strip(),
        'chinese': translate(line_dict['Paper Title'].strip()) if trans else '暂无',
        'link': line_dict['Link'].strip(),
        'abstract': line_dict['Abstract'].strip().replace("\"", "'").replace("\n", "").replace("\r", ""),
        'author': line_dict['Author Names'].strip(),
        'keywords': line_dict['Author Keywords'].replace("\n", "").strip().lower().split(','),
    }
    return a_dict


def corr_of_2papers(paper_a, paper_b):
    corr = 0
    for keys_a in paper_a['keywords']:
        for keys_b in paper_b['keywords']:
            if keys_a == keys_b and len(keys_a) > 12:
                corr += 1
    if corr > 0:
        corr = 50 // corr
    return int(corr)


def tojsline_paper(adict, part):
    s = "\t{id: " + str(adict['id']) + ", betCent: " + str(adict['betCent']) +\
        ", closeCent: " + str(adict['closeCent']) + ", community: " + \
        str(part[adict['id']]) + ", visited: 0, title: \"" + adict['title'] \
        + "\", link: \"" + adict['link'] + "\", author: \"" +\
        adict['author'] + "\", keywords: \"" + ", ".join(adict['keywords'])\
        + "\", year: \"" + adict['year'] + "\", conference: \"" +\
        adict['conference'] + "\", abstract: \"" + adict['abstract'] +\
        "\", chinese: \"" + adict['chinese'] + "\"},\n"
    return s
