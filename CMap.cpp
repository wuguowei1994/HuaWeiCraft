/*
 * CMap.cpp

 *
 *  Created on: 2017年1月2日
 *      Author: steven
 */
#include "CMap.h"
#include <iostream>
#include <vector>
#include "string.h"
#include <limits.h>
#include <stack>
using namespace std;
CMap::CMap(int capacity) {
	//可以容纳的顶点最大值
	m_iCapacity = capacity;
	//已经添加的顶点(结点)个数
	m_iNodeCount = 0;
	weightSum = 0;
	//声明一个数组，数组的元素类型是Node
	m_pNodeArray = new Node[m_iCapacity]; //用来存放顶点的数组
	//声明一个数组，数组的元素类型是int
	m_pMatrix = new int[m_iCapacity * m_iCapacity]; //用来存放邻接矩阵;本质上它是一维数组
	m_dist = new int[m_iCapacity];
	m_path = new int[m_iCapacity];
	//将所有元素都置为0
	/**
	 * void *memset(void *s, int v, size_t n);
	 这里s可以是数组名，也可以是指向某一内在空间的指针；
	 v为要填充的值；
	 n为要填充的字节数，通常为sizeof(s)；
	 sizeof(int):计算int类型的大小
	 */
	memset(m_pMatrix, 0, m_iCapacity * m_iCapacity * sizeof(int));
	memset(m_dist, 0, m_iCapacity * sizeof(int));
	memset(m_path, 0, m_iCapacity * sizeof(int));
	//如果有n个顶点，那么生成的树一定是n-1条边
	m_pEdge = new Edge[m_iCapacity - 1];
}
CMap::~CMap() {
	delete[] m_pNodeArray;
	delete[] m_pMatrix;
	delete[] m_pEdge;
	delete[] m_dist;
	delete[] m_path;
}
bool CMap::addNode(Node *pNode) {
	//m_pNodeArray:用来存放顶点的数组;m_iNodeCount:已经添加的顶点(结点)个数;
	//m_pNodeArray[]这个数组的下标就是顶点的索引
	if (pNode == NULL) {
		return false;
	}
	m_pNodeArray[m_iNodeCount].m_cData = pNode->m_cData;
	m_iNodeCount++;
	return true;
}
void CMap::resetNode() {
	for (int i = 0; i < m_iNodeCount; i++) {
		m_pNodeArray[i].m_bIsVisited = false;
	}
}
//为有向图设置邻接矩阵
bool CMap::setValueToMaxtrixForDirectedGraph(int row, int col, int val) {
	//用来存放邻接矩阵;row:行;col：列
	//有向图的邻接矩阵不沿对角线对称
	if (row < 0 || row >= m_iCapacity || col < 0 || col >= m_iCapacity)
		return false;
	m_pMatrix[row * m_iCapacity + col] = val;
	return true;
	//PS：注意这里的索引是从0开始的，所以row不用加1
}

bool CMap::getValueFromMatrix(int row, int col, int &val) {
	val = m_pMatrix[row * m_iCapacity + col];
	return true;
}

