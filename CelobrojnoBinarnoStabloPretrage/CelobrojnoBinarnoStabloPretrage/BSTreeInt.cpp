#include "BSTreeInt.h"

#include <exception>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"
#include <cmath>

void BSTreeInt::deleteTree(BSTNodeInt* ptr)
{
	if (ptr != nullptr) {
		deleteTree(ptr->left);
		deleteTree(ptr->right);
		delete ptr;
	}
}

BSTNodeInt* BSTreeInt::search(int el) const
{
	BSTNodeInt* ptr = root;
	while (ptr != nullptr)
		if (ptr->isEQ(el))
			return ptr;
		else if (ptr->isGT(el))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	return nullptr;
}

void BSTreeInt::insert(int el)
{
	BSTNodeInt* ptr = root, * par = nullptr;
	while (ptr != nullptr) {  // trazenje mesta za umetanje novog cvora
		par = ptr;
		if (ptr->isLT(el))
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	if (root == nullptr)    // stablo je prazno
		root = new BSTNodeInt(el);
	else if (par->isLT(el))
		par->right = new BSTNodeInt(el);
	else
		par->left = new BSTNodeInt(el);
	numOfElements++;
}

void BSTreeInt::add(int el)
{
	if (isInTree(el)) {
		return;
	}
	BSTNodeInt* ptr = root, * par = nullptr;
	while (ptr != nullptr) {  // trazenje mesta za umetanje novog cvora
		par = ptr;
		if (ptr->isLT(el))
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	if (root == nullptr)    // stablo je prazno
		root = new BSTNodeInt(el);
	else if (par->isLT(el))
		par->right = new BSTNodeInt(el);
	else
		par->left = new BSTNodeInt(el);
	numOfElements++;
}

void BSTreeInt::deleteByCopying(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) { 	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)             // cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)         // cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			BSTNodeInt* parent = node;
			while (tmp->right != nullptr) {		// nalazenje krajnjeg desnog cvora
				parent = tmp;             		// u levom podstablu
				tmp = tmp->right;
			}
			node->setKey(tmp->getKey());		// prepisivanje reference na kljuc 
			if (parent == node)           		// tmp je direktni levi potomak node-a
				parent->left = tmp->left;		// ostaje isti raspored u levom podstablu
			else
				parent->right = tmp->left; 		// levi potomak tmp-a 
			delete tmp;							// se pomera na mesto tmp-a
			numOfElements--;
			return;
		}
		if (ptr == root)						// u slucaju (1) i (2) samo je pomerena
			root = node;						// referenca node pa je potrebno
		else if (par->left == ptr)				// izmeniti i link prethodnog cvora
			par->left = node;					// u slucaju (3) ovo nema dejstva
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::deleteByMerging(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) {	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)				// cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)			// cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			while (tmp->right != nullptr)		// nalazenje krajnjeg desnog cvora
				tmp = tmp->right;				// u levom podstablu
			tmp->right = node->right;			// prebacivanje desnog linka node-a u tmp
			node = node->left;					// na tekucem mestu bice prvi levi potomak
		}
		if (ptr == root)
			root = node;
		else if (par->left == ptr)
			par->left = node;
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::preorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		ptr->visit();
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

void BSTreeInt::inorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		inorder(ptr->left);
		ptr->visit();
		inorder(ptr->right);
	}
}

void BSTreeInt::postorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		ptr->visit();
	}
}

void BSTreeInt::iterativePreorder() const
{
	BSTNodeInt* ptr = root;
	StackAsArrayBSTNodeInt stack(numOfElements);
	if (ptr != nullptr) {
		stack.push(ptr);
		while (!stack.isEmpty()) {
			ptr = stack.pop();
			ptr->visit();
			if (ptr->right != nullptr)	// levi potomak se stavlja u magacin
				stack.push(ptr->right); // posle desnog, da bi se prvi obradio
			if (ptr->left != nullptr)
				stack.push(ptr->left);
		}
	}
}

void BSTreeInt::breadthFirstSearch() const
{
	BSTNodeInt* ptr = root;
	QueueAsArrayBSTNodeInt queue(numOfElements);
	if (ptr != nullptr) {
		queue.enqueue(ptr);
		while (!queue.isEmpty()) {
			ptr = queue.dequeue();
			ptr->visit();
			if (ptr->left != nullptr)
				queue.enqueue(ptr->left);
			if (ptr->right != nullptr)
				queue.enqueue(ptr->right);
		}
	}
}

