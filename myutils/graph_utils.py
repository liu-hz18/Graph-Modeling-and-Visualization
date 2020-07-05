
import matplotlib.pyplot as plt
import numpy as np
import networkx as nx
import community


def stat(info_dict_list, corr, name, max_number=500):
    print("[Python]: Buliding Graph...")
    movie_num = min(max_number, len(info_dict_list))
    Adj_mat = np.zeros((movie_num, movie_num))
    for i in range(movie_num):
        for j in range(i+1, movie_num):
            Adj_mat[i][j] = Adj_mat[j][i] =\
                corr(info_dict_list[i], info_dict_list[j])
    # display_mat(Adj_mat, name)
    return Adj_mat, movie_num


def plot_degree(G, name):
    degree = nx.degree_histogram(G)
    # print("[Python]: ", degree)
    x = np.arange(len(degree))
    plt.figure()
    plt.bar(x, degree, color='r')
    plt.xlabel('节点度数')
    plt.ylabel('节点数量')
    plt.savefig('pictures/' + name + "_degree.pdf", format="pdf")


def plot_close(G, name):
    closeness_centrality = nx.closeness_centrality(G).values()
    # print("[Python]: ", closeness_centrality)
    x = np.arange(len(closeness_centrality))
    plt.figure()
    plt.bar(x, closeness_centrality, color='r')
    plt.xlabel('节点编号')
    plt.ylabel('紧密中心度')
    plt.savefig('pictures/' + name + "_closeness.pdf", format="pdf")


def plot_bet(G, name):
    betweenness_centrality = nx.betweenness_centrality(G).values()
    # print("[Python]: ", betweenness_centrality)
    x = np.arange(len(betweenness_centrality))
    plt.figure()
    plt.bar(x, betweenness_centrality, color='r')
    plt.xlabel('节点编号')
    plt.ylabel('介数中心度')
    plt.savefig('pictures/' + name + "_betweeness.pdf", format="pdf")


def display_graph(G, name):
    # print("[Python]: ", G.number_of_edges(), G.number_of_nodes())
    part = community.best_partition(G)
    values = [part.get(node) for node in G.nodes()]
    # mod = community.modularity(part, G)
    # print("[Python]: ", part, mod)  # 0.70257
    plt.figure()
    nx.draw_spring(
        G, cmap=plt.get_cmap('jet'), node_color=values, node_size=20,
        with_labels=False, edge_color='gray', alpha=0.5)
    plt.savefig('pictures/' + name + "_graph.pdf", format="pdf")
    plot_degree(G, name)
    plot_bet(G, name)
    plot_close(G, name)


def save_graph(G, file):
    nodes, edges = G.number_of_nodes(), G.number_of_edges()
    with open(file, 'w', encoding='utf-8') as f:
        f.write(str(nodes) + ' ' + str(edges) + '\n')
        for edge in G.edges():
            f.write(str(edge[0]) + ' ' + str(edge[1]) + ' ' + \
                    str(int(G[edge[0]][edge[1]]['weight'])) + '\n')


def build_graph(mat, name, max_number=500, stat=False):
    mat = mat[0:max_number, 0:max_number]
    G = nx.from_numpy_matrix(mat)
    # connect
    sub_graph = G.subgraph(max(nx.connected_components(G), key=len))
    node_set = sub_graph.nodes()
    G = nx.convert_node_labels_to_integers(sub_graph)
    save_graph(G, 'graph.txt')
    mat = nx.to_numpy_matrix(G)
    part = community.best_partition(G)
    if stat:
        display_graph(G, name)
    return G, mat, node_set, part


def display_mat(Adj_mat, name):
    # print("[Python]: ", np.max(Adj_mat), np.min(Adj_mat), np.count_nonzero(Adj_mat))
    plt.figure()
    plt.matshow(Adj_mat)
    plt.savefig('pictures/' + name + "_adjmat.pdf", format="pdf")
