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
#include <list>
using std::list;

//��Ⱥ��
struct Community{
	int sumIn, sumTot;//��Ⱥ�ڲ��ı�Ȩ�͡���Ⱥ������������Ⱥ���ߵı�Ȩ��
	Community(){
		sumIn = sumTot = 0;
	}
};

//�򻯵ı���
struct reducedEdge{
	int weight, to;
	reducedEdge(int t, int w = 0): to(t){
		weight = w;
	}
};

//�򻯵Ľڵ���
struct reducedNode{
	int community;//�����ĸ���Ⱥ
	list<reducedEdge> neighbor; //���ӵı�
};
