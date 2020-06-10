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
#include "util.h"

//并查集
class unionSet{
	int n;
	int* parent;
	int* size;
	bool* singled;

public:
	unionSet(int _n):n(_n), parent(new int[n]), size(new int[n]), singled(new bool[n]){
	    for(int i = 0; i < n; i++)parent[i] = i;//i本身就在自己的集合内
		memset(size, 1, n * sizeof(int));
		memset(singled, 1, n * sizeof(bool));
	}
	~unionSet(){
		delete[] parent;
		delete[] size;
	}
	void reset(){
		for(int i = 0; i < n; i++)parent[i] = i;
	}
	//查找，路径压缩
	int find(int x){
		return (x == parent[x]) ? x : (parent[x] = find(parent[x]));
	}
	//合并两个集合
	void Union(int x, int y){
		x = find(x);
		y = find(y);
		if(x == y)return;
		if(size[x] > size[y])swap(x, y);
		parent[x] = y;
		size[y] += size[x];
		singled[x] = singled[y] = false;
	}
	void isolate(int x){//使某点从集合中孤立出来O(n)
		if(singled[x])return;
		int i = 0;
		for(; i < n; i++){//找到x的一个孩子
			if(parent[i] == x && i != x)break;
		}
		if(i == n || x == i)return;
		parent[i] = (parent[x] == x) ? i : parent[x];
		for(int j = i+1; j < n; j++){//重连接
			if(parent[j] == x)parent[j] = i;
		}
		parent[x] = x;//孤立
	}
};
