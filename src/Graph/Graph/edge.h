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
#include "macro.h"

//边类
struct Edge{
	int data;//数据域，也可以记成from
	int to;//有向图中指向的节点编号
	int weight;//权重
	char edgeType;
	Edge(): edgeType(UNETERMINED){}
	Edge(int t, int w = 1): weight(w), to(t), edgeType(UNETERMINED){}
	//Edge(int f, int t, int w = 1):data(f), to(t), weight(w){}
	void reset(){
		edgeType = UNETERMINED;
	}
	//权重比较器
	bool operator<(Edge const& e){
		return weight < e.weight;
	}
	bool operator==(Edge const& e){
		return weight == e.weight;
	}
};