int CMap::getValueFromMatrix(int row, int col) {
	return m_pMatrix[row * m_iCapacity + col];
}
void CMap::printMatrix() {
	for (int i = 0; i < m_iCapacity; i++) {
		for (int k = 0; k < m_iCapacity; k++) {
			cout << m_pMatrix[i * m_iCapacity + k] << " ";
		}
		cout << endl;
	}
}
//深度优先搜索
void CMap::depthFirstTraverse(int nodeIndex) {
	int value = 0;
	//m_pNodeArray :用来存放顶点的数组
	cout << m_pNodeArray[nodeIndex].m_cData << "->";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	//通过邻接矩阵判断是否与其他的顶点有连接
	for (int i = 0; i < m_iCapacity; i++) {
		getValueFromMatrix(nodeIndex, i, value);
		if (value != 0)	//value!=0表明有相连的顶点
				{
			//再判断该点是否被访问过
			if (m_pNodeArray[i].m_bIsVisited) {
				//结束掉这一次循环
				continue;
			}
			//当这个点没有被访问过才开始迭代深度优先搜索:以这个节点为起点，开始下一轮的深度优先搜索
			else {
				depthFirstTraverse(i);
			}
		}
		//没有顶点与该顶点相连
		else {
			continue;
		}
	}
}
//广度优先搜索
void CMap::breadthFirstTraverse(int nodeIndex) {
	cout << m_pNodeArray[nodeIndex].m_cData << "->";
	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	//vector是一个能够存放任意类型的动态数组，能够增加和压缩数据
	vector<int> curVec;
	//在vector尾部加入一个数据
	curVec.push_back(nodeIndex);
	breadthFirstTraverseImpl(curVec);
}
//广度优先的具体实现实现
void CMap::breadthFirstTraverseImpl(vector<int> preVec) {
	int value = 0;
	vector<int> curVec;
	//这个for循环执行完毕以后，会把preVec里面的顶点对应的下一层顶点全部访问完毕
	for (int j = 0; j < (int) preVec.size(); j++) {
		for (int i = 0; i < m_iCapacity; i++) {
			getValueFromMatrix(preVec[j], i, value);
			if (value != 0) {
				if (m_pNodeArray[i].m_bIsVisited)
					continue;
				else {
					cout << m_pNodeArray[i].m_cData << "->";
					m_pNodeArray[i].m_bIsVisited = true;
					curVec.push_back(i);
				}

			}
		}
	}
	//把已经保存在curVec里面的顶点的下一层顶点再访问一遍
	if (curVec.size() == 0)
		return;
	else
		breadthFirstTraverseImpl(curVec);

}
//普里姆生成树
void CMap::primTree(int nodeIndex) {
	//保存边的权值
	int value = 0;
	//边的计数器
	int edgeCount = 0;
	//点集
	vector<int> nodeVec;
	//边集
	vector<Edge> edgeVec;

	cout << "prim算法的生成树是：" << m_pNodeArray[nodeIndex].m_cData << "-->";

	nodeVec.push_back(nodeIndex);
	m_pNodeArray[nodeIndex].m_bIsVisited = true;

	//算法停止条件：边数=顶点数-1
	while (edgeCount < m_iCapacity - 1)
	//里面的for循环会把与该顶点相关的所有边都放入集合中
	{
		//取出集合中尾部的值
		int temp = nodeVec.back();
		for (int i = 0; i < m_iCapacity; i++) {
			getValueFromMatrix(temp, i, value);
			if (value != 0) {
				if (m_pNodeArray[i].m_bIsVisited)
					continue;
				else {
					//新建一条边
					Edge edge(temp, i, value);
					//把这条可用边放入边的集合中
					edgeVec.push_back(edge);
				}

			}
		}

		//去除边集中错误的边(这一步非常重要)
		for (int i = 0; i < (int) edgeVec.size(); i++) {
			if (m_pNodeArray[edgeVec[i].m_iNodeIndexB].m_bIsVisited
					&& m_pNodeArray[edgeVec[i].m_iNodeIndexA].m_bIsVisited)
				edgeVec.erase(edgeVec.begin() + i);

		}
		//从可选边集合中找出最小的边
		//函数返回的是被传入的边集中最小边的索引
		int edgeIndex = getMinEdge(edgeVec);
		//把这条最小边的状态改为已选用
		edgeVec[edgeIndex].m_bSelected = true;

		//m_pEdge是一个数组，它内部元素的类型是Edge;把这条最小边放入m_pEdge数组中
		m_pEdge[edgeCount] = edgeVec[edgeIndex];
		//边的计数器加1
		edgeCount++;

		//把找到的这条边的终点作为下一次prim算法的起点，进行迭代
		int nextNodeIndex = edgeVec[edgeIndex].m_iNodeIndexB;
		//放入点集
		nodeVec.push_back(nextNodeIndex);
		if (m_pNodeArray[edgeVec[edgeIndex].m_iNodeIndexB].m_bIsVisited) {
			cout << m_pNodeArray[edgeVec[edgeIndex].m_iNodeIndexA].m_cData
					<< "-->";
		} else
			cout << m_pNodeArray[edgeVec[edgeIndex].m_iNodeIndexB].m_cData
					<< "-->";
		//更改点的状态
		m_pNodeArray[nextNodeIndex].m_bIsVisited = true;

	}

}

