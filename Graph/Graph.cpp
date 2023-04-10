#include "Graph.h"
#include<iostream>
#include <iomanip>
#include<math.h>
#include<vector>
using  namespace  std;

Graph::Graph()
{
	// Intialize things that needs to be initialized.
	//��ʼ��
	v = "";
	w = "";
}
Graph::~Graph()
{
	// Deallocate all dynamic memory you have allocated
	//�ͷŶ�̬�ڴ�
}
void Graph::addVertex(std::string v)
{
	// Adds a vertex(����) to the Graph.
	vertex.push_back(v);
	v_isVisited.push_back(false);
	d_shortest.push_back(INT_MAX);
	pre.push_back(-1);

}

void  Graph::initialize() {
	v_size = vertex.size();
	//�Բ�ֱ������������֮����о��븳ֵ
	for (int i = 0; i < v_size; i++) {
		for (int j = 0; j < v_size; j++) {
			if ((i != j) && (matrix[i][j] == 0))
				matrix[i][j] = INT_MAX;
		}
	}

}

void Graph::addEdge(std::string v, std::string w, int weight)
{
	int  start = 0;
	int  end = 0;
	v_size = vertex.size();
	matrix.resize(v_size, vector<int>(v_size));
	// Adds an edge(��) to the Graph. 
	start = vToIndex(v);
	end = vToIndex(w);
	matrix[start][end] = weight;
	matrix[end][start] = weight;
}

int Graph::vToIndex(string  v) {
	//��ĳ������ĸ��ʾ�ĵ����Ϊ������
	int  index = 0;
	for (int i = 0; i < v_size; i++) {
		if (vertex[i] == v)
			index = i;
	}
	return  index;

}


void  Graph::showGraph() {
	/*matrix.size() : ���ؾ������������ vector �����а����� vector ��������
		matrix[0].size() : ���ؾ�����������������һ���а�����Ԫ��������
		matrix.empty() : �жϾ����Ƿ�Ϊ�ա�*/
	if (matrix.empty() == true)
		cout << "the matrix is empty" << endl;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			if (matrix[i][j] == INT_MAX) {
				cout << "  int";
			}
			else {
				cout << setw(5) << matrix[i][j];
			}

		}
		cout << endl;
	}
}

void  Graph::showInfo() {
	cout << "v_Visited:" << endl;
	for (int i = 0; i < v_size; i++) {
		cout << v_isVisited[i] << " ";
	}
	cout << endl;
	cout << "d_shortest:" << endl;
	for (int i = 0; i < v_size; i++) {
		if (d_shortest[i] == INT_MAX)
			cout << "INT  ";
		else
			cout << d_shortest[i] << " ";
	}
	cout << endl;
	cout << "pre:" << endl;
	for (int i = 0; i < v_size; i++) {
		cout << pre[i] << " ";
	}
	cout << endl;
}





int Graph::shortestPath(std::string v, std::string w)
{
	// Performs Dijkstra's algorithm and identifies the shortest path between v and w.
	// Should also store the actual path (i.e. passed nodes/vertices) in a class variable 
	// so that it can be fetched later with getShortestPath().
	// Returns path cost.
	this->v = v;
	this->w = w;
	if ((ifHaveV(v) == false) || (ifHaveV(w) == false)) {
		cout << "The vector are not in this graph." << endl;
		cout << "Please check your input." << endl;
		return  -1;
	}
	else {
		v_isVisited[vToIndex(v)] = true;
		d_shortest[vToIndex(v)] = 0;
		for (int i = 0; i < v_size; i++) {
			d_shortest[i] = matrix[vToIndex(v)][i];
			if (matrix[vToIndex(v)][i] != INT_MAX) {
				pre[i] = vToIndex(v);
			}
		}
		pre[vToIndex(v)] = -1;
		/*cout << "��Դ����в�����Ľ����" << endl;
		showInfo();*/
		int  min = INT_MAX;
		int  min_index = v_size;

		for (int x = 0; x < v_size - 1; x++) {
			for (int i = 0; i < v_size; i++) {
				//����ѭ�����еĵ㣬�����ҵ���ûȷ�����·������dist��С�Ķ���v1
				//��min����ʾ��̾��룬��min_index����ʾv1������
				if (v_isVisited[i] == true)
					continue;
				else {
					if (d_shortest[i] < min)
					{
						min = d_shortest[i];
						min_index = i;
					}
					//cout << "test  min:" << min << "   min_index:" << min_index << endl;
				}

			}
			//cout << "ѭ����  min:" << min << "   min_index:" << min_index << endl;
			v_isVisited[min_index] = true;
			//��������ڽ���v1�ıߣ�����v1���ڽӶ���
			for (int j = 0; j < v_size; j++) {
				if (v_isVisited[j] == false && ((min + matrix[min_index][j]) < d_shortest[j]) && (matrix[min_index][j] != INT_MAX)) {
					d_shortest[j] = min + matrix[min_index][j];
					pre[j] = min_index;
					//cout << "test" << d_shortest[j] << "  test" << pre[j] << endl;
				}
			}
			min = INT_MAX;
			min_index = v_size;
		}
		//�������֮�����̾���
		int   w_index = vToIndex(w);
		int  shortest_dis = d_shortest[w_index];
		return  shortest_dis;
	}



}

int  Graph::findPre(int index) {
	return  pre[index];
}

std::string Graph::getShortestPath()
{
	// Returns the actual path stored in the class variable from shortestPath(...)
	//����pre���ҵ��յ��Ӧ�����·��
	int  index = vToIndex(w);
	string  path = "";
	vector<int> stack;
	while (index != -1) {
		stack.push_back(index);
		index = findPre(index);

	}

	while (stack.empty() != true) {
		path += vertex[stack.back()] + " , ";
		stack.pop_back();

	}

	return  path;
}
void Graph::readGraphFromFile(std::string pathToFile)
{
	std::ifstream in;
	in.open(pathToFile);
	std::string type = "", v = "", w = "";
	int weight = 0;

	while (in >> type)
	{
		if (type == "vertex")
		{
			in >> v;
			this->addVertex(v);
		}
		else if (type == "edge")
		{
			in >> v;
			in >> w;
			in >> weight;
			this->addEdge(v, w, weight);
		}
	}
}



bool Graph::ifHaveV(string  v) {
	bool  inOrNot = false;
	for (int i = 0; i < v_size; i++) {
		if (v == vertex[i])
			inOrNot = true;
	}
	return  inOrNot;
}