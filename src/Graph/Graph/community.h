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
#include <list>
using std::list;

//社群类
struct Community{
	int sumIn, sumTot;//社群内部的边权和、社群与其他所有社群连线的边权和
	Community(){
		sumIn = sumTot = 0;
	}
};

//简化的边类
struct reducedEdge{
	int weight, to;
	reducedEdge(int t, int w = 0): to(t){
		weight = w;
	}
};

//简化的节点类
struct reducedNode{
	int community;//属于哪个社群
	list<reducedEdge> neighbor; //连接的边
};
