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

//获得介数中心度
#include "Graph.h"

//递归得到 from 到 to 的最短路,O(n)
//pathlist[i][j]用栈存储，和递归保持对应
void Graph::getPath(int from, int to, int**path, int i, int j){
	if(path[from][to] == from){
		pathlist[i][j].push(to); pathlist[i][j].push(from); 
		//vertex[from].betweenCentrality ++;//如果介数中心度也算自己的话
		return;
	}
	vertex[path[from][to]].betweenCentrality ++;//介数中心度++;
	//vertex[to].betweenCentrality ++;//如果介数中心度也算自己的话,本句替换上一句
	pathlist[i][j].push(to);
	getPath(from, path[from][to], path, i, j);
}

//得到介数中心度,O(n^2)*O(n) = O(n^3)
void Graph::getBetweenCent(int** distMatrix, int** path){
	for(int i = 0; i < n; i++)vertex[i].betweenCentrality = 0;
	//有向图要遍历所有i,j;
	if(isDirected){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(i != j && distMatrix[i][j] < INT_MAX){//节点之间存在通路
					getPath(i, j, path, i, j);
				}
			}
		}
	}else{//无向图只需要遍历上三角
		for(int i = 0; i < n; i++){
			for(int j = i+1; j < n; j++){
				if(distMatrix[i][j] < INT_MAX){//节点之间存在通路
					getPath(i, j, path, i, j);
				}
			}
		}
	}
	//normalization
	for(int i = 0; i < n; i++){
		vertex[i].betweenCentrality *= (2.0f / ((n-1)*(n-2)));
	}
}
