# encoding=utf-8
import os
import shutil
import argparse

from myutils import (
    save_info_list, rewrite_nodejs,
    tojsline_paper, load_paper,
    tojsline_movie, load_movie,
    build_graph, display_graph,
)


js_prefix = 'static/js/'
program_path = 'bin\\graph.exe'


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--n', type=int, default=500, help='number of nodes to build graph')
    parser.add_argument('--t', action='store_true', help='enable translation (en->ch), this needs network connection and may take much time')
    parser.add_argument('--s', action='store_true', help='show quantitative information of statistical graph')
    return parser.parse_args()


def run_program(program, file_name='graph.txt'):
    print("[Python]: Running C++ Algorithm Lib...")
    if 0 != os.system(program + " < " + file_name):
        print('[Python]: run ' + program + ' failed!')


def clear_file(name):
    shutil.move(js_prefix + 'edges.js', js_prefix + '%s/edges.js' % name)
    shutil.move(js_prefix + 'paths.js', js_prefix + '%s/paths.js' % name)
    shutil.move(js_prefix + 'nodes.js', js_prefix + '%s/nodes.js' % name)
    shutil.move('./graph.txt', js_prefix + '%s/graph.txt' % name)


def run_all(name, load_func, js_func, max_number, translate=False, stat=False):
    print('[Python]: Running on data: %s...' % name.upper())
    mat, size, info_dict_list = load_func(name, max_number, translate)
    G, _, nodes, part = build_graph(mat, name, max_number, stat)
    save_info_list(nodes, info_dict_list, js_prefix + 'nodes.txt')
    run_program(program_path)
    clear_file(name)
    rewrite_nodejs(js_prefix + 'nodes.txt', js_prefix + '%s/nodes.js' % name,
                   js_func, js_prefix + '%s/info_nodes.js' % name, part)
    print('-' * 30)


if __name__ == '__main__':
    import matplotlib.pyplot as plt
    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.rcParams['axes.unicode_minus'] = False
    opt = parse_args()
    run_all(name='movie', load_func=load_movie, js_func=tojsline_movie, max_number=opt.n, stat=opt.s)
    run_all(name='paper', load_func=load_paper, js_func=tojsline_paper, max_number=opt.n, translate=opt.t, stat=opt.s)
