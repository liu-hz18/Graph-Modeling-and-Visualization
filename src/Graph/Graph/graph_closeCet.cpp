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

#include "Graph.h"

//��ý������Ķ�cloCet,��n��dijkstra �� bellmanFord
void Graph::getCloseCet(bool hasNegEdge){
	for(int i = 0; i < n; i++)vertex[i].closeCentrality = -1;
	if(!hasNegEdge){
		for(int i = 0; i < n; i++){
			vertex[i].closeCentrality = 0;//��ʼ��
			dijkstraHeap(i);//ʹ��dijkstra O(n(n+e)logn)
		}
	}else{
		for(int i = 0; i < n; i++){
			vertex[i].closeCentrality = 0;//��ʼ��
			bellmanFord(i);//ʹ��bellmanFord, O(n^2e)
		}
	}
}
