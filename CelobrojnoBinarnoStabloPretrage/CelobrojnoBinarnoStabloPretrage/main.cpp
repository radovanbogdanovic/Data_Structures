//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//     Main januar 2024
//    BSTreeInt tree;
//    int values[] = { 10, 5, 15, 3, 8, 12, 20 };
//
//    for (int value : values)
//        tree.insert(value);
//
//    tree.inorder();
//    cout << endl;
//    cout << "Broj bliskih roditelja za n=5: "
//        << tree.countCloseParents(5) << endl;
//
//    int a;
//    cin >> a;
//    return 0;
//
//
//} MAIN JAN 2024

//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//class TestBTreeInt : public BSTreeInt
//{
//public:
//    void makeExample()
//    {
//        root = new BSTNodeInt(10);
//        root->left = new BSTNodeInt(5);
//        root->right = new BSTNodeInt(15);
//        root->left->left = new BSTNodeInt(3);
//        root->left->right = new BSTNodeInt(8);
//        root->right->right = new BSTNodeInt(20);
//        numOfElements = 6;
//    }
//};
//
//int main()
//{
//    TestBTreeInt tree;
//    tree.makeExample();
//
//    cout << "Pre brisanja: ";
//    tree.breadthFirstSearch();
//    cout << "\nNivo sa najvise cvorova: " << tree.maxLevel() << endl;
//
//    tree.deleteLeaves();
//
//    cout << "Posle brisanja listova: ";
//    tree.breadthFirstSearch();
//    cout << "\nNivo sa najvise cvorova: " << tree.maxLevel() << endl;
//
//    system("pause");
//    return 0;
//} MAIN JUN 2024
//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//class TestBTreeInt : public BSTreeInt
//{
//public:
//    void makeExample()
//    {
//        root = new BSTNodeInt(10);
//        root->left = new BSTNodeInt(6);
//        root->right = new BSTNodeInt(15);
//        root->left->left = new BSTNodeInt(2);
//        root->left->right = new BSTNodeInt(14);
//        root->right->left = new BSTNodeInt(12);
//        root->right->right = new BSTNodeInt(29);
//        numOfElements = 7;
//    }
//};
//
//int main()
//{
//    TestBTreeInt tree;
//    tree.makeExample();
//
//    BSTNodeInt* result = tree.minEvenDiff();
//
//    if (result != nullptr)
//        cout << "Najbolji cvor: " << result->key << endl;
//    else
//        cout << "Stablo je prazno." << endl;
//
//    return 0;
//} MAIN JUN2 2024
//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    BSTreeInt tree;
//    int values[] = { 10, 5, 8, 14, 12, 16, 3, 11, 2, 7, 15, 7, 8, 20};
//    int n = 14;
//
//    tree.populate(values, n);
//
//    cout << "Inorder: ";
//    tree.inorder();
//    cout << "\nSuma intervala [4, 15]: "
//        << tree.sumInterval(4, 15) << endl;
//
//    return 0;
//} MAIN 2. KOLOK 2024
//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    BSTreeInt tree;
//    int values[] = { 10, 5, 15, 3, 8, 12, 20 };
//    int n = sizeof(values) / sizeof(values[0]);
//
//    tree.create(values, n);
//
//    cout << "Inorder: ";
//    tree.inorder();
//    cout << "\nRastojanje 5-15: "
//        << tree.inorderDistance(5, 15) << endl;
//    cout << "Rastojanje 5-99: "
//        << tree.inorderDistance(5, 99) << endl;
//
//    return 0;
//} MAIN 2. KOLOK 2024 POPRAVNI
//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    BSTreeInt tree;
//    int values[] = {
//        10, 5, 20, 2, 7, 15, 30,
//        12, 18, 25, 40, 22, 27
//    };
//
//    for (int value : values)
//        tree.insert(value);
//
//    BSTNodeInt* result = tree.maxDiffOfEvenNodes();
//
//    cout << "Cvor sa najvecom razlikom: "
//        << (result != nullptr ? result->getKey() : -1)
//        << endl;
//
//    BSTreeInt emptyTree;
//    cout << boolalpha;
//    cout << "Prazno stablo vraca nullptr: "
//        << (emptyTree.maxDiffOfEvenNodes() == nullptr)
//        << endl;
//
//    return 0;
//} MAIN DECEMBAR 2026
//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    BSTreeInt tree;
//    int values[] = { 50, 30, 70, 20, 40, 60, 80 };
//
//    for (int value : values)
//        tree.insert(value);
//
//    cout << "Suma do 40: "
//        << tree.sumUpThePath(tree.search(50), 40)
//        << endl;
//
//    cout << "Suma do 99: "
//        << tree.sumUpThePath(tree.search(50), 99)
//        << endl;
//
//    return 0;
//} MAIN JANUAR 2026
//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    BSTreeInt tree;
//    int values[] = { 10, 5, 15, 3, 8, 2, 1 };
//
//    for (int value : values)
//        tree.insert(value);
//
//    BSTNodeInt* result = tree.findDeepestLeaf(tree.search(10));
//
//    if (result != nullptr)
//        cout << "Najdublji list: " << result->key << endl;
//    else
//        cout << "Stablo je prazno." << endl;
//
//    return 0;
//} April 2025
//#include "BSTreeInt.h"
//#include <iostream>
//using namespace std;
//
//int main()
//{
//    BSTreeInt tree;
//    int values[] = { 10, 5, 16, 3, 8, 14, 20, 7 };
//
//    for (int value : values)
//        tree.insert(value);
//
//    BSTNodeInt* result =
//        tree.getDeepestEvenParent(tree.search(10));
//
//    if (result != nullptr)
//        cout << "Najdublji paran roditelj: " << result->key << endl;
//    else
//        cout << "Takav cvor ne postoji." << endl;
//
//    return 0;
//} oktrobar2 2025
#include "BSTreeInt.h"
#include <iostream>
using namespace std;

class TestBTreeInt : public BSTreeInt
{
public:
    void makeExample()
    {
        root = new BSTNodeInt(10);
        root->left = new BSTNodeInt(5);
        root->right = new BSTNodeInt(15);
        root->left->left = new BSTNodeInt(3);
        root->left->right = new BSTNodeInt(8);
        root->right->left = new BSTNodeInt(12);
        root->right->right = new BSTNodeInt(20);
        numOfElements = 7;
    }
};

int main()
{
    TestBTreeInt tree;
    tree.makeExample();

    tree.breadthFirstSearch();
    cout << "\nNivo sa najvise cvorova: "
        << tree.maxLevelCount() << endl;

    return 0;
}