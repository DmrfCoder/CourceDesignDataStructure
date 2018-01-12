#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

#include "AdtGraph.h"

/*
 * 算法思路：
 *   问题一：实际上就是求从（0,0）点出发到其他所有可达点的最短路径
 *   问题二：求从（0,0）点出发的最小生成树
 */


void Qone(MGraph &G);

void Qtwo(MGraph G);

void GetData(vector<Node> &v, int n);

void Prim(MGraph G);

void ShortestPath(MGraph G);

int main() {


    cout << "请输入节点个数：" << endl;
    int n;
    cin >> n;

    vector<Node> v;
    GetData(v, n);

    MGraph G;

    CreateUDN(G, v);

    /*   for (int i = 1; i <= 100; ++i) {
           for (int j = 1; j <= 100; ++j) {
               cout << G.arcs[i][j].adj << " ";
           }
           cout << endl;
      }*/



    Qone(G);
    //Qtwo(G);
    //ShortestPath(G);
    Prim(G);
    return 0;
}


void GetData(vector<Node> &v, int n) {
    ifstream in("/home/dmrf/文档/DataStructure/CourseDesign/NetData.txt");

    if (!in.is_open()) {
        cout << "文件打开失败！" << endl;
        return;
    }

    Node node1;
    node1.y = 0;
    node1.x = 0;
    node1.code = 0;
    v.push_back(node1);

    while (!in.eof() && n > 0) {
        Node node;
        in >> node.code >> node.x >> node.y;
        v.push_back(node);
        n--;
    }

    if (n >= 48) {
        v.pop_back();
    }

    in.close();
    cout << "文件读取成功～" << endl;
}


void Qone(MGraph &G) {
    int len[G.vexnum];
    int road[G.vexnum];
    bool flag[G.vexnum];
    for (int i = 0; i < G.vexnum; ++i) {
        len[i] = G.arcs[0][i].adj;
        flag[i] = false;
    }
    flag[0] = true;


    int min = 1000000;
    int index = 0;

    while (true) {
        min = 1000000;
        index = 0;

        for (int i = 0; i < G.vexnum; ++i) {//找到从点1出发的最短边（该边一定是最短路径的一部分）
            if (len[i] < min && !flag[i] && len[i] != -1) {
                min = len[i];
                index = i;
            }
        }

        if (index == 0) {
            break;
        }
        flag[index] = true;

        for (int j = 0; j < G.vexnum; ++j) {
            if (!flag[j] && G.arcs[index][j].adj != -1) {//如果点j没有归入最短点的集合而且点index到点j有路径

                if (len[j] > len[index] + G.arcs[index][j].adj || len[j] == -1) {


                    len[j] = len[index] + G.arcs[index][j].adj;

                    road[j] = index;

                }
            }
        }

    }

    int si = G.vexnum;

    int deletenum = 0;
    cout << "最短路径结果如下：" << endl;
    for (int k = 1; k < si; ++k) {

        if (!flag[k]) {


            cout << k << "无法实现传输,该点将被剔除" << endl;
            deletenum++;
            DeleteVex(G, k);
        } else {
            cout << "源点到" << k;
            cout << "最短距离为" << len[k];
            cout << "路径为：源点--";
            int temp[500];
            int is = 0;

            temp[is++] = k;

            int pr = road[k];
            while (pr != 0) {
                temp[is++] = pr;
                pr = road[pr];
            }
            for (int i = is - 1; i > 0; --i) {
                cout << temp[i] << "--";
            }
            cout << temp[0] << endl;


        }
    }

    cout << "共有" << deletenum << "个点被剔除" << endl;
}