int BSTreeInt::countCloseParents(BSTNodeInt* root, int n) const // JANUAR 2024
{
	int count = 0;
	BSTNodeInt* ptr = root;
	BSTNodeInt* levi = nullptr;
	BSTNodeInt* desni = nullptr;
	if (ptr == nullptr) {
		return 0;
	}
	if (ptr->right and ptr->left) {
		if (n >= (ptr->getKey() - ptr->left->getKey()) && n >= (ptr->right->getKey() - ptr->getKey())) {
			count += 1;
			levi = root->left;
			desni = root->right;
			return count + countCloseParents(levi, n) + countCloseParents(desni, n);
		}
		else {
			levi = root->left;
			desni = root->right;
			return count + countCloseParents(levi, n) + countCloseParents(desni, n);
		}

	}
	else if (ptr->right) {
		if (n >= (ptr->right->getKey() - ptr->getKey())) {
			count += 1;
			desni = ptr->right;
			return count + countCloseParents(desni, n);
		}
		else {
			desni = ptr->right;
			return count + countCloseParents(desni, n);
		}
	}
	else if (root->left) {
		if (n >= (ptr->getKey() - ptr->left->getKey())) {
			count += 1;
			levi = ptr->left;
			return count + countCloseParents(levi, n);
		}
		else {
			levi = ptr->left;
			return count + countCloseParents(levi, n);
		}
	}
	else 
		return 0;
}
int BSTreeInt::countCloseParents(int n) const // JANUAR 2024
{
		return countCloseParents(root, n);
}

void BSTreeInt::deleteLeaves(BSTNodeInt* ptr, BSTNodeInt* ptr_parent, bool isright) // JUN 2024
{
	if (ptr == nullptr) {
		return;
	}
	else if (!ptr->right && !ptr->left) {
		delete ptr;
		if (isright) {
			ptr_parent->right = nullptr;
		}
		else {
			ptr_parent->left = nullptr;
		}
		numOfElements--;
		return;
	}
	else if (ptr->right && ptr->left) {
		deleteLeaves(ptr->right, ptr, true);
		deleteLeaves(ptr->left, ptr, false);
	}
	else if (ptr->right) {
		deleteLeaves(ptr->right, ptr, true);
	}
	else if (ptr->left) {
		deleteLeaves(ptr->left, ptr, false);
	}
	return;

}

void BSTreeInt::deleteLeaves() // JUN 2024
{
	BSTNodeInt* ptr = root;

	if (ptr == nullptr)
		return;

	if (ptr != nullptr && (!ptr->right && !ptr->left)) {
		delete ptr;
		root = nullptr;
		numOfElements--;
		return;
	}

	deleteLeaves(ptr->right, ptr, true);
	deleteLeaves(ptr->left, ptr, false);
}

int BSTreeInt::maxLevel() const // JUN 2024
{
	int currentlevel = 0;
	int nodesincurrentlevel = 1;
	int maxlevel = 0;
	int nodesinmaxlevel = 0;
	BSTNodeInt* ptr = nullptr;

	if (root == nullptr) {
		return -1;
	}
	QueueAsArrayBSTNodeInt queue = QueueAsArrayBSTNodeInt(numOfElements);
	queue.enqueue(root);

	while (!queue.isEmpty()) {
		int nodesinnextlevel = 0;
		for (int i = 0; i < nodesincurrentlevel; i++) {
			ptr = queue.dequeue();

			if (ptr->right) {
				queue.enqueue(ptr->right);
				nodesinnextlevel++;
			}
			if (ptr->left) {
				queue.enqueue(ptr->left);
				nodesinnextlevel++;
			}
		}

		
		if (nodesinmaxlevel < nodesincurrentlevel) {
			nodesinmaxlevel = nodesincurrentlevel;
			maxlevel = currentlevel;
		}
		nodesincurrentlevel = nodesinnextlevel;
		currentlevel++;
		
	}


	return maxlevel;
}

int BSTreeInt::minEvenDiff(BSTNodeInt* ptr, BSTNodeInt*& best, int& minDiff, bool& found) const // JUN 2 2024
{
	int zbirulevom = 0;
	int zbirudesnom = 0;
	int diff = 0;

	if (ptr == nullptr) {
		return 0;
	}
	
	zbirulevom = minEvenDiff(ptr->left, best, minDiff, found);
	zbirudesnom = minEvenDiff(ptr->right, best, minDiff, found);

	diff = abs(zbirudesnom - zbirulevom);

	if (ptr->right && ptr->left && !found) {
		minDiff = diff;
		best = ptr;
		found = true;
	}

	if (ptr->right && ptr->left && diff < minDiff) {
		minDiff = diff;
		best = ptr;
	}

	if (ptr->getKey() % 2 == 0) {
		return ptr->getKey() + zbirulevom + zbirudesnom;
	}
	else {
		return zbirudesnom + zbirulevom;
	} 
}



BSTNodeInt* BSTreeInt::minEvenDiff() const // JUN 2 2024
{
	BSTNodeInt* best = nullptr;
	int minDiff = 0;
	bool found = false;

	minEvenDiff(root, best, minDiff, found);

	return best;
}


void BSTreeInt::populate(int* arData, int n)
{
	for (int i = 0; i < n; i++) {
		add(arData[i]);
	}
}

void BSTreeInt::sumInterval(BSTNodeInt* ptr, int min, int max, int& sum) const // 2. kolok 2024
{
	if (ptr != nullptr) {
		if (ptr->getKey() <= max && ptr->getKey() >= min) {
			sum += ptr->getKey();
		};
		sumInterval(ptr->left, min, max, sum);
		sumInterval(ptr->right, min, max, sum);
	}

}


int BSTreeInt::sumInterval(int min, int max) const // 2. kolok 2024
{
	int sum = 0;
	sumInterval(root, min, max, sum);
	return sum;
}

void BSTreeInt::create(int* vec, int n) // 2. KOLOK 2024 POPR
{
	for (int i = 0; i < n; i++) {
		insert(vec[i]);
	}
}

int BSTreeInt::inorderDistance(int a, int b) const// 2. KOLOK 2024 POPR
{
	bool foundA = false;
	bool foundB = false;
	int length = 0;
	if (a > b) {
		int pom = a;
		a = b;
		b = pom;
	}
	inorderDistance(root, foundA, foundB, a, b, length);
	if (foundA && foundB) {
	return length + 1;
	}
	else {
		return -1;
	}

}

void BSTreeInt::inorderDistance(BSTNodeInt* ptr, bool& foundA, bool& foundB, int a, int b, int& length) const // 2. KOLOK 2024 POPR
{
	if (ptr != nullptr) {
		inorderDistance(ptr->left, foundA, foundB, a, b, length);
		if (ptr->getKey() == a) {
			foundA = true;
		}
		if (ptr->getKey() == b) {
			foundB = true;
		}
		if (foundA && !foundB) {
			length++;
		}
		inorderDistance(ptr->right, foundA, foundB, a, b, length);
	}
}

BSTNodeInt* BSTreeInt::maxDiffOfEvenNodes() const
{
	BSTNodeInt* ptr = root;
	BSTNodeInt* rezultat = nullptr;
	int max = 0;
	maxDiffOfEvenNodes(ptr, max, rezultat);
	return rezultat;
}

int BSTreeInt::maxDiffOfEvenNodes(BSTNodeInt* ptr, int& max, BSTNodeInt*& rezultat) const
{
	int ud = 0;
	int ul = 0;
	int diff = 0;
	if (!ptr) {
		return 0;
	}


	ul = maxDiffOfEvenNodes(ptr->left, max, rezultat);
	ud = maxDiffOfEvenNodes(ptr->right, max, rezultat);

	diff = abs(ul - ud);

	if (max <= diff) {
		max = diff;
		rezultat = ptr;
	}
	

	if (ptr->getKey() % 2 == 0) {
		return 1 + ul + ud;
	}
	return ul + ud;
}

int BSTreeInt::sumUpThePath(BSTNodeInt* root, int destKey)
{
	BSTNodeInt* ptr = root;
	int sum = 0;
	if (!ptr) {
		return -1;
	}
	sumUpThePath(root, destKey, sum);
	return sum;


}

