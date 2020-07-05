
from .utils import read_csv_to_dict_list
from .graph_utils import stat


def load_movie(name, max_number=500, trans=False):
    info_dict_list = read_csv_to_dict_list('./data/豆瓣电影/movies.csv', parse_movie_line, max_number, trans)
    mat, size = stat(info_dict_list, corr_of_2movies, max_number=max_number, name=name)
    return mat, size, info_dict_list


def parse_movie_line(line_dict, trans=False):
    a_dict = {
        'name': line_dict['影片'].strip(),
        'director': line_dict['导演'].strip().split(';'),
        'writer': line_dict['编剧'].strip().split(';'),
        'actor': line_dict['主演'].strip().split(';'),
        'type': line_dict['类型'].strip().split(';'),
        'region': line_dict['国家/地区'].strip(),
        'language': line_dict['语言'].strip(),
        'date': line_dict['上映日期'].strip(),
    }
    return a_dict


def corr_of_2movies(movie_a, movie_b):
    comm_director = len(set(movie_a['director']) & set(movie_b['director'])) if movie_a['director'] != [''] else 0
    comm_writer = len(set(movie_a['writer']) & set(movie_b['writer'])) if movie_a['writer'] != [''] else 0
    comm_actor = len(set(movie_a['actor']) & set(movie_b['actor'])) if movie_a['actor'] != [''] else 0
    corr = 10 * comm_director + 5 * comm_writer + 1 * comm_actor
    if corr > 0:
        corr = 200 // corr
    return int(corr)


def tojsline_movie(adict, part):
    s = "\t{id: " + str(adict['id']) + ", betCent: " + str(adict['betCent']) +\
        ", closeCent: " + str(adict['closeCent']) + ", community: " + \
        str(part[adict['id']]) + ", visited: 0, name: \"" + adict['name'] \
        + "\", director: \"" + ", ".join(adict['director'])+ "\", writer: \"" +\
        ", ".join(adict['writer']) + "\", actor: \"" + ", ".join(adict['actor'])\
        + "\", type: \"" + ", ".join(adict['type'])+ "\", region: \"" +\
        adict['region'] + "\", language: \"" + adict['language'] + "\", date: \""\
        + adict['date'] + "\"},\n"
    return s