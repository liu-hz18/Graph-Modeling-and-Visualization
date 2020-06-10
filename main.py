# encoding=utf-8
from collections import OrderedDict
import os
import shutil

from myutils.utils import save_info_list, rewrite_nodejs
from myutils.paper_utils import tojsline_paper, load_paper
from myutils.movie_utils import tojsline_movie, load_movie
from myutils.graph_utils import build_graph, display_graph

js_prefix = 'static/js/'
program_path = 'bin\\graph.exe'


def run_program(program, file_name='graph.txt'):
    print("[Python]: Running C++ Algorithm Program...")
    if 0 != os.system(program + " < " + file_name):
        print('[Python]: run ' + program + ' failed!')


def clear_file(name):
    shutil.move(js_prefix + 'edges.js', js_prefix + '%s/edges.js' % name)
    shutil.move(js_prefix + 'paths.js', js_prefix + '%s/paths.js' % name)
    shutil.move(js_prefix + 'nodes.js', js_prefix + '%s/nodes.js' % name)


def run_all(name, load_func, js_func):
    print('[Python]: Running on data: %s...' % name)
    mat, size, info_dict_list = load_func()
    G, _, nodes, part = build_graph(mat, size)
    # display_graph(G)
    save_info_list(nodes, info_dict_list, js_prefix + 'nodes.txt')
    run_program(program_path)
    clear_file(name)
    rewrite_nodejs(js_prefix + 'nodes.txt', js_prefix + '%s/nodes.js' % name,
                   js_func, js_prefix + '%s/info_nodes.js' % name, part)
    print('-----------------------------')


if __name__ == '__main__':
    run_all(name='movie', load_func=load_movie, js_func=tojsline_movie)
    run_all(name='paper', load_func=load_paper, js_func=tojsline_paper)
