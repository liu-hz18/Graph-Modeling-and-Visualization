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

//无负权回路，求任意两点间最短路,O(n^3),得到介数中心度O(n^3),返回距离矩阵
int** Graph::floyd(bool print){
	reset();
	int** distMatrix = listToMatrix();//邻接表转邻接矩阵
	//因为任一最短路径的前缀仍为最短路径，所以设置path
	int** path = new int*[n];//道路矩阵，记录最短路径上的终点的前一个点，保证递归得到其前缀
	//初始化
	for(int i = 0; i < n; i++){
		path[i] = new int[n];
		for(int j = 0; j < n; j++)path[i][j] = i;
	}
	//floyd, dp, O(n^3)
	int temp;
	for(int k = 0; k < n; k++){
		for(int u = 0; u < n; u++){
			for(int v = 0; v < n; v++){
				if(distMatrix[u][v] > (temp = add(distMatrix[u][k], distMatrix[k][v]))){//松弛
					distMatrix[u][v] = temp;
					path[u][v] = path[k][v];//记录路径
					if(!isDirected){path[v][u] = path[k][u]; distMatrix[v][u] = temp;}
				}
			}
		}
	}
	//打印结果
	if(print)for(int i = 0; i < n; i++, putchar(10))for(int j = 0; j < n; j++)
		if(distMatrix[i][j] < INT_MAX)printf(" %3d", distMatrix[i][j]);
		else printf("    ");

	//得到介数中心度，同时打印path
	getBetweenCent(distMatrix, path);
	return distMatrix;
}

