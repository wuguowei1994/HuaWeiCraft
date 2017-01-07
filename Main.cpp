/*
 * Demo.cpp
 *
 *  Created on: 2017年1月2日
 *      Author: steven
 */

#include <iostream>

#include "CMap.h"
#include "Node.h"
#include "stdlib.h"

using namespace std;

//Dijkstra算法

int main(void) {
//	clock_t start, end;
//	start = clock();
	//指定节点个数为4个
	CMap *pMap = new CMap(4);
	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	//A~E对应着0～4
	//(0,1,1)代表A-B之间有一条权重为1的有向边;以此类推
	pMap->setValueToMaxtrixForDirectedGraph(0, 1, 1);
	pMap->setValueToMaxtrixForDirectedGraph(0, 2, 2);
	pMap->setValueToMaxtrixForDirectedGraph(0, 3, 1);
	pMap->setValueToMaxtrixForDirectedGraph(2, 1, 3);
	pMap->setValueToMaxtrixForDirectedGraph(3, 1, 1);
	pMap->setValueToMaxtrixForDirectedGraph(2, 3, 1);
	pMap->setValueToMaxtrixForDirectedGraph(3, 2, 1);
	pMap->printMatrix();
	//以A点作为起点,计算出所有顶点的最短路径
	pMap->dijkstraTree(2);
	pMap->showPath(2, 1);
//    pMap->kruskalTree();
//	end = clock();
//	cout << "Run time: " << (double) (end - start) / CLOCKS_PER_SEC << "S"
//			<< endl;
	return 0;
}

