// 2020�괺 ���ѧԺ ��ɢ��ѧ����ҵ

/********************************************************/
// ����: ͼ��Ϣ��Ӧ��֤��ͨ��
//		e+1�У���һ��Ϊ n(������) e(����), 
//		������e��ÿ��3��int: f t w, �ֱ���������ڵ��Ȩ��
// ���:
//      edges.js: ����Ϣ��֧����(Prim)��Ϣ��js�ļ�
//		nodes.js: �ڵ���Ϣ�ͽ������Ķȡ��������Ķȡ���������
//      paths.js: �������������·��(Floyd)
//	CopyRight: ������  ��84  2018011446, CST.THU, 2020.6
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
