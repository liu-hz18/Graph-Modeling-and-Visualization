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

//顶点类
struct Vertex{
	int data;//数据域
	int dTime, fTime;
	int inDegree, outDegree;
	int priority;//优先级数
	int parent;//遍历树中的父亲
	char state;//访问状态
	float betweenCentrality, closeCentrality;//介数中心度 和 紧密中心度
	int topoIndex;//拓扑排序的rank
	int earStartTime, latStartTime;//最早启动时间和最晚启动时间
	int community;//属于的社群
	Vertex():inDegree(0), outDegree(0), state(UNDISCOVERED), 
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX),
		betweenCentrality(0.0), closeCentrality(0.0), topoIndex(-1), community(-1){}
	void reset(){
		dTime = fTime = parent = topoIndex = -1;
		state = UNDISCOVERED;
		priority = INT_MAX;
	}
	//优先级比较器
	bool operator<(Vertex const& v){
		return priority < v.priority;
	}
	bool operator==(Vertex const& v){
		return priority == v.priority;
	}
};
