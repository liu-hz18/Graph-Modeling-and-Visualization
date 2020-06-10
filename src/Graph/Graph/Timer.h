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

#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
using namespace std::chrono;

class Timer {
	steady_clock::time_point begin;
	bool is_running;
	double time_elasped;

public:
	Timer() :is_running(false), time_elasped(0.0) {
	}
	void start() {
		begin = system_clock::now();
		is_running = true;
	}
	double duration() const {
		return time_elasped + std::chrono::duration<double>(steady_clock::now() - begin).count();
	}
	void pause() {
		if (is_running){
			time_elasped += std::chrono::duration<double>(steady_clock::now() - begin).count();
			is_running = false;
		}
	}
};
#endif
