/**********************************************************/
//        2020�괺 ���ѧԺ ��ɢ��ѧ(��)ͼ��������ҵ
// ����: ͼ��Ϣ��Ӧ��֤��ͨ��
//		e+1�У���һ��Ϊ n(������) e(����), 
//		������e��ÿ��3��int: f t w, �ֱ������㡢����Ȩ��(int)
// ���: ��֤��ǰĿ¼����static/js/
//      edges.js: ����Ϣ��֧����(Prim)��Ϣ��js�ļ�
//		nodes.js: �ڵ���Ϣ�ͽ������Ķȡ��������Ķȡ���������
//      paths.js: �������������·��(Floyd)
//	CopyRight: ������  ��84  2018011446, CST.THU, 2020.6
/**********************************************************/

#include <stdio.h>
#include <string.h>
#include "Graph.h"
#include "Timer.h"

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	Graph* G = new Graph(n, /*isDirect =*/ false);//����ͼ
	int f, t, w;
	//�ӱ�
	for(int i = 0; i < m; i++){
		scanf("%d%d%d", &f, &t, &w);
		G->insertEdge(f, t, w);
	}
	//G->randomGraph(m, /*weight_max =*/ 1);//�������ͼ, ���ͼ�����߱�������Ⱥ�������������ʺ���Ϊ��������������Ϊ����
	//G->printEdge();
	{
		Timer timer;
		timer.start();
		// Minimum Spanning Tree
		printf("[C++]: minimum Spanning Tree: %d\n", G->primHeap(/*root =*/ 1-1));
		timer.pause();
		G->printEdge(); //edges.js
		// min Path and Between Centrality
		timer.start();
		G->floyd(/*print =*/ false);//ͬʱ���betCent
		timer.pause();
		G->printAllminPath(); //paths.js
		// closeness Centrality
		timer.start();
		G->getCloseCet(/*hasNegEdge =*/ false);//���closeCet
		timer.pause();
		// communityDetecting
		timer.start();
		G->communityDetecting(/*iter=*/200, /*thread_num=*/12);
		timer.pause();
		G->printVetex(); //nodes.js
		// print time
		printf("[C++]: Time Elasped: %.3f s\n", timer.duration());
	}
	delete G;
	return 0;
}
