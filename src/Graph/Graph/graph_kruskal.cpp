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

#include "unionSet.h"
#include "Graph.h"

//用于qsort的compare
int compare(const void* x, const void* y){
	return (*(Edge*)x).weight - (*(Edge*)y).weight;
}

//最小支撑树，并查集版本 kruskal, O(eloge),返回最小支撑树的边集
int Graph::kruskal(list<Edge>& result){
	reset();
	//构建边表
	Edge* edge = new Edge[e];
	unionSet set(n);
	int count = 0, sum = 0;
	//有向图遍历方式，无向图在邻接表中边数为2e，所以只需要存一半
	for(int i = 0; i < n; i++){
		for(auto& iter : edgeList[i]){
			if(!isDirected && iter.to <= i)continue;//保证无向图每个边只存一次
			edge[count].data = i;
			edge[count].to = iter.to;
			edge[count].weight = iter.weight;
			count++;
		}
	}
	//从小到大 排序
	qsort(edge, e, sizeof(Edge), compare);
	//kruskal
	for(int i = 0; i < e; i++){
		int u = edge[i].data;
		int v = edge[i].to;
		if(set.find(u) != set.find(v)){
			set.Union(u, v); //O(1)
			vertex[v].parent = u;
			result.push_back(edge[i]);
			sum += edge[i].weight;
		}
	}
	delete[] edge;
	return sum;
}
