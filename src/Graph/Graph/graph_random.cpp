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

#include "util.h"
#include "Graph.h"

//对n个顶点的图随机插入e条正权边, 无重边和自环, 有正整数权重(默认都取1), 只有空图可以调用
void Graph::randomGraph(int _e, int w_max){
	assert(_e > 0 && _e < (n*(n-1))>>1 && e == 0);
	srand(unsigned(time(NULL)));
	while(e < _e){
		int i = dice(n), j = dice(n);
		while(i == j){i = dice(n);j = dice(n);}//i != j
		if(!existEdge(i, j)){	
			insertEdge(i, j, 1 + dice(w_max));
		}
	}
}
