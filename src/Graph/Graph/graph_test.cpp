/**********************************************************/
//        2020年春 软件学院 离散数学(二)图分析大作业
// 输入: 图信息，应保证连通。
//		e+1行，第一行为 n(顶点数) e(边数), 
//		接下来e行每行3个int: f t w, 分别代表出点、入点和权重(int)
// 输出: 保证当前目录下有static/js/
//      edges.js: 边信息和支撑树(Prim)信息，js文件
//		nodes.js: 节点信息和介数中心度、紧密中心度、社区划分
//      paths.js: 任意两点间的最短路径(Floyd)
//	CopyRight: 刘泓尊  计84  2018011446, CST.THU, 2020.6
/**********************************************************/

#include <stdio.h>
#include <string.h>
#include "Graph.h"
#include "Timer.h"

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	Graph* G = new Graph(n, /*isDirect =*/ false);//无向图
	int f, t, w;
	//加边
	for(int i = 0; i < m; i++){
		scanf("%d%d%d", &f, &t, &w);
		G->insertEdge(f, t, w);
	}
	//G->randomGraph(m, /*weight_max =*/ 1);//生成随机图, 随机图并不具备鲜明的群体性特征，不适合作为输入样例，仅作为测试
	//G->printEdge();
	{
		Timer timer;
		timer.start();
		// Minimum Spanning Tree
		printf("[C++]: minimum Spanning Tree: %d\n", G->primHeap(/*root =*/ 1-1));
		timer.pause();
		G->printEdge(); //edges.js
		// min Path and Between Centrality
		timer.start();
		G->floyd(/*print =*/ false);//同时获得betCent
		timer.pause();
		G->printAllminPath(); //paths.js
		// closeness Centrality
		timer.start();
		G->getCloseCet(/*hasNegEdge =*/ false);//获得closeCet
		timer.pause();
		// communityDetecting
		timer.start();
		G->communityDetecting(/*iter=*/200, /*thread_num=*/12);
		timer.pause();
		G->printVetex(); //nodes.js
		// print time
		printf("[C++]: Time Elasped: %.3f s\n", timer.duration());
	}
	delete G;
	return 0;
}
