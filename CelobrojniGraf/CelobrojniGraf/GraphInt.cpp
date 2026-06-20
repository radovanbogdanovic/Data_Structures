#include "GraphInt.h"

#include <iostream>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"

GraphAsListsInt::GraphAsListsInt() : start(nullptr), nodeNum()
{
}

GraphAsListsInt::~GraphAsListsInt()
{
	cout << "Not implemented!" << endl;
}

LinkedNodeInt* GraphAsListsInt::findNode(const int& data) const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && ptr->node != data)
		ptr = ptr->next;
	return ptr;
}

LinkedEdgeInt* GraphAsListsInt::findEdge(const int& dataSrc, const int& dataDest) const
{
	LinkedNodeInt* ptr = findNode(dataSrc);
	if (ptr == nullptr)
		return nullptr;
	LinkedEdgeInt* pEdge = ptr->adj;
	while (pEdge != nullptr && pEdge->dest->node != dataDest)
		pEdge = pEdge->link;
	return pEdge;
}

void GraphAsListsInt::insertNode(const int& data)
{
	start = new LinkedNodeInt(data, nullptr, start);
	nodeNum++;
}

bool GraphAsListsInt::insertEdge(const int& dataSrc, const int& dataDest, const double& weight /*= 0*/)
{
	LinkedNodeInt* pSrc = nullptr;
	LinkedNodeInt* pDest = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && (pSrc == nullptr || pDest == nullptr)) {
		if (ptr->node == dataSrc) {
			pSrc = ptr;
		}
		else if (ptr->node == dataDest) {
			pDest = ptr;
		}
		ptr = ptr->next;
	}
	if (pSrc == nullptr || pDest == nullptr)
		return false;
	pSrc->adj = new LinkedEdgeInt(pDest, pSrc->adj);
	return true;
}

bool GraphAsListsInt::deleteEdge(const int& dataSrc, const int& dataDest)
{
	LinkedNodeInt* pSrc = findNode(dataSrc);
	if (pSrc == nullptr)
		return false;

	LinkedEdgeInt* pEdgePrev = nullptr;
	LinkedEdgeInt* pEdge = pSrc->adj;
	while (pEdge != nullptr && pEdge->dest->node != dataDest) {
		pEdgePrev = pEdge;
		pEdge = pEdge->link;
	}
	if (pEdge == nullptr)
		return false;

	if (pEdgePrev == nullptr)
		pSrc->adj = pEdge->link;
	else
		pEdgePrev->link = pEdge->link;

	delete pEdge;

	return true;
}

void GraphAsListsInt::deleteEdgeToNode(const LinkedNodeInt* pDest)
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr)
	{
		LinkedEdgeInt* pEdgePrev = nullptr;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr && pEdge->dest != pDest) {
			pEdgePrev = pEdge;
			pEdge = pEdge->link;
		}
		if (pEdge != nullptr)
		{
			if (pEdgePrev == nullptr)
				ptr->adj = pEdge->link;
			else
				pEdgePrev->link = pEdge->link;
		}
		ptr = ptr->next;
	}
}

bool GraphAsListsInt::deleteNode(const int& data)
{
	LinkedNodeInt* prev = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && ptr->node != data) {
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == nullptr)
		return false;

	LinkedEdgeInt* pEdge = ptr->adj;
	while (pEdge != nullptr) {
		LinkedEdgeInt* pEdgeTmp = pEdge->link;
		delete pEdge;
		pEdge = pEdgeTmp;
	}
	ptr->adj = nullptr;

	deleteEdgeToNode(ptr);

	if (prev == nullptr)
		start = start->next;
	else
		prev->next = ptr->next;

	delete ptr;
	nodeNum--;

	return true;
}

void GraphAsListsInt::print() const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr)
	{
		cout << ptr->node << " -> ";
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			cout << pEdge->dest->node << " | ";
			pEdge = pEdge->link;
		}
		cout << endl;
		ptr = ptr->next;
	}
}

void GraphAsListsInt::setStatusForAllNodes(int status) const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = status;
		ptr = ptr->next;
	}
}

