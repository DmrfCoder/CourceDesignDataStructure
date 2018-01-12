#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "MyStack.h"

using namespace std;

/*
 * 1代表可走，0代表没路
 */

int main() {
    fstream in("/home/dmrf/文档/DataStructure/CourseDesign/maze.txt");
    if (!in.is_open()) {
        cout << "文件打开失败！" << endl;
        return 0;
    }


    vector<int> data;
    int k;
    while (!in.eof()) {
        in >> k;
        data.push_back(k);
    }

    in.close();
    data.pop_back();


    int num = sqrt(data.size());
    int d[num + 3][num + 3];

    int x, y;
    x = y = 1;


    for (int j = 1; j <= num + 2; ++j) {
        for (int i = 1; i <= num + 2; ++i) {
            if (j == 1 || j == num + 2 || i == 1 || i == num + 2) {
                d[j][i] = 0;
            } else {
                d[j][i] = data[(j - 2) * num + i - 2];
            }

        }
    }

    cout << "文件中的迷宫设置如下：" << endl;
    for (int j = 2; j < num + 2; ++j) {
        for (int i = 2; i < num + 2; ++i) {
            if (d[j][i] == 1) {
                cout << "*" << " ";
            } else {
                cout << "#" << " ";
            }
        }
        cout << endl;

    }


    SqStack S;
    InitStack(S);

    Loc bebin;
    Loc end;

    cout << "请输入入口点坐标和出口点坐标：" << endl;
    cin >> bebin.x >> bebin.y >> end.x >> end.y;
    bebin.x++;
    bebin.y++;
    end.x++;
    end.y++;

    Loc cur;

    Push(S, bebin);

    d[bebin.x][bebin.y] = 2;

    int stapnum = 1;

    while (!StackEmpty(S)) {
        GetTop(S, cur);

        if (cur.x == end.x && cur.y == end.y) {
            cout << "success" << endl;
            break;
        } else {
            Loc temp;
            if (d[cur.x + 1][cur.y] != 0 && d[cur.x + 1][cur.y] != 2) {
                d[cur.x + 1][cur.y] = 2;
                temp.x = cur.x + 1;
                temp.y = cur.y;
                Push(S, temp);
            } else if (d[cur.x][cur.y + 1] != 0 && d[cur.x][cur.y + 1] != 2) {
                d[cur.x][cur.y + 1] = 2;
                temp.x = cur.x;
                temp.y = cur.y + 1;
                Push(S, temp);
            } else if (d[cur.x - 1][cur.y] != 0 && d[cur.x - 1][cur.y] != 2) {
                d[cur.x - 1][cur.y] = 2;
                temp.x = cur.x - 1;
                temp.y = cur.y;
                Push(S, temp);
            } else if (d[cur.x][cur.y - 1] != 0 && d[cur.x][cur.y - 1] != 2) {
                d[cur.x][cur.y - 1] = 2;
                temp.x = cur.x;
                temp.y = cur.y - 1;
                Push(S, temp);
            } else {
                Loc t;
                Pop(S, t);
            }

        }


    }

    while (!StackEmpty(S)) {
        Loc c;
        Pop(S, c);
        // cout << "(" << c.x << "," << c.y << ")" << endl;
        d[c.x][c.y] = 6;
    }


    cout<<"走出迷宫的路线为："<<endl;
    for (int j = 2; j < num + 2; ++j) {
        for (int i = 2; i < num + 2; ++i) {
            if (d[j][i] == 1) {
                cout << "*" << " ";
            } else if (d[j][i] == 0) {
                cout << "#" << " ";
            } else if (d[j][i] == 2) {
                cout << "$" << " ";
            } else {
                cout << "^" << " ";
            }
        }
        cout << endl;

    }
    return 0;
}


