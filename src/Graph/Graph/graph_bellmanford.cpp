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

//��Ȩ����,�޸���,��Դs���·, O(e)~O(ne).�����ڸ�������false.(������inqueue, ���Կ���SPFA)����BFS���
bool Graph::bellmanFord(int s){
	assert(0 <= s && s < n);
	reset();
	queue<int> Q;
	bool* inqueue = new bool[n];
	memset(inqueue, false, n * sizeof(bool));
	vertex[s].priority = 0;//priority����������нڵ㵽Դ�����̾���
	Q.push(s); inqueue[s] = true;
	//bfs
	while(!Q.empty()){
		int v = Q.front(); Q.pop(); inqueue[v] = false;
		for(auto& iter :edgeList[v]){
			int u = iter.to;
			if(vertex[u].priority > add(vertex[v].priority, iter.weight)){//�ɳ�
				vertex[u].priority = vertex[v].priority + iter.weight;
				if(!inqueue[u]){ Q.push(u); inqueue[u] = true; }
			}
		}
	}
	//�õ�Դ��s�Ľ������Ķ�
	for(int i = 0; i < n; i++){
		if(i != s && vertex[i].priority < INT_MAX)
			vertex[s].closeCentrality += vertex[i].priority;
	}
	delete[] inqueue;
	return true;
}
