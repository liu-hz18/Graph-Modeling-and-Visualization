// 2020年春 软件学院 离散数学大作业

/********************************************************/
// 输入: 图信息，应保证连通。
//		e+1行，第一行为 n(顶点数) e(边数), 
//		接下来e行每行3个int: f t w, 分别代表两个节点和权重
// 输出:
//      edges.js: 边信息和支撑树(Prim)信息，js文件
//		nodes.js: 节点信息和介数中心度、紧密中心度、社区划分
//      paths.js: 任意两点间的最短路径(Floyd)
//	CopyRight: 刘泓尊  计84  2018011446, CST.THU, 2020.6
/********************************************************/

#pragma once

#include "vertex.h"
#include "edge.h"
#include "unionSet.h"
#include "community.h"

//有向图类
class Graph{
private:
	int n, e;//顶点数和边数
	Vertex* vertex;//顶点列表
	list<Edge>* edgeList;//邻接表
	stack<int>** pathlist;//最短路径的二维矩阵套链表
	bool isDirected;
	vector<Edge> treeList;//保存树边
	
	void reset();//重置访问状态
	
	void getPath(int from, int to, int**path, int i, int j);//递归得到from到to 的最短路
	
	void getBetweenCent(int** distMatrix, int** path);//得到介数中心度

	void printPath(int from, int to, int** mat, ofstream& fout);//打印任意两点间最短路径

	int** listToMatrix();//邻接表转邻接矩阵

	reducedNode* initReduceGraph();//初始化信息简化的图

	unionSet* fastUnfolding(double& modu, unsigned seed);//社群发现fastUnfolding算法

public:
	//输入顶点个数 和 是否是有向图
	Graph(int _n, bool directed = true):n(_n), e(0), vertex(new Vertex[_n+1]), edgeList(new list<Edge>[_n+1]), isDirected(directed){
		pathlist = new stack<int>*[n];
		for(int i = 0; i < n; i++){ pathlist[i] = new stack<int>[n]; }//初始化最短路径
		for(int i = 0; i < n; i++){ vertex[i].data = i; }//设置索引
	}
	~Graph(){
		delete[] vertex;
		delete[] edgeList;
		for(int i = 0; i < n; i++){
			delete[] pathlist[i];
		}
		delete[] pathlist;
	}
	
	void insertEdge(int from, int to, int w = 1);//有向图加边，只需要加一个边
	
	bool existEdge(int f, int t);//(f, t)存在边,O(n)

	void printVetex();//打印顶点信息
	
	void printEdge();//打印边信息

	void printSpanningTree(list<Edge>*);//输出最小支撑树的树边

	void randomGraph(int _e, int w_max = 1);//对n个顶点的图随机插入e条正权边, 无重边和自环, 有正整数权重
	
	int primBrute(int s, list<Edge>* result);//最小支撑树,朴素prim,O(n^2+e)
	
	int primHeap(int s);//prim堆优化,O((n+e)logn)
	
	//最小支撑树，并查集版本 kruskal, O(eloge),返回最小支撑树的边集
	int kruskal(list<Edge>& result);

	//朴素dijkstra,正权矩阵, 单源点s最短路,O(n^2+e)
	void dijkstraBrute(int s);
	
	void dijkstraHeap(int s);//dijkstra堆优化,O((n+e)logn)
	
	//无负权回路，求任意两点间最短路,O(n^3),得到介数中心度O(n^3),返回距离矩阵.同时获得介数中心度betCet
	int** floyd(bool print = false);
	
	//边权任意,无负环 单源s最短路, O(e)~O(ne).若存在负环返回false.(可以看作SPFA)基于BFS框架
	bool bellmanFord(int s);

	//获得紧密中心度cloCet,跑n次dijkstra 或 bellmanFord, 默认 没有负权(hasNegEdge = false)
	void getCloseCet(bool hasNegEdge = false);

	void printAllminPath();//打印所有点对之间的最短路

	double communityDetecting(int iter, int threadnum = 4);//社群发现

	bool isTreeEdge(int from, int to);

};