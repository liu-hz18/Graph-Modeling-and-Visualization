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

//边权任意,无负环,单源s最短路, O(e)~O(ne).若存在负环返回false.(设置了inqueue, 可以看作SPFA)基于BFS框架
bool Graph::bellmanFord(int s){
	assert(0 <= s && s < n);
	reset();
	queue<int> Q;
	bool* inqueue = new bool[n];
	memset(inqueue, false, n * sizeof(bool));
	vertex[s].priority = 0;//priority存放其他所有节点到源点的最短距离
	Q.push(s); inqueue[s] = true;
	//bfs
	while(!Q.empty()){
		int v = Q.front(); Q.pop(); inqueue[v] = false;
		for(auto& iter :edgeList[v]){
			int u = iter.to;
			if(vertex[u].priority > add(vertex[v].priority, iter.weight)){//松弛
				vertex[u].priority = vertex[v].priority + iter.weight;
				if(!inqueue[u]){ Q.push(u); inqueue[u] = true; }
			}
		}
	}
	//得到源点s的紧密中心度
	for(int i = 0; i < n; i++){
		if(i != s && vertex[i].priority < INT_MAX)
			vertex[s].closeCentrality += vertex[i].priority;
	}
	delete[] inqueue;
	return true;
}
