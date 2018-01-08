//
// Created by dmrf on 17-12-6.
//

#ifndef INC_1_ADTGRAPH_H
#define INC_1_ADTGRAPH_H

#define MAX_VERTEX_NUM 500

#include <math.h>
#include <iostream>
#include <queue>

using namespace std;
typedef enum {
    DG, DN, UDG, UDN//有向图 有向网 无向图 无向网
} GraphKind;

typedef struct ArcCell {
    double adj;//边的关系类型，无权图值为0或1，有权图为权值
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
    int vexs[MAX_VERTEX_NUM];//用来存储顶点
    AdjMatrix arcs;//用来存储边
    int vexnum, arcnum;//顶点数和边数
    int graphKind;//图的类型
} MGraph;

typedef struct {
    int code;
    int x;
    int y;
} Node;

bool Visited[MAX_VERTEX_NUM];

bool CreateDG(MGraph &G);

bool CreateDN(MGraph &G);

bool CreateUDG(MGraph &G);

bool CreateUDN(MGraph &G, vector<Node> v);

int LocateVex(MGraph g, int a);

void DFS(MGraph G, int v);

//创建图
bool CreateGraph(MGraph &G) {
    cout << "请输入图的类型（0-DG 1-DN 2-UDG 3-UDN）：" << endl;
    cin >> G.graphKind;

    switch (G.graphKind) {
        case DG:
            return CreateDG(G);
            break;
        case DN:
            return CreateDN(G);
            break;
        case UDG:
            return CreateUDG(G);
            break;
        case UDN:
            //return CreateUDN(G);
            break;
        default:
            cout << "图的类型输入错误！" << endl;
            return false;
    }
}

//销毁图
bool DestroyGraph(MGraph &G) {
    return true;
}

//寻找图中a点的位置
int LocateVex(MGraph G, int a) {

    for (int i = 1; i <= G.vexnum; ++i) {

        if (a == G.vexs[i]) {
            return i;
        }
    }

    return -1;
}

//返回下标为l的点的值
char GetVex(MGraph G, int l) {
    if (l <= G.vexnum && l >= 1) {
        return G.vexs[l];
    } else {
        cout << "所获取的点的下标不合法！" << endl;
        return -1;
    }

}

//设置下标为l的顶点的值为v
bool PutVex(MGraph &G, int l, char v) {
    if (l <= G.vexnum && l >= 1) {
        G.vexs[l] = v;
        cout << "设置坐标" << v << "成功" << endl;
        return true;
    } else {
        cout << "所设置的点的下标不合法！" << endl;
        return false;
    }
}

//返回v的第一个邻接顶点
char FirstAdjVex(MGraph G, char v) {
    int i = LocateVex(G, v);
    if (i < 1 || i > G.vexnum) {
        cout << v << "不在图中！" << endl;
        return NULL;
    } else {
        for (int j = 1; j < G.vexnum; ++j) {
            if (G.arcs[i][j].adj != -1) {
                //cout << v << "的第一个邻接顶点是" << G.vexs[j] << endl;
                return G.vexs[j];
            }
        }
    }

    cout << v << "没有邻顶点～" << endl;
    return NULL;
}

//返回v的第一个邻接顶点
int FirstAdjVex2(MGraph G, char v) {
    int i = LocateVex(G, v);
    if (i < 1 || i > G.vexnum) {
        cout << v << "不在图中！" << endl;
        return NULL;
    } else {
        for (int j = 1; j < G.vexnum; ++j) {
            if (G.arcs[i][j].adj != -1) {
                //cout << v << "的第一个邻接顶点是" << G.vexs[j] << endl;
                return j;
            }
        }
    }

    // cout << v << "没有邻顶点～" << endl;
    return -1;
}

//u是v的一个邻接点，寻找v的下一个邻接点并返回
char NextAdjVex(MGraph G, char v, char u) {
    int i = LocateVex(G, v);
    if (i < 1 || i > G.vexnum) {
        cout << v << "不在图中！" << endl;
        return NULL;
    } else {
        int j = LocateVex(G, u);
        if (j == -1) {
            cout << u << "不在图中！" << endl;
            return NULL;
        }
        if (G.arcs[i][j].adj == -1) {
            cout << v << "和" << u << "不邻接！" << endl;
        } else {
            for (int k = j + 1; k < G.vexnum; ++k) {
                if (G.arcs[i][k].adj != 0 && G.arcs[i][k].adj != -1) {
                    return G.vexs[k];
                }
            }

            cout << "没有下一个临邻接点～" << endl;
            return NULL;
        }
    }
}

//u是v的一个邻接点，寻找v的下一个邻接点并返回
int NextAdjVex2(MGraph G, char v, char u) {
    int i = LocateVex(G, v);
    if (i < 1 || i > G.vexnum) {
        cout << v << "不在图中！" << endl;
        return NULL;
    } else {
        int j = LocateVex(G, u);
        if (j == -1) {
            // cout << u << "不在图中！" << endl;
            return -1;
        }
        if (G.arcs[i][j].adj == -1) {
            cout << v << "和" << u << "不邻接！" << endl;
        } else {
            for (int k = j + 1; k <= G.vexnum; ++k) {
                if (G.arcs[i][k].adj != 0 && G.arcs[i][k].adj != -1) {
                    return k;
                }
            }

            //   cout << "没有下一个临邻接点～" << endl;
            return -1;
        }
    }
}

//插入点v
bool InserVex(MGraph &G, char v) {
    if (G.vexnum == MAX_VERTEX_NUM) {
        cout << "空间不够，无法插入！" << endl;
        return false;
    } else {
        int i = LocateVex(G, v);
        if (i != -1) {
            cout << "该点已存在，无法插入！" << endl;
            return false;
        } else {
            G.vexnum++;
            G.vexs[G.vexnum] = v;
            return true;
        }

    }
}

//删除v
bool DeleteVex(MGraph &G, int v) {
    int i = LocateVex(G, v);
    if (i == -1) {
        //cout << "要删除的点不存在！" << endl;
        return false;
    } else {
        for (int j = i; j < G.vexnum; ++j) {
            for (int k = 1; k <= G.vexnum; ++k) {
                G.arcs[j][k] = G.arcs[j + 1][k];
            }
        }
        for (int j = i; j < G.vexnum; ++j) {
            for (int k = 1; k <= G.vexnum; ++k) {
                G.arcs[k][j] = G.arcs[k][j + 1];
            }
        }

        for (int l = i; l < G.vexnum; ++l) {
            G.vexs[l] = G.vexs[l + 1];
        }
        G.vexnum--;
        return true;

    }
}

//在图中插入边v u
bool InsertArc(MGraph &G, char v, char u) {


    int i = LocateVex(G, v);
    int j = LocateVex(G, u);

    if (G.graphKind == UDG) {//无向图

        G.arcs[i][j].adj = 1;
        G.arcs[j][i].adj = 1;
        G.arcnum++;
        cout << "插入边成功～" << endl;
        return true;
    } else if (G.graphKind == DG) {//有向图
        G.arcs[i][j].adj = 1;
        G.arcnum++;
        cout << "插入边成功～" << endl;
        return true;
    }
    cout << "插入边失败！" << endl;
    return false;
}


bool DeleteArc(MGraph &G, char v, char u) {
    int i = LocateVex(G, v);
    int j = LocateVex(G, u);
    if (G.graphKind == UDG) {//无向图

        G.arcs[i][j].adj = -1;
        G.arcs[j][i].adj = -1;
        G.arcnum--;
        cout << "删除边成功～" << endl;
        return true;
    } else if (G.graphKind == DG) {//有向图
        G.arcs[i][j].adj = -1;
        G.arcnum--;
        cout << "删除边成功～" << endl;
        return true;
    }
    cout << "删除边失败！" << endl;
    return false;
}

//深度优先遍历
void DFSTraverse(MGraph G) {

    for (int i = 1; i <= G.vexnum; ++i) {
        Visited[i] = false;
    }


    for (int j = 1; j <= G.vexnum; ++j) {
        if (!Visited[j]) {
            DFS(G, j);
        }
    }


}

void DFS(MGraph G, int v) {

    char c = GetVex(G, v);
    cout << c << " ";
    Visited[v] = true;
    for (int f = FirstAdjVex2(G, c); f > 0;) {
        if (!Visited[f]) {
            DFS(G, f);

        }

        char k = GetVex(G, f);
        f = NextAdjVex2(G, c, k);
    }

}


//广度优先遍历
void BFDTraverse(MGraph G) {
    queue<char> q;

    for (int i = 1; i <= G.vexnum; ++i) {
        Visited[i] = false;
    }

    for (int j = 1; j <= G.vexnum; ++j) {
        if (!Visited[j]) {
            cout << GetVex(G, j) << " ";
            q.push(GetVex(G, j));
            while (!q.empty()) {
                char c = q.front();
                q.pop();
                int l = LocateVex(G, c);

                for (int w = FirstAdjVex2(G, c); w > 0; w = NextAdjVex2(G, c, GetVex(G, w))) {
                    if (!Visited[w]) {
                        cout << GetVex(G, w) << " ";
                        Visited[w] = true;
                    }
                }
            }
        }
    }
}

