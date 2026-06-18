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