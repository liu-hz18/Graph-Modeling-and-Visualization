
import matplotlib.pyplot as plt
import numpy as np
import networkx as nx
import community  # pip install python-louvain
from .utils import max_number


def stat(info_dict_list, corr):
    print("[Python]: Buliding Graph...")
    movie_num = min(max_number, len(info_dict_list))
    print('[Python]: node num: %d' % movie_num)
    Adj_mat = np.zeros((movie_num, movie_num))
    for i in range(movie_num):
        for j in range(i+1, movie_num):
            Adj_mat[i][j] = Adj_mat[j][i] =\
                corr(info_dict_list[i], info_dict_list[j])
    # display_mat(Adj_mat)
    return Adj_mat, movie_num


def plot_degree(G):
    degree = nx.degree_histogram(G)
    print("[Python]: ", degree)
    x = np.arange(len(degree))
    plt.bar(x, degree, color='r')
    plt.show()


def plot_close(G):
    closeness_centrality = nx.closeness_centrality(G).values()
    print("[Python]: ", closeness_centrality)
    x = np.arange(len(closeness_centrality))
    plt.bar(x, closeness_centrality, color='r')
    plt.show()


def plot_bet(G):
    betweenness_centrality = nx.betweenness_centrality(G).values()
    print("[Python]: ", betweenness_centrality)
    x = np.arange(len(betweenness_centrality))
    plt.bar(x, betweenness_centrality, color='r')
    plt.show()


def display_graph(G):
    print("[Python]: ", G.number_of_edges(), G.number_of_nodes())
    part = community.best_partition(G)
    mod = community.modularity(part, G)
    values = [part.get(node) for node in G.nodes()]
    print("[Python]: ", part, mod)  # 0.70257
    nx.draw_spring(G, cmap=plt.get_cmap('jet'), node_color=values, node_size=20, with_labels=False, edge_color='gray', alpha=0.5)
    plt.show()
    plot_degree(G)
    plot_bet(G)
    plot_close(G)


def save_graph(G, file):
    nodes, edges = G.number_of_nodes(), G.number_of_edges()
    with open(file, 'w', encoding='utf-8') as f:
        f.write(str(nodes) + ' ' + str(edges) + '\n')
        for edge in G.edges():
            f.write(str(edge[0]) + ' ' + str(edge[1]) + ' ' + \
                str(int(G[edge[0]][edge[1]]['weight'])) + '\n')


def build_graph(mat, size):
    mat = mat[0:max_number, 0:max_number]
    G = nx.from_numpy_matrix(mat)
    # connect
    sub_graph = G.subgraph(max(nx.connected_components(G), key=len))
    node_set = sub_graph.nodes()
    G = nx.convert_node_labels_to_integers(sub_graph)
    save_graph(G, 'graph.txt')
    mat = nx.to_numpy_matrix(G)
    part = community.best_partition(G)
    # display_graph(G)
    return G, mat, node_set, part


def display_mat(Adj_mat):
    print("[Python]: ", np.max(Adj_mat), np.min(Adj_mat), np.count_nonzero(Adj_mat))
    plt.matshow(Adj_mat)
    plt.show()