int CMap::getMinEdge(vector<Edge> edgeVec) {
	int minWeight = 0;
	int edgeIndex = 0;
	int i = 0;
//找出一条没有被访问过的边
	for (; i < (int) edgeVec.size(); i++) {
		if (!edgeVec[i].m_bSelected) {
			minWeight = edgeVec[i].m_iWeightValue;
			edgeIndex = i;
			//找到以后终止整个for循环
			break;
		}

	}

	if (minWeight == 0)		//如果成立，说明所有的边都被访问过
		return -1;
//寻找最小权重
	for (; i < (int) edgeVec.size(); i++) {
		if (edgeVec[i].m_bSelected || edgeVec[i].m_iNodeIndexA == 1
				|| edgeVec[i].m_iNodeIndexB == 1) {
			continue;
		} else {
			if (minWeight > edgeVec[i].m_iWeightValue) {
				minWeight = edgeVec[i].m_iWeightValue;
				edgeIndex = i;
			}
		}

	}
//返回找到的最小边的权重
	return edgeIndex;

}
//克鲁斯卡尔算法生成树
void CMap::kruskalTree() {

	int value = 0;
	int edgeCount = 0;

	//数组的数组
	//定义存放结点集合的数组
	vector<vector<int> > nodeSets;

	//第一步：取出所有边
	vector<Edge> edgeVec;
	for (int i = 0; i < m_iCapacity; i++) {
		for (int k = i + 1; k < m_iCapacity; k++) {
			getValueFromMatrix(i, k, value);
			if (value != 0) {
				Edge edge(i, k, value);
				edgeVec.push_back(edge);

			}
		}
	}

	//第二步：从所有边中取出组成最小生成树的边
	//1.找到算法结束条件
	while (edgeCount < m_iCapacity - 1) {
		//2.从边集合中找到最小边
		int minEdgeIndex = getMinEdge(edgeVec);
		edgeVec[minEdgeIndex].m_bSelected = true;
		//3.找出最小边连接的点
		int nodeAIndex = edgeVec[minEdgeIndex].m_iNodeIndexA;
		int nodeBIndex = edgeVec[minEdgeIndex].m_iNodeIndexB;

		bool nodeAIsInSet = false;
		bool nodeBIsInSet = false;

		int nodeAInSetLabel = -1;
		int nodeBInSetLabel = -1;
		//4.找出点所在的点集合
		for (int i = 0; i < (int) nodeSets.size(); i++) {
			nodeAIsInSet = isInSet(nodeSets[i], nodeAIndex);
			if (nodeAIsInSet) {
				nodeAInSetLabel = i;//i实际上是该点所在集合在vector<vector<int>> nodeSets这个数组的数组中的索引
			}

		}

		for (int i = 0; i < (int) nodeSets.size(); i++) {
			nodeBIsInSet = isInSet(nodeSets[i], nodeBIndex);
			if (nodeBIsInSet) {
				nodeBInSetLabel = i;//i实际上是该点所在集合在vector<vector<int>> nodeSets这个数组的数组中的索引
			}

		}

		//5.根据点所在集合的不同做出不同处理
		//对应的情况：找到的边它的两个顶点都不在任何集合中;那么新建一个集合，把这两个点放入即可
		if (nodeAInSetLabel == -1 && nodeBInSetLabel == -1) {
			vector<int> vec;
			vec.push_back(nodeAIndex);
			vec.push_back(nodeBIndex);
			nodeSets.push_back(vec);
		}
		//对应A是新点，B是已经存在于集合中的点;那么把A放入B所在的集合即可
		else if (nodeAInSetLabel == -1 && nodeBInSetLabel != -1) {
			nodeSets[nodeBInSetLabel].push_back(nodeAIndex);
		}
		//对应B是新点，A是已经存在于集合中的点;那么把B放入A所在的集合即可
		else if (nodeAInSetLabel != -1 && nodeBInSetLabel == -1) {
			nodeSets[nodeAInSetLabel].push_back(nodeBIndex);
		}
		//对应A和B都不是新点，而且A和B不在一个集合中;那么把这两个集合合并即可
		else if (nodeAInSetLabel != -1 && nodeBInSetLabel != -1
				&& nodeAInSetLabel != nodeBInSetLabel) {
			//合并两个集合,将A和B两个集合合并到A中
			mergeNodeSet(nodeSets[nodeAInSetLabel], nodeSets[nodeBInSetLabel]);
			//去掉B集合
			for (int k = nodeBInSetLabel; k < (int) nodeSets.size() - 1; k++) {
				nodeSets[k] = nodeSets[k + 1];
			}

		}
		//对应A和B都不是新点，而且A和B在一个集合中;如果采用，那么会形成环路，所以放弃这条边
		else if (nodeAInSetLabel != -1 && nodeAInSetLabel == nodeBInSetLabel) {
			continue;

		}

		//把最小边放入集合中
		m_pEdge[edgeCount] = edgeVec[minEdgeIndex];
		edgeCount++;
		weightSum = weightSum + edgeVec[minEdgeIndex].m_iWeightValue;
		cout << edgeVec[minEdgeIndex].m_iNodeIndexA << "--"
				<< edgeVec[minEdgeIndex].m_iNodeIndexB << " ";
		cout << edgeVec[minEdgeIndex].m_iWeightValue << endl;
		if (edgeCount == m_iCapacity - 1)
			cout << "权重之和：" << weightSum << endl;

	}
}
//target是点的索引
bool CMap::isInSet(vector<int> nodeSet, int target) {
	for (int i = 0; i < (int) nodeSet.size(); i++) {
		if (nodeSet[i] == target)
			return true;
	}
	return false;
}

