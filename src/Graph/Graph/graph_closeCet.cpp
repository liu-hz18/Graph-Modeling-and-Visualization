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

#include "Graph.h"

//获得紧密中心度cloCet,跑n次dijkstra 或 bellmanFord
void Graph::getCloseCet(bool hasNegEdge){
	for(int i = 0; i < n; i++)vertex[i].closeCentrality = -1;
	if(!hasNegEdge){
		for(int i = 0; i < n; i++){
			vertex[i].closeCentrality = 0;//初始化
			dijkstraHeap(i);//使用dijkstra O(n(n+e)logn)
		}
	}else{
		for(int i = 0; i < n; i++){
			vertex[i].closeCentrality = 0;//初始化
			bellmanFord(i);//使用bellmanFord, O(n^2e)
		}
	}
}