long GraphAsListsInt::breadthFirstTraversal(const int& data) const
{
	long retVal = 0;

	LinkedNodeInt* ptr = findNode(data);
	if (ptr == nullptr)
		return 0;

	setStatusForAllNodes(1);

	QueueAsArrayLinkedNodeInt queue(nodeNum);
	queue.enqueue(ptr);
	ptr->status = 2;
	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		ptr->status = 3;
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status == 1) {
				queue.enqueue(pEdge->dest);
				pEdge->dest->status = 2;
			}
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalIterative(const int& data) const
{
	long retVal = 0;

	LinkedNodeInt* ptr = findNode(data);
	if (ptr == nullptr)
		return 0;

	setStatusForAllNodes(1);

	StackAsArrayLinkedNodeInt stack(nodeNum);
	stack.push(ptr);
	ptr->status = 2;
	while (!stack.isEmpty()) {
		ptr = stack.pop();
		ptr->status = 3;
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status == 1) {
				stack.push(pEdge->dest);
				pEdge->dest->status = 2;
			}
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalRecursive(LinkedNodeInt* ptr) const
{
	int retVal = 0;
	if (ptr->status != 1) {
		ptr->visit();
		ptr->status = 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			retVal += depthFirstTraversalRecursive(pEdge->dest);
			pEdge = pEdge->link;
		}
		retVal++;
	}
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalRecursive(const int& data) const
{
	LinkedNodeInt* pNode = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = 0;
		if (ptr->node == data) {
			pNode = ptr;
		}
		ptr = ptr->next;
	}

	if (pNode == nullptr)
		return 0;

	return depthFirstTraversalRecursive(pNode);
}

long GraphAsListsInt::topologicalOrderTravrsal() const
{
	int retVal = 0;

	setStatusForAllNodes(0);

	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			pEdge->dest->status += 1;
			pEdge = pEdge->link;
		}
		ptr = ptr->next;
	}

	QueueAsArrayLinkedNodeInt queue(nodeNum);
	ptr = start;
	while (ptr != nullptr) {
		if (ptr->status == 0)
			queue.enqueue(ptr);
		ptr = ptr->next;
	}

	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			pEdge->dest->status--;
			if (pEdge->dest->status == 0)
				queue.enqueue(pEdge->dest);
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

bool GraphAsListsInt::arePathsPossible(LinkedNodeInt* start, LinkedNodeInt* goal1, LinkedNodeInt* goal2, LinkedNodeInt* mid) const
{
	//status:
	//0 - zabranjen
	//1 - neobradjen
	//2 - u q neobradjen
	//3 - obradjen
	setStatusForAllNodes(1);
	QueueAsArrayLinkedNodeInt queue = QueueAsArrayLinkedNodeInt(nodeNum);
	queue.enqueue(start);
	start->status = 2;
	start->prev = nullptr;
	LinkedNodeInt* ptr = nullptr;
	LinkedEdgeInt* adj = nullptr;
	bool firstP = false;
	bool secondP1 = false;
	bool secondP2 = false;
	
	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		adj = ptr->adj;
		
		if (ptr == mid) {
			firstP = true;
			setStatusForAllNodes(1);
			while (ptr->prev) {
				ptr->prev->status = 0;
				ptr = ptr->prev;
			}
			break;
		}

		ptr->status = 3;
		while (adj) {
			if (adj->dest->status == 1) {
				queue.enqueue(adj->dest);
				adj->dest->prev = ptr;
				adj->dest->status = 2;
			}
			adj = adj->link;
		}
	}
	if (!firstP) {
		return false;
	}
	QueueAsArrayLinkedNodeInt queue1 = QueueAsArrayLinkedNodeInt(nodeNum);
	queue1.enqueue(mid);
	mid->status = 2;
	while (!queue1.isEmpty()) {
		ptr = queue1.dequeue();
		adj = ptr->adj;

		if (ptr == goal1) {
			secondP1 = true;
		}
		if (ptr == goal2) {
			secondP2 = true;
		}

		ptr->status = 3;
		while (adj) {
			if (adj->dest->status == 1) {
				adj->dest->prev = ptr;
				adj->dest->status = 2;
				queue1.enqueue(adj->dest);
			}

			adj = adj->link;
		}
	
	}
	if (firstP && secondP1 && secondP2) {
		return true;
	}
	
	return false;
	


}