void Prim(MGraph G) {

    int min;
    vector<int> a;
    vector<int> b;
    vector<int> minvalue;
    vector<int> index;

    index.push_back(1);

    a.push_back(1);
    bool flag[G.vexnum + 1];

    for (int k = 1; k <= G.vexnum; ++k) {
        flag[k] = false;
    }
    int min_index;

    for (int i = 2; i <= G.vexnum; ++i) {
        if (G.arcs[1][i].adj != -1) {
            min = G.arcs[1][i].adj;
            min_index = i;
            break;
        }

    }

    for (int j = min_index + 1; j <= G.vexnum; ++j) {
        if (G.arcs[1][j].adj != -1 && G.arcs[1][j].adj < min) {
            min = G.arcs[1][j].adj;
            min_index = j;
        }
    }

    flag[1] = true;
    flag[min_index] = true;
    b.push_back(min_index);
    minvalue.push_back(min);
    index.push_back(min_index);

    while (index.size() != G.vexnum) {
        int n = index[0];
        int f = 0;
        min = 1000000;

        for (int l = 0; l < index.size(); ++l) {

            for (int k = 1; k <= G.vexnum; ++k) {
                if (G.arcs[index[l]][k].adj != -1 && G.arcs[index[l]][k].adj < min && !flag[k]) {
                    min = G.arcs[index[l]][k].adj;
                    min_index = k;
                    f = l;
                }
            }
        }

        flag[min_index] = true;
        int aa = a.front();
        int bb = b.front();
        a.push_back(index[f]);
        b.push_back(min_index);
        index.push_back(min_index);
        minvalue.push_back(min);


    }


    int va = 0;
    for (int m = 0; m < minvalue.size(); ++m) {
        va += minvalue[m];
    }


    cout << "最小能耗：" << va << endl;
    cout << "建立以下" << a.size() << "条网络：" << endl;
    for (int i1 = 0; i1 < a.size(); ++i1) {
        cout << "点" << a[i1] << "与点" << b[i1] << endl;
    }

    /* for (int j1 = 0; j1 < index.size(); ++j1) {
         cout << index[j1] << " ";
     }
 */
}

void Qtwo(MGraph G) {

    int min;
    vector<int> a;//起点集合
    vector<int> b;//终点集合
    vector<int> minvalue;//最小值集合
    vector<int> index;//最小点集合

    index.push_back(1);

    a.push_back(1);
    bool flag[G.vexnum + 1];

    for (int k = 1; k <= G.vexnum; ++k) {
        flag[k] = false;
    }
    int min_index;

    for (int i = 2; i <= G.vexnum; ++i) {
        if (G.arcs[1][i].adj != -1) {
            min = G.arcs[1][i].adj;
            min_index = i;
            break;
        }

    }

    for (int j = min_index + 1; j <= G.vexnum; ++j) {
        if (G.arcs[1][j].adj != -1 && G.arcs[1][j].adj < min) {
            min = G.arcs[1][j].adj;
            min_index = j;
        }
    }

    flag[1] = true;
    flag[min_index] = true;
    b.push_back(min_index);
    minvalue.push_back(min);
    index.push_back(min_index);

    while (index.size() != G.vexnum) {
        int n = index[0];
        int f = 0;
        min = 1000000;
        bool br = false;

        for (int l = 0; l < index.size(); ++l) {

            for (int k = 1; k <= G.vexnum; ++k) {
                if (G.arcs[index[l]][k].adj != -1 && G.arcs[index[l]][k].adj < min && !flag[k]) {
                    br = true;
                    min = G.arcs[index[l]][k].adj;
                    min_index = k;
                    f = l;
                }
            }
        }

        if (!br) {
            cout << "不存在你想要的" << endl;
            break;
        }
        flag[min_index] = true;
        a.push_back(index[f]);
        b.push_back(min_index);
        index.push_back(min_index);
        minvalue.push_back(min);


    }


    int va = 0;
    for (int m = 0; m < minvalue.size(); ++m) {
        va += minvalue[m];
    }

    cout << "最小能耗为：" << va << endl;
    cout << "建立以下" << a.size() << "条路径：" << endl;
    for (int i1 = 0; i1 < a.size() - 1; ++i1) {
        cout << a[i1] << "--" << b[i1] << endl;
    }

    /* for (int j1 = 0; j1 < index.size(); ++j1) {
         cout << index[j1] << " ";
     }*/

}