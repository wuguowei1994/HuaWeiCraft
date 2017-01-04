/*
 * Edge.h
 *
 *  Created on: 2017年1月3日
 *      Author: steven
 */

#ifndef EDGE_H_
#define EDGE_H_

class Edge{
public:
	Edge(int nodeIndexA=0,int nodeIndexB=0,int weightValue=0);
	//连接边的两个点：不强调起点和终点(无向图)
	int m_iNodeIndexA;
	int m_iNodeIndexB;
	//边的权重
	int m_iWeightValue;
	bool m_bSelected;
};





#endif /* EDGE_H_ */
