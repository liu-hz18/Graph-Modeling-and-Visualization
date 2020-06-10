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

#include "util.h"
#include "Graph.h"

//��n�������ͼ�������e����Ȩ��, ���رߺ��Ի�, ��������Ȩ��(Ĭ�϶�ȡ1), ֻ�п�ͼ���Ե���
void Graph::randomGraph(int _e, int w_max){
	assert(_e > 0 && _e < (n*(n-1))>>1 && e == 0);
	srand(unsigned(time(NULL)));
	while(e < _e){
		int i = dice(n), j = dice(n);
		while(i == j){i = dice(n);j = dice(n);}//i != j
		if(!existEdge(i, j)){	
			insertEdge(i, j, 1 + dice(w_max));
		}
	}
}
