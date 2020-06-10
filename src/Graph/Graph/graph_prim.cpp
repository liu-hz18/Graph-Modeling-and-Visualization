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

#include "minHeap.h"
#include "Graph.h"

//最小支撑树,朴素prim(BFS),O(n^2+e)
int Graph::primBrute(int s, list<Edge>* result){
	assert(0 <= s && s < n);
	reset();
	int sum = 0;
	vertex[s].priority = 0;
	int u = s, shortest;
	for(int i = 0; i < n; i++){
		vertex[u].state = VISITED;
		if(u != s){
			Edge e = Edge(u, shortest); e.data = vertex[u].parent;//(v, u) 
			result->push_back(e);
			sum += shortest;
		}
		for(auto& iter :edgeList[u]){
			int j = iter.to;
			//松弛操作
			if(vertex[j].state == UNDISCOVERED && vertex[j].priority > iter.weight){
				vertex[j].priority = iter.weight;
				vertex[j].parent = u;//为还原树的结构，必须记录parent
			}
		}
		//选出下一个极短跨边
		shortest = INT_MAX;
		for(int j = 0; j < n; j ++){
			if(vertex[j].state == UNDISCOVERED && shortest > vertex[j].priority){
				shortest = vertex[j].priority;
				u = j;
			}
		}
	}
	return sum;
}

//prim() (BFS)堆优化,O((n+e)logn),选择 最短的边 加入树
int Graph::primHeap(int s){
	assert(0 <= s && s < n);
	reset();
	MinHeap<Vertex> H(max(n, e));
	int sum = 0;
	int count = 0;
	vertex[s].priority = 0;
	H.push(vertex[s]);
	//最小支撑树的边 用树边TREE代表
	while(!H.empty()){
		Vertex ver = H.pop();
		int u = ver.data;
		if(vertex[u].state == VISITED)continue;
		vertex[u].state = VISITED;
		if(u != s){
			sum += ver.priority;
			Edge e = Edge(u, ver.priority); e.data = vertex[u].parent;//(v, u)
			treeList.push_back(e);
			count++;
		}
		for(auto& iter : edgeList[u]){
			int j = iter.to;
			if(vertex[j].priority > iter.weight){//松弛
				vertex[j].priority = iter.weight;
				vertex[j].parent = u;//为还原树的结构，必须记录parent
				H.push(vertex[j]);
			}
		}
	}
	printf("[C++]: Nodes: %d, Tree Edge: %d\n", n, count);
	return sum;
}
