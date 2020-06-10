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

#include "vertex.h"
#include "edge.h"
#include "unionSet.h"
#include "community.h"

//����ͼ��
class Graph{
private:
	int n, e;//�������ͱ���
	Vertex* vertex;//�����б�
	list<Edge>* edgeList;//�ڽӱ�
	stack<int>** pathlist;//���·���Ķ�ά����������
	bool isDirected;
	vector<Edge> treeList;//��������
	
	void reset();//���÷���״̬
	
	void getPath(int from, int to, int**path, int i, int j);//�ݹ�õ�from��to �����·
	
	void getBetweenCent(int** distMatrix, int** path);//�õ��������Ķ�

	void printPath(int from, int to, int** mat, ofstream& fout);//��ӡ������������·��

	int** listToMatrix();//�ڽӱ�ת�ڽӾ���

	reducedNode* initReduceGraph();//��ʼ����Ϣ�򻯵�ͼ

	unionSet* fastUnfolding(double& modu, unsigned seed);//��Ⱥ����fastUnfolding�㷨

public:
	//���붥����� �� �Ƿ�������ͼ
	Graph(int _n, bool directed = true):n(_n), e(0), vertex(new Vertex[_n+1]), edgeList(new list<Edge>[_n+1]), isDirected(directed){
		pathlist = new stack<int>*[n];
		for(int i = 0; i < n; i++){ pathlist[i] = new stack<int>[n]; }//��ʼ�����·��
		for(int i = 0; i < n; i++){ vertex[i].data = i; }//��������
	}
	~Graph(){
		delete[] vertex;
		delete[] edgeList;
		for(int i = 0; i < n; i++){
			delete[] pathlist[i];
		}
		delete[] pathlist;
	}
	
	void insertEdge(int from, int to, int w = 1);//����ͼ�ӱߣ�ֻ��Ҫ��һ����
	
	bool existEdge(int f, int t);//(f, t)���ڱ�,O(n)

	void printVetex();//��ӡ������Ϣ
	
	void printEdge();//��ӡ����Ϣ

	void printSpanningTree(list<Edge>*);//�����С֧����������

	void randomGraph(int _e, int w_max = 1);//��n�������ͼ�������e����Ȩ��, ���رߺ��Ի�, ��������Ȩ��
	
	int primBrute(int s, list<Edge>* result);//��С֧����,����prim,O(n^2+e)
	
	int primHeap(int s);//prim���Ż�,O((n+e)logn)
	
	//��С֧���������鼯�汾 kruskal, O(eloge),������С֧�����ı߼�
	int kruskal(list<Edge>& result);

	//����dijkstra,��Ȩ����, ��Դ��s���·,O(n^2+e)
	void dijkstraBrute(int s);
	
	void dijkstraHeap(int s);//dijkstra���Ż�,O((n+e)logn)
	
	//�޸�Ȩ��·����������������·,O(n^3),�õ��������Ķ�O(n^3),���ؾ������.ͬʱ��ý������Ķ�betCet
	int** floyd(bool print = false);
	
	//��Ȩ����,�޸��� ��Դs���·, O(e)~O(ne).�����ڸ�������false.(���Կ���SPFA)����BFS���
	bool bellmanFord(int s);

	//��ý������Ķ�cloCet,��n��dijkstra �� bellmanFord, Ĭ�� û�и�Ȩ(hasNegEdge = false)
	void getCloseCet(bool hasNegEdge = false);

	void printAllminPath();//��ӡ���е��֮������·

	double communityDetecting(int iter, int threadnum = 4);//��Ⱥ����

	bool isTreeEdge(int from, int to);

};