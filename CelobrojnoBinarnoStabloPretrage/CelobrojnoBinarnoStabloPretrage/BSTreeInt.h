#pragma once

#include "BSTNodeInt.h"

class BSTreeInt
{
protected:
	BSTNodeInt* root;
	long numOfElements;

	void deleteTree(BSTNodeInt* ptr);

	void inorder(const BSTNodeInt* ptr) const;
	void preorder(const BSTNodeInt* ptr) const;
	void postorder(const BSTNodeInt* ptr) const;

public:
	BSTreeInt() { root = nullptr; numOfElements = 0; }
	~BSTreeInt() { deleteTree(root); }

	bool isEmpty() const { return root == nullptr; }

	bool isInTree(int el) const { return search(el) != nullptr; }
	BSTNodeInt* search(int el) const;

	void insert(int el);
	void add(int el);
	void deleteByCopying(int el);
	void deleteByMerging(int el);

	void preorder() const { preorder(root); }
	void inorder() const { inorder(root); }
	void postorder() const { postorder(root); }

	void iterativePreorder() const;
	void breadthFirstSearch() const;

	int countCloseParents(BSTNodeInt* root, int n) const;

	int countCloseParents(int n) const;

	void deleteLeaves();
	void deleteLeaves(BSTNodeInt* ptr, BSTNodeInt* ptr_parent, bool isright);
	int maxLevel() const;
	BSTNodeInt* minEvenDiff() const;
	int minEvenDiff(BSTNodeInt* ptr, BSTNodeInt*& best, int& minDiff, bool& found) const;
	void populate(int* arData, int n);
	int sumInterval(int min, int max) const;
	int sumInterval(BSTNodeInt* ptr, int min, int max, int& sum) const;
	void create(int* vec, int n);
	int inorderDistance(int a, int b) const;
	void inorderDistance(BSTNodeInt* ptr, bool& foundA, bool& foundB, int a, int b, int& length) const;
	BSTNodeInt* maxDiffOfEvenNodes() const;
	int maxDiffOfEvenNodes(BSTNodeInt* ptr, int& max, BSTNodeInt*& rezultat) const;
	int sumUpThePath(BSTNodeInt* root, int destKey);
	int sumUpThePath(BSTNodeInt* ptr1, int destKey, int& sum);
	BSTNodeInt* findDeepestLeaf(BSTNodeInt* root) const;
	void findDeepestLeaf(BSTNodeInt* ptr, BSTNodeInt*& rez, int& depth, int& maxdepth) const;
	BSTNodeInt* getDeepestEvenParent(BSTNodeInt* root);
	void getDeepestEvenParent(BSTNodeInt* root, BSTNodeInt*& rez);
};