//创建有向图
bool CreateDG(MGraph &G) {
    //输入图的点数和边数以及点的代号
    cout << "请输入点的个数和边的个数：" << endl;
    cin >> G.vexnum >> G.arcnum;
    cout << "请输入" << G.vexnum << "个点的代号：" << endl;
    for (int i = 1; i <= G.vexnum; ++i) {
        cin >> G.vexs[i];
    }

    //初始化邻接矩阵
    for (int j = 1; j <= G.vexnum; ++j) {
        for (int i = 1; i < G.vexnum; ++i) {
            G.arcs[j][i].adj = -1;
        }
    }

    cout << "请输入有联系的点（格式：点1 点2）:" << endl;

    for (int k = 1; k <= G.arcnum; ++k) {
        char a, b;
        input_arc_UDN3:
        cin >> a >> b;
        int i = LocateVex(G, a);
        int j = LocateVex(G, b);

        if (i == -1 || j == -1) {
            cout << "您输入的点有误，请重新输入该路径：" << endl;
            goto input_arc_UDN3;
        } else {
            G.arcs[i][j].adj = 1;
        }
    }

    cout << "创建DG成功~" << endl;
    return true;
}

//创建有向网
bool CreateDN(MGraph &G) {
    //输入图的点数和边数以及点的代号
    cout << "请输入点的个数和边的个数：" << endl;
    cin >> G.vexnum >> G.arcnum;
    cout << "请输入" << G.vexnum << "个点的代号：" << endl;
    for (int i = 1; i <= G.vexnum; ++i) {
        cin >> G.vexs[i];
    }

    //初始化邻接矩阵
    for (int j = 1; j <= G.vexnum; ++j) {
        for (int i = 1; i < G.vexnum; ++i) {
            G.arcs[j][i].adj = -1;
        }
    }

    cout << "请输入边的详细信息（格式：点1 点2 距离）:" << endl;

    for (int k = 1; k <= G.arcnum; ++k) {
        char a, b;
        int v;
        input_arc_UDN4:
        cin >> a >> b >> v;
        int i = LocateVex(G, a);
        int j = LocateVex(G, b);

        if (i == -1 || j == -1) {
            cout << "您输入的点有误，请重新输入该路径：" << endl;
            goto input_arc_UDN4;
        } else if (v <= 0) {
            cout << "您输入的距离不合法，请重新输入该路径：" << endl;
            goto input_arc_UDN4;
        } else {
            G.arcs[i][j].adj = v;
        }
    }


    cout << "创建DN成功~" << endl;
    return true;

}

//创建无向图
bool CreateUDG(MGraph &G) {

    //输入图的点数和边数以及点的代号
    cout << "请输入点的个数和边的个数：" << endl;
    cin >> G.vexnum >> G.arcnum;
    cout << "请输入" << G.vexnum << "个点的代号：" << endl;
    for (int i = 1; i <= G.vexnum; ++i) {
        cin >> G.vexs[i];
    }

    //初始化邻接矩阵
    for (int j = 1; j <= G.vexnum; ++j) {
        for (int i = 1; i < G.vexnum; ++i) {
            G.arcs[j][i].adj = -1;
        }
    }

    cout << "请输入有联系的点（格式：点1 点2）:" << endl;

    for (int k = 1; k <= G.arcnum; ++k) {
        char a, b;
        input_arc_UDN2:
        cin >> a >> b;
        int i = LocateVex(G, a);
        int j = LocateVex(G, b);

        if (i == -1 || j == -1) {
            cout << "您输入的点有误，请重新输入该路径：" << endl;
            goto input_arc_UDN2;
        } else {
            G.arcs[i][j].adj = 1;
            G.arcs[j][i].adj = 1;
        }
    }

    cout << "创建UDG成功~" << endl;
    return true;
}

//构造无向网
bool CreateUDN(MGraph &G, vector<Node> v) {


    G.vexnum = v.size() + 1;
    G.arcnum = G.vexnum * G.vexnum;


    G.vexs[1] = 0;
    for (int i = 2; i <= G.vexnum; ++i) {
        G.vexs[i] = v[i - 2].code;
    }

    //初始化邻接矩阵
    for (int j = 1; j <= G.vexnum; ++j) {
        for (int i = 1; i <= G.vexnum; ++i) {
            G.arcs[j][i].adj = -1;
        }
    }


    for (int l = 1; l <= G.vexnum; ++l) {
        for (int i = 1; i <= G.vexnum; ++i) {
            if (l == 1) {
                double val;
                val = sqrt(pow(v[i].x, 2) + pow(v[i].y, 2));
                if (val <= 10 && val > 0) {
                    G.arcs[l][i].adj = val;
                }
            } else {
                double val;
                val = sqrt(pow(v[i].x - v[l].x, 2) + pow(v[i].y - v[l].y, 2));
                if (val <= 10 && val > 0) {

                    G.arcs[l][i].adj = val;
                }
            }
        }
    }

    G.vexnum = v.size() + 1;
    G.arcnum = G.vexnum * G.vexnum;

    cout << "创建UDN成功~" << endl;
    return true;
}


#endif //INC_1_ADTGRAPH_H
