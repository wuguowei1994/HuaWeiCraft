/*
 * Demo.cpp
 *
 *  Created on: 2017年1月2日
 *      Author: steven
 */

/*
              A
            /   \
 	       B     D
          / \   / \
 	 	 C   F G - H
         \   /
           E
   A B C D E F G H
 A   1   1
 B 1   1     1
 C	 1     1
 D 1           1 1
 E     1     1
 F   1     1
 G       1       1
 H       1     1
 */


#include <iostream>

#include "CMap.h"
#include "Node.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;
//对应第一张无权重的无向图
/*
int main(void) {
	//指定节点个数为8个
	CMap *pMap = new CMap(8);
	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	Node *pNodeE = new Node('E');
	Node *pNodeF = new Node('F');
	Node *pNodeG = new Node('G');
	Node *pNodeH = new Node('H');
	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	pMap->addNode(pNodeF);
	pMap->addNode(pNodeG);
	pMap->addNode(pNodeH);
	//A~B对应着0～7
	//(0,1)代表A-B之间有一条边;以此类推
	pMap->setValueToMaxtrixForUndirectedGraph(0, 1);
	pMap->setValueToMaxtrixForUndirectedGraph(1, 2);
	pMap->setValueToMaxtrixForUndirectedGraph(1, 5);
	pMap->setValueToMaxtrixForUndirectedGraph(3, 6);
	pMap->setValueToMaxtrixForUndirectedGraph(3, 7);
	pMap->setValueToMaxtrixForUndirectedGraph(6, 7);
	pMap->setValueToMaxtrixForUndirectedGraph(2, 4);
	pMap->setValueToMaxtrixForUndirectedGraph(4, 5);
	pMap->setValueToMaxtrixForUndirectedGraph(0, 3);
	pMap->printMatrix();
	pMap->resetNode();
	cout << "深度优先算法的结果：";
	//以A点作为起点
	pMap->depthFirstTraverse(0);
	cout << endl;
	cout << "广度优先算法的结果：";
	pMap->resetNode();
	pMap->breadthFirstTraverse(0);
	return 0;

}
*/


/*
 	 	 A
 	   / | \
 	  B--F--E
 	  \	/ \ /
 	   C --D
	//顶点编号
 	A B C D E F
 	0 1 2 3 4 5
	//边的权重
 	A-B 6      A-E 5    A-F 1
 	B-C 3      B-F 2
 	C-F 8      C-D 7
 	D-F 4      D-E 2
 	E-F 9
 */


/**
 * 对应第二张的无向带权重图
 */

int main(void) {
	clock_t start, end;
		 start = clock();
	//指定节点个数为6个
	CMap *pMap = new CMap(6);
	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	Node *pNodeE = new Node('E');
	Node *pNodeF = new Node('F');
	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	pMap->addNode(pNodeF);
	//A~F对应着0～6
	//(0,1,6)代表A-B之间有一条权重为6的边;以此类推
	pMap->setValueToMaxtrixForUndirectedGraph(0,1,6);
	pMap->setValueToMaxtrixForUndirectedGraph(0,4,5);
	pMap->setValueToMaxtrixForUndirectedGraph(0,5,1);
	pMap->setValueToMaxtrixForUndirectedGraph(1,2,3);
	pMap->setValueToMaxtrixForUndirectedGraph(1,5,2);
	pMap->setValueToMaxtrixForUndirectedGraph(2,5,8);
	pMap->setValueToMaxtrixForUndirectedGraph(2,3,7);
    pMap->setValueToMaxtrixForUndirectedGraph(3,5,4);
    pMap->setValueToMaxtrixForUndirectedGraph(3,4,2);
    pMap->setValueToMaxtrixForUndirectedGraph(4,5,9);
    //以A点作为起点
    pMap->primTree(0);  //普里姆算法
   //pMap->kruskalTree();  //克鲁斯卡尔算法
      end = clock();
      cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S"<<endl;
	return 0;
}



//对应课本第192页图6.21
/*
int main(void) {
	clock_t start, end;
	 start = clock();
	//指定节点个数为8个
	CMap *pMap = new CMap(8);
	Node *pNodeA = new Node('A');
	Node *pNodeB = new Node('B');
	Node *pNodeC = new Node('C');
	Node *pNodeD = new Node('D');
	Node *pNodeE = new Node('E');
	Node *pNodeF = new Node('F');
	Node *pNodeG = new Node('G');
	Node *pNodeH = new Node('H');
	pMap->addNode(pNodeA);
	pMap->addNode(pNodeB);
	pMap->addNode(pNodeC);
	pMap->addNode(pNodeD);
	pMap->addNode(pNodeE);
	pMap->addNode(pNodeF);
	pMap->addNode(pNodeG);
	pMap->addNode(pNodeH);
	//A~H对应着0～7
	//(0,1,4)代表A-B之间有一条权重为4的边;以此类推
	pMap->setValueToMaxtrixForUndirectedGraph(0,1,4);
	pMap->setValueToMaxtrixForUndirectedGraph(0,3,6);
	pMap->setValueToMaxtrixForUndirectedGraph(0,6,7);
	pMap->setValueToMaxtrixForUndirectedGraph(1,2,12);
	pMap->setValueToMaxtrixForUndirectedGraph(2,3,9);
	pMap->setValueToMaxtrixForUndirectedGraph(2,4,1);
	pMap->setValueToMaxtrixForUndirectedGraph(2,5,2);
    pMap->setValueToMaxtrixForUndirectedGraph(2,7,10);
    pMap->setValueToMaxtrixForUndirectedGraph(3,6,2);
    pMap->setValueToMaxtrixForUndirectedGraph(3,4,13);
    pMap->setValueToMaxtrixForUndirectedGraph(4,6,11);
    pMap->setValueToMaxtrixForUndirectedGraph(4,5,5);
    pMap->setValueToMaxtrixForUndirectedGraph(4,7,8);
    pMap->setValueToMaxtrixForUndirectedGraph(5,7,7);
    pMap->setValueToMaxtrixForUndirectedGraph(7,6,14);
    //以A点作为起点
    pMap->primTree(0);
//    pMap->kruskalTree();
    end = clock();
    cout<<"Run time: "<<(double)(end - start) / CLOCKS_PER_SEC<<"S"<<endl;
	return 0;
}
*/








