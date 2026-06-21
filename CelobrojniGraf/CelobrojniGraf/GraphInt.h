#pragma once

//#include "LinkedEdgeInt.h"
#include "LinkedNodeInt.h"

class GraphAsListsInt
{
protected:
	LinkedNodeInt* start;
	long nodeNum;
public:
	GraphAsListsInt();
	~GraphAsListsInt();

	LinkedNodeInt* findNode(const int& data) const;
	LinkedEdgeInt* findEdge(const int& dataSrc, const int& dataDest) const;

	void insertNode(const int& data);
	bool insertEdge(const int& dataSrc, const int& dataDest, const double& weight = 0);

private:
	void deleteEdgeToNode(const LinkedNodeInt* pDest);
public:
	bool deleteEdge(const int& dataSrc, const int& dataDest);
	bool deleteNode(const int& data);

	void print() const;

private:
	void setStatusForAllNodes(int status) const;
public:
	long breadthFirstTraversal(const int& data) const;
	long depthFirstTraversalIterative(const int& data) const;
private:
	long depthFirstTraversalRecursive(LinkedNodeInt* ptr) const;
public:
	long depthFirstTraversalRecursive(const int& data) const;


	bool arePathsPossible(LinkedNodeInt* start, LinkedNodeInt* goal1, LinkedNodeInt* goal2, LinkedNodeInt* mid) const;
	void deorientation();
	int printMaxConnectedComponentNodes();
	int* defineOrder(int* dep, int n);

	int countSafeNodes() const;
	bool isSafe(LinkedNodeInt* ptr) const;

	long topologicalOrderTravrsal() const;

	int whichOneIsCloser(int a, int b, int c) const;
	void ensureEdgeExists(int b, int c);
	LinkedNodeInt* FindStation(int s, int g1, int g2, int& noInter);
	bool pathGoesThrough(int a, int b, int c);
	bool pathThroughEdgeExists(int a, int b, int c, int d);

};

