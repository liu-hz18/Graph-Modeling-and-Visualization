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

int min(int& a, int& b);
int max(int& a, int& b);
int add(int a, int b);
//生成0-n随机数
int dice(int n);
int dice(int lo, int hi);
void swap(int& a, int& b);

inline int min(int& a, int& b){return a > b ? b : a;}
inline int max(int& a, int& b){return a > b ? a : b;}
inline int add(int a, int b){return (a == INT_MAX || b == INT_MAX) ? INT_MAX : (a + b);}
//生成0-n随机数
inline int dice(int n){return rand() % n;}
inline int dice(int lo, int hi){return lo + rand() % (hi - lo);}
inline void swap(int& a, int& b){int temp = a; a = b; b = temp;}

namespace util{
	template<typename T>
	inline void swap(T&a, T&b){T temp = a; a = b; b = temp;}
}

