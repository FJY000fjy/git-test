#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <sstream>
#include <fstream>
#include<iostream>
#include<vector>
using  namespace  std;
const  int  MAX_SCALE = 20;
class Graph
{
private:
	vector<string>  vertex;//��ļ���v[0]='a',v['1']='s'....
	int  v_size = 0;//�������
	vector<vector<int>> matrix;//�ڽӾ���
	vector<bool>   v_isVisited;//ĳ���Ƿ��Ѿ�������
	vector<int>    d_shortest;//Դ��s���������������̾���
	vector<int>    pre;//Դ��s����ĳ�����ֱ��ǰ��
	string  v;//���
	string  w;//�յ�

public:
	Graph();
	~Graph();
	void addVertex(std::string v);
	void addEdge(std::string v, std::string w, int weight);
	void  initialize();//��ȡ�����ݺ���еĳ�ʼ������
	int  vToIndex(string  v);//��ĳ������ĸ��ʾ�ĵ����Ϊ������
	int  findPre(int index);//����ĳ���㣬����pre���ҵ��������·���ϵ�ǰ��
	int shortestPath(std::string v, std::string w);
	std::string getShortestPath();
	void readGraphFromFile(std::string pathToFile);
	void showGraph();//��ʾ�����ڽӾ���
	void showInfo();//��ʾ���Ź��߱������
	bool ifHaveV(string  v);//���������û�����ĵ��Ƿ���ͼ��
};

#endif
#pragma once
