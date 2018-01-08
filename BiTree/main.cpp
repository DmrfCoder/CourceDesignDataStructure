#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "BiTree.h"

typedef struct {
    char m;
    char p;
    int s;
    int d;
} Node;
void Test1();
void Test2();
int main() {

    Test1();
    cout<<endl;
    Test2();
    return 0;
}


void Test1() {
    fstream in("/home/dmrf/文档/DataStructure/CourseDesign/Tree.txt");
    if (!in.is_open()) {
        cout << "文件打开失败！" << endl;
        return;
    }
    vector<Node> v;
    char m, p, s, d;
    BiTree biTree;
    InitBitree(biTree);
    while (!in.eof()) {

        Node n;
        in >> n.m >> n.p >> n.s >> n.d;
        v.push_back(n);
    }

    for (int i = 0; i < v.size() - 1; ++i) {
        if (i == 0) {
            biTree->c = v[i].m;
            biTree->data = v[i].d;
        } else {
            BiTree biTree1;
            InitBitree(biTree1);
            biTree1->data = v[i].d;
            biTree1->c = v[i].m;
            InstertChild(biTree, v[i].p, v[i].s, biTree1);
        }

    }

    cout << "构建树成功～" << endl;


    cout << "层次遍历递归实现：" << endl;
    LevelOrderTraverse(biTree);

    cout << endl;
    cout << "层次遍历非递归实现：" << endl;
    LevelOrderTraverse2(biTree);


    cout << endl;
    cout << "中序遍历递归实现：" << endl;
    InOrderTraverse(biTree);

    cout << endl;
    cout << "中序遍历非递归实现：" << endl;
    InOrderTraverse2(biTree);

    cout << endl;
    cout << "后序遍历递归实现：" << endl;
    PostOrderTraverse(biTree);

    cout << endl;
    cout << "后序遍历非递归实现：" << endl;
    PostOrderTraverse2(biTree);

    cout << endl;
    cout << "先序遍历递归实现：" << endl;
    PreOrderTraverse(biTree);


    cout << endl;
    cout << "先序遍历非递归实现：" << endl;
    PreOrderTraverse2(biTree);


    cout << endl;
    cout << "该二叉树的高度为：";
    cout << Depth(biTree) << endl;

    cout << "该二叉树的宽度为：";
    cout << Width(biTree) << endl;


    cout << "该二叉树的节点个数为：" << biTree->node_count << endl;


    string ps;
    if (!IsBiSort(biTree)) {
        ps = "不是";
    } else {
        ps = "是";
    }
    cout << "该二叉树" << ps << "二叉排序树" << endl;


}


void Test2() {
    fstream in("/home/dmrf/文档/DataStructure/CourseDesign/Tree2.txt");
    if (!in.is_open()) {
        cout << "文件打开失败！" << endl;
        return;
    }
    vector<Node> v;
    char m, p, s, d;
    BiTree biTree;
    InitBitree(biTree);
    while (!in.eof()) {

        Node n;
        in >> n.m >> n.p >> n.s >> n.d;
        v.push_back(n);
    }

    for (int i = 0; i < v.size() - 1; ++i) {
        if (i == 0) {
            biTree->c = v[i].m;
            biTree->data = v[i].d;
        } else {
            BiTree biTree1;
            InitBitree(biTree1);
            biTree1->data = v[i].d;
            biTree1->c = v[i].m;
            InstertChild(biTree, v[i].p, v[i].s, biTree1);
        }

    }

    cout << "构建树成功～" << endl;


    cout << "层次遍历递归实现：" << endl;
    LevelOrderTraverse(biTree);

    cout << endl;
    cout << "层次遍历非递归实现：" << endl;
    LevelOrderTraverse2(biTree);


    cout << endl;
    cout << "中序遍历递归实现：" << endl;
    InOrderTraverse(biTree);

    cout << endl;
    cout << "中序遍历非递归实现：" << endl;
    InOrderTraverse2(biTree);

    cout << endl;
    cout << "后序遍历递归实现：" << endl;
    PostOrderTraverse(biTree);

    cout << endl;
    cout << "后序遍历非递归实现：" << endl;
    PostOrderTraverse2(biTree);

    cout << endl;
    cout << "先序遍历递归实现：" << endl;
    PreOrderTraverse(biTree);


    cout << endl;
    cout << "先序遍历非递归实现：" << endl;
    PreOrderTraverse2(biTree);


    cout << endl;
    cout << "该二叉树的高度为：";
    cout << Depth(biTree) << endl;

    cout << "该二叉树的宽度为：";
    cout << Width(biTree) << endl;


    cout << "该二叉树的节点个数为：" << biTree->node_count << endl;


    string ps;
    if (!IsBiSort(biTree)) {
        ps = "不是";
    } else {
        ps = "是";
    }
    cout << "该二叉树" << ps << "二叉排序树" << endl;


}