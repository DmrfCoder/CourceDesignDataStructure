//
// Created by dmrf on 17-11-20.
//

#ifndef INC_1_BITREE_H
#define INC_1_BITREE_H
#define TElemType int

#include <queue>
#include <stack>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

typedef struct {
    char a;
    char b;
    int v;
} Vex;

typedef struct BiNode {
    struct BiNode *lchild;
    struct BiNode *rchild;
    struct BiNode *parent;
    int v = 0;
    char c = NULL;
} BiNode, *BiTree;

int Depth(BiTree biTree);

void LevelOrderTraversePrint(BiTree biTree, int depth);

void InitBitree(BiTree &biTree) {
    biTree = new BiNode();
    biTree->lchild = NULL;
    biTree->rchild = NULL;
    biTree->parent = NULL;
    cout << "初始化成功～" << endl;
}

void DestroyBiTree(BiTree biTree) {

    if (biTree == NULL) {
        return;
    }
    if (biTree->lchild != NULL) {
        DestroyBiTree(biTree->lchild);
    }

    if (biTree->rchild != NULL) {
        DestroyBiTree(biTree->rchild);
    }
    free(biTree);
}


void GetCode(BiTree biTree, string s, ofstream &code) {//先序遍历
    if (biTree == NULL) {
        cout << "该树为空，无法遍历！" << endl;
    }

    if (biTree->c != NULL) {
        int cs=biTree->c;
        code<<cs<<" "<<s<<endl;
        cout<<cs<<" "<<s<<endl;
        /*if (biTree->c == 32) {
            cout << " " << " " << s << endl;
            code << " " << " " << s << endl;
        } else{
            cout << biTree->c << " " << s << endl;
            code << biTree->c << " " << s << endl;
        }*/

    }
    if (biTree->lchild != NULL) {
        GetCode(biTree->lchild, s + "0", code);

    }

    if (biTree->rchild != NULL) {
        GetCode(biTree->rchild, s + "1", code);
    }

    code.flush();
}


#endif //INC_1_BITREE_H

