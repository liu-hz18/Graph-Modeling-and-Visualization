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
#include <assert.h>
#include <time.h>
#include <stdlib.h>

#include <vector>
#include <stack>
#include <queue>
#include <list>

using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

#ifndef INT_MIN
#define INT_MIN (-INT_MAX - 1)
#endif

#define DEFAULT_CAPACITY 64

#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2

#define UNETERMINED 0
#define TREE 1
#define CROSS 2
#define FORWARD 3
#define BACKWARD 4
