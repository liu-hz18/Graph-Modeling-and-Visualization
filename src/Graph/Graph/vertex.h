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

#pragma once
#include "macro.h"

//������
struct Vertex{
	int data;//������
	int dTime, fTime;
	int inDegree, outDegree;
	int priority;//���ȼ���
	int parent;//�������еĸ���
	char state;//����״̬
	float betweenCentrality, closeCentrality;//�������Ķ� �� �������Ķ�
	int topoIndex;//���������rank
	int earStartTime, latStartTime;//��������ʱ�����������ʱ��
	int community;//���ڵ���Ⱥ
	Vertex():inDegree(0), outDegree(0), state(UNDISCOVERED), 
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX),
		betweenCentrality(0.0), closeCentrality(0.0), topoIndex(-1), community(-1){}
	void reset(){
		dTime = fTime = parent = topoIndex = -1;
		state = UNDISCOVERED;
		priority = INT_MAX;
	}
	//���ȼ��Ƚ���
	bool operator<(Vertex const& v){
		return priority < v.priority;
	}
	bool operator==(Vertex const& v){
		return priority == v.priority;
	}
};