void CMap::mergeNodeSet(vector<int>&nodeSetA, vector<int> nodeSetB) {
	for (int i = 0; i < (int) nodeSetB.size(); i++) {
		nodeSetA.push_back(nodeSetB[i]);
	}
}
//Dijkstra算法;dist[i]记录了从起点到达顶点i的最短距离;path[i]记录了从起点到顶点i路径上的i前面的一个顶点
void CMap::dijkstraTree(int nodeIndex) {
	int i, j, k;
	//点集
	vector<int> nodeVec;
	//边集
	vector<Edge> edgeVec;
	//数组dist[i]记录了从起点到达顶点i的最短距离
	//数组path[i]记录了从起点到顶点i路径上的i前面的一个顶点

	for (i = 0; i < m_iCapacity; i++)     //初始化
			{
		if (getValueFromMatrix(nodeIndex, i) > 0 && i != nodeIndex) {
			m_dist[i] = getValueFromMatrix(nodeIndex, i);
			m_path[i] = nodeIndex;     //path记录最短路径上从v0到i的前一个顶点
		} else {
			m_dist[i] = INT_MAX;    //若i不与v0直接相邻，则权值置为无穷大
			m_path[i] = -1;
		}
		m_pNodeArray[i].m_bIsVisited = false;
		m_path[nodeIndex] = nodeIndex;
		m_dist[nodeIndex] = 0;
	}

	m_pNodeArray[nodeIndex].m_bIsVisited = true;
	for (int i = 1; i < m_iCapacity; i++)     //循环扩展n-1次
			{
		int min = INT_MAX;
		int u = 0;
		for (j = 0; j < m_iCapacity; j++)    //寻找未被扩展的权值最小的顶点
				{
			if (m_pNodeArray[j].m_bIsVisited == false && m_dist[j] < min) {
				min = m_dist[j];
				u = j;
			}
		}
		m_pNodeArray[u].m_bIsVisited = true;
		for (k = 0; k < m_iCapacity; k++)   //更新dist数组的值和路径的值
				{
			if (m_pNodeArray[k].m_bIsVisited == false
					&& getValueFromMatrix(u, k) > 0
					&& min + getValueFromMatrix(u, k) < m_dist[k]) {
				m_dist[k] = min + getValueFromMatrix(u, k);
//				cout<<"m_dist"<<k<<"为:"<<m_dist[k];
				m_path[k] = u;
			}
		}
	}
}
//打印从顶点beginIndex到顶点endIndex最短路径上的各个顶点
void CMap::showPath(int beginIndex, int endIndex) {
	int count=0;
	cout << "从顶点" << beginIndex << "到顶点" << endIndex << "的最短路径:" << endl;
	stack<int> s;
	while (endIndex != beginIndex) {
		s.push(endIndex);
		endIndex = m_path[endIndex];
	}
	s.push(endIndex);
	while (!s.empty()) {
		cout << s.top() << "--";
		count++;
		s.pop();
	}
	cout << endl << "最短路径的权重为：" << m_dist[1];
}

