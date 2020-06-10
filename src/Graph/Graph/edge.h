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

//����
struct Edge{
	int data;//������Ҳ���Լǳ�from
	int to;//����ͼ��ָ��Ľڵ���
	int weight;//Ȩ��
	char edgeType;
	Edge(): edgeType(UNETERMINED){}
	Edge(int t, int w = 1): weight(w), to(t), edgeType(UNETERMINED){}
	//Edge(int f, int t, int w = 1):data(f), to(t), weight(w){}
	void reset(){
		edgeType = UNETERMINED;
	}
	//Ȩ�رȽ���
	bool operator<(Edge const& e){
		return weight < e.weight;
	}
	bool operator==(Edge const& e){
		return weight == e.weight;
	}
};