int BSTreeInt::sumUpThePath(BSTNodeInt* ptr1, int destKey, int& sum)
{
	BSTNodeInt* ptr = ptr1;

	sum += ptr->getKey();

	if (destKey == ptr->getKey()) {
		return sum;
	}
	if (ptr->right && destKey > ptr->getKey()) {
		sumUpThePath(ptr->right, destKey, sum);
	}
	if (ptr->left && destKey < ptr->getKey()) {
		sumUpThePath(ptr->left, destKey, sum);
	}
	if (destKey > ptr->getKey() && !ptr->right) {
		sum = -1;
	}
	if (destKey < ptr->getKey() && !ptr->left) {
		sum = -1;
	}
	

}

BSTNodeInt* BSTreeInt::findDeepestLeaf(BSTNodeInt* root) const
{
	if (!root) {
	return nullptr;
	}
	BSTNodeInt* rez = nullptr;
	int depth = 0;
	int maxdepth = 0;
	findDeepestLeaf(root, rez, depth, maxdepth);

	return rez;

}


void BSTreeInt::findDeepestLeaf(BSTNodeInt* ptr, BSTNodeInt*& rez, int& depth, int& maxdepth) const
{
	QueueAsArrayBSTNodeInt q(numOfElements);
	BSTNodeInt* a = nullptr;
	q.enqueue(ptr);
	int elincurrent = 1;
	int elinnext = 0;
	while (!q.isEmpty()) {
		for (int i = 0; i < elincurrent; i++) {
			a = q.dequeue();

			if (a->left) {
				elinnext++;
				q.enqueue(a->left);
			}
			if (a->right) {
				elinnext++;
				q.enqueue(a->right);
			}
			if (!a->right && !a->left && depth>=maxdepth) {
				maxdepth = depth;
				rez = a;
			}
		}
		elincurrent = elinnext;
		elinnext = 0;
		depth++;

	}
}

BSTNodeInt* BSTreeInt::getDeepestEvenParent(BSTNodeInt* root)
{
	BSTNodeInt* rez = nullptr;
	if (root == nullptr || (root->right == nullptr && root->left == nullptr)) {
		return nullptr;
	}
	getDeepestEvenParent(root, rez);

	return rez;
}

void BSTreeInt::getDeepestEvenParent(BSTNodeInt* root, BSTNodeInt*& rez)
{
	QueueAsArrayBSTNodeInt q(numOfElements);
	BSTNodeInt* ptr = nullptr;
	q.enqueue(root);
	int depth = 0;
	int maxdepth = 0;
	int nodesincurrentlevel = 1;
	int nodesinnextlevel = 0;
	while (!q.isEmpty()) {
		for (int i = 0; i < nodesincurrentlevel; i++) {
			ptr = q.dequeue();
			if (ptr->getKey() % 2 == 0 && (ptr->right != nullptr || ptr->left != nullptr) && depth >= maxdepth) {
				maxdepth = depth;
				rez = ptr;
			}

			if (ptr->right) {
				q.enqueue(ptr->right);
				nodesinnextlevel++;
			}
			if (ptr->left) {
				q.enqueue(ptr->left);
				nodesinnextlevel++;
			}
		
		}
		depth++;
		nodesincurrentlevel = nodesinnextlevel;
		nodesinnextlevel = 0;
	}

}

int BSTreeInt::maxLevelCount()
{
	QueueAsArrayBSTNodeInt q(numOfElements);
	BSTNodeInt* ptr = nullptr;
	q.enqueue(root);
	int nodesincurrent = 1;
	int nodesinnext = 0;
	int level = 0;
	int maxlevel = 0;
	int maxnodes = 0;
	while (!q.isEmpty()) {
		for (int i = 0; i < nodesincurrent; i++) {
			ptr = q.dequeue();
			if (nodesincurrent > maxnodes) {
				maxlevel = level;
				maxnodes = nodesincurrent;
			}

			if (ptr->left) {
				q.enqueue(ptr->left);
				nodesinnext++;
			}
			if (ptr->right) {
				q.enqueue(ptr->right);
				nodesinnext++;
			}
		}
		nodesincurrent = nodesinnext;
		nodesinnext = 0;
		level++;
	}


	return maxlevel;
}


