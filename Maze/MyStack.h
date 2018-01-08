//
// Created by dmrf on 17-11-11.
//

#ifndef INC_1_MYSTACK_H
#define INC_1_MYSTACK_H
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10


#include <iostream>

using namespace std;
typedef struct {
    int x;
    int y;
}Loc;


typedef struct {
    Loc *base;//栈底
    Loc *top;//栈顶
    int stacksize;//栈已分配的存储空间
} SqStack;

bool InitStack(SqStack &S) {
    S.base = new Loc[STACK_INIT_SIZE];
    if (S.base == NULL) {
        cout << "分配空间失败！" << endl;
        return false;
    }

    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    cout << "初始化栈成功～" << endl;
    return true;

}

bool DestroyStack(SqStack &S) {

    if (S.base == NULL) {
        cout << "该栈不存在，无法销毁！" << endl;
        return false;
    }

    delete S.base;
    S.base = NULL;
    S.top = NULL;
    S.stacksize = 0;
    cout << "销毁成功～" << endl;
    return true;
}

bool ClearStack(SqStack &S) {

    if (S.base == NULL) {
        cout << "该栈不存在，无法清空！" << endl;
        return false;
    }

    S.top = S.base;
    cout << "清空成功～" << endl;
    return true;
}

bool StackEmpty(SqStack S) {
    if (S.base == NULL) {
        cout << "该栈不存在，无法判空！" << endl;
        return false;
    }
    if (S.top != S.base) {
       // cout << "该栈不为空～" << endl;
        return false;
    }
   // cout << "该栈为空～" << endl;
    return true;
}

int StackLength(SqStack S) {
    if (S.base == NULL) {
        cout << "该栈不存在，无法获取长度！" << endl;
        return -1;
    }

    int length = (S.top - S.base);
    cout << "当前栈的长度为：" << length << endl;
    return length;
}

bool GetTop(SqStack S, Loc &e) {
    if (S.base == NULL) {

        cout << "该栈不存在，无法获取栈顶！" << endl;
        return false;
    }
    if (S.base == S.top) {

        cout << "该栈为空，无法获取栈顶！" << endl;
        return false;
    }

    e = *(S.top - 1);
    return true;
}

bool Push(SqStack &S, Loc e) {
    if (S.base == NULL) {

        cout << "该栈不存在，无法PUSH！" << endl;
        return false;
    }
    if ((S.top - S.base) >= S.stacksize) {
        S.base = static_cast<Loc *>(realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(Loc)));
        if (S.base == NULL) {
            cout << "分配空间失败！无法Push元素！" << endl;
            return false;
        }
        S.top = S.base + STACKINCREMENT;
        S.stacksize += STACKINCREMENT;
    }

    *S.top = e;
    S.top++;
  //  cout <<"push:"<< "(" << e.x << "," << e.y << ")" << endl;
    return true;
}

bool Pop(SqStack &S, Loc &e) {
    if (S.base == NULL) {
        cout << "该栈不存在，无法弹出元素！" << endl;
        return false;
    }
    if (S.base == S.top) {
        cout << "该栈为空，无法弹出元素！" << endl;
        return false;
    }
    S.top--;
    e = *S.top;
   // cout <<"pop:"<< "(" << e.x << "," << e.y << ")" << endl;
    return true;
}

bool StackTraverse(SqStack S) {
    if (S.base == NULL) {
        cout << "该栈不存在，无法遍历！" << endl;
        return false;
    }
    if (S.base == S.top) {
        cout << "该栈为空，无法遍历！" << endl;
        return false;
    }

    cout << "栈S从栈顶到栈底的遍历情况如下：" << endl;
    Loc *i = S.top - 1;
    while (i - S.base >= 0) {
        i--;
    }

    cout << endl;
    return true;
}

#endif //INC_1_MYSTACK_H