void GraphAsListsInt::deorientation()
{
	LinkedNodeInt* ptr = start;
	LinkedEdgeInt* adj = nullptr;
	while (ptr) {
		adj = ptr->adj;
		while (adj) {
			if (!findEdge(adj->dest->node, ptr->node)) {
				insertEdge(adj->dest->node, ptr->node);
			}
			adj = adj->link;
		}

		ptr = ptr->next;
	}
}

int GraphAsListsInt::printMaxConnectedComponentNodes()
{
	//status 0 - zabranjen, 1 - neobradjen, 2 - u q neobradjen, 3 - obradjen, 4- max komponenta

	deorientation();
	setStatusForAllNodes(1);
	LinkedNodeInt* ptr = start;
	LinkedNodeInt* ptr2 = nullptr;
	LinkedEdgeInt* adj = ptr->adj;
	QueueAsArrayLinkedNodeInt q = QueueAsArrayLinkedNodeInt(nodeNum);
	int counter = 0;
	int max_count = 0;
	LinkedNodeInt* max_end = nullptr;
	LinkedNodeInt* max_start = nullptr;
	for (int i = 0; i < nodeNum; i++) {
		if (ptr->status == 1) {
			q.enqueue(ptr);
			ptr->status = 2;
			while (!q.isEmpty()) {
				ptr2 = q.dequeue();
				ptr2->status = 1;
				adj = ptr2->adj;
				counter++;
				if (counter > max_count) {
					max_count = counter;
					max_end = ptr2;
					max_start = ptr;
				}
			
				ptr2->status = 3;

				while (adj) {
					if (adj->dest->status == 1) {
						q.enqueue(adj->dest);
						adj->dest->status = 2;
						adj->dest->prev = ptr2;
					}
					adj = adj->link;
				}
			}
			
			counter = 0;
			ptr = ptr->next;
		} else {
			counter = 0;
			ptr = ptr->next;
	
		}
	}
	//if (max_end && max_start) {
	//	do {
	//		max_end->visit();
	//		max_end = max_end->prev;

	//	} while (max_end != nullptr);
	//}
	if (max_start == nullptr)
		return 0;
	QueueAsArrayLinkedNodeInt q2 = QueueAsArrayLinkedNodeInt(nodeNum);
	setStatusForAllNodes(1);
	q2.enqueue(max_start);
	max_start->status = 2;
	while (!q2.isEmpty()) {
		ptr2 = q2.dequeue();
		ptr2->visit();
		adj = ptr2->adj;
		ptr2->status = 3;
		while (adj) {
			if (adj->dest->status == 1) {
				q2.enqueue(adj->dest);
				adj->dest->status = 2;
			}

			adj = adj->link;
		}
	}

	return max_count;
}

int* GraphAsListsInt::defineOrder(int* dep, int n)
{
	while (start != nullptr) {
		deleteNode(start->node);
	}
	LinkedNodeInt* dependent = nullptr;
	LinkedNodeInt* dependency = nullptr;
	for (int i = 0; i < n; i += 2) {
		dependent = findNode(dep[i]);
		dependency = findNode(dep[i + 1]);

		if (!dependent) {
			insertNode(dep[i]);
			dependent = findNode(dep[i]);
			dependent->status = 0;
		}

		if (!dependency) {
			insertNode(dep[i + 1]);
			dependency = findNode(dep[i + 1]);
			dependency->status = 0;
		}

		if (!findEdge(dep[i + 1], dep[i])) {
			insertEdge(dep[i + 1], dep[i]);
			dependent->status++;
		}
	}
	int* rezultat = new int[nodeNum]();
	LinkedNodeInt* ptr = start;
	LinkedEdgeInt* adj = nullptr;
	int i = 0;
	QueueAsArrayLinkedNodeInt q = QueueAsArrayLinkedNodeInt(nodeNum);
	while (ptr) {
		if (ptr->status == 0) {
			q.enqueue(ptr);
		}
		ptr = ptr->next;
	}
	while (!q.isEmpty()) {
		ptr = q.dequeue();
		rezultat[i] = ptr->node;
		i++;
		adj = ptr->adj;
		while (adj) {
			adj->dest->status--;
			if (adj->dest->status == 0) {
				q.enqueue(adj->dest);
			}
			adj = adj->link;
		}
	}
	if (i == nodeNum) {
		return rezultat;
	}
	else {
		return nullptr;
	}
}




