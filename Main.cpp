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
	//指定节点个数为5个
	CMap *pMap = new CMap(5);
	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	Node *pNodeE = new Node('E');
	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	//A~E对应着0～4
	//(0,1,1)代表A-B之间有一条权重为1的有向边;以此类推
	pMap->setValueToMaxtrixForDirectedGraph(0, 1, 100);
	pMap->setValueToMaxtrixForDirectedGraph(0, 2, 30);
	pMap->setValueToMaxtrixForDirectedGraph(0, 4, 10);
	pMap->setValueToMaxtrixForDirectedGraph(2, 1, 60);
	pMap->setValueToMaxtrixForDirectedGraph(2, 3, 60);
	pMap->setValueToMaxtrixForDirectedGraph(3, 1, 10);
	pMap->setValueToMaxtrixForDirectedGraph(4, 3, 50);
//	pMap->printMatrix();
	//以A点作为起点
	pMap->dijkstraTree(0);
	pMap->showPath(0,4);
//	for (int i = 0; i < 5; i++) {
//		if (i != 0) {
//			pMap->showPath(i, 0);
//			cout << pMap->m_dist[i] << endl;
//		}
//	}
//    pMap->kruskalTree();
//	end = clock();
//	cout << "Run time: " << (double) (end - start) / CLOCKS_PER_SEC << "S"
//			<< endl;
	return 0;
}

