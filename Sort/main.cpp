#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <queue>
#include <time.h>

using namespace std;

void MSort(vector<int> v);

void getNum();

void ShellSort(vector<int> v);

void ShellInsert(vector<int> &v, int d);

void HeapSort(vector<int> v);

int Partition(vector<int> &v, int low, int high);

void BubbleSort(vector<int> v);

void QSort(vector<int> &v, int low, int high);

void SelectSort(vector<int> v);

void HeapAdjust(vector<int> &v, int s, int m);

void QuickSort(vector<int> v);

int GetMaxBit(vector<int> v);

void InsertSort(vector<int> v);

void radixSort(vector<int> v);

void doSort(vector<int> v);

int main() {

    // getNum();
/*
    vector<int> v;
    v.push_back(456);
    v.push_back(34);
    v.push_back(29);
    v.push_back(199);
    v.push_back(5);
    v.push_back(43);
    v.push_back(5);
    v.push_back(533);
    v.push_back(555);
    v.push_back(65);
    v.push_back(2);

    doSort(v);*/

     ifstream in("/home/dmrf/文档/DataStructure/CourseDesign/num.txt");
     if (!in.is_open()) {
         cout << "文件打开失败~" << endl;
         return 0;
     }
     int x = 0;
     vector<int> v;
     int t;
     int w=1;
     while (!in.eof()) {
         in >> t;
         v.push_back(t);
         if (v.size() == 20000) {
             cout<<"第"<<w<<"次排序："<<endl;
             w++;
             doSort(v);
             v.clear();
         }
     }

    return 0;
}

void doSort(vector<int> v) {


    double Time;
    time_t end;
    time_t start;


    start = clock();
    cout << "快速排序中..." << endl;
    QuickSort(v);
    end = clock();
    Time = (end - start) / CLOCKS_PER_SEC;
    cout << "快速排序：" << Time << endl;

    start = clock();
    cout << "归并排序中..." << endl;
    MSort(v);
    end = clock();
    Time = (end - start) / CLOCKS_PER_SEC;
    cout << "归并排序：" << Time << endl;


    start = clock();
    cout << "插入排序中..." << endl;
    InsertSort(v);
    end = clock();
    Time = (end - start) / CLOCKS_PER_SEC;
    cout << "插入排序:" << Time << endl;

    start = clock();
    cout << "希尔排序中..." << endl;
    ShellSort(v);
    end = clock();
    Time = (end - start) / CLOCKS_PER_SEC;
    cout << "希尔排序：" << Time << endl;


    start = clock();
    cout << "冒泡排序中..." << endl;
    BubbleSort(v);
    end = clock();
    Time = (end - start) / CLOCKS_PER_SEC;
    cout << "冒泡排序：" << Time << endl;



    start = clock();
    cout << "选择排序中..." << endl;
    SelectSort(v);
    end = clock();
    Time = (end - start) / CLOCKS_PER_SEC;
    cout << "选择排序：" << Time << endl;


    start = clock();
    cout << "堆排序中..." << endl;
    HeapSort(v);
    end = clock();
    Time = (end - start) / CLOCKS_PER_SEC;
    cout << "堆排序：" << Time << endl;


    start = clock();
    cout << "基数排序中..." << endl;
    radixSort(v);
    end = clock();
    Time = (end - start) / CLOCKS_PER_SEC;
    cout << "基数排序：" << Time << endl;

}

void getNum() {

    ofstream out("/home/dmrf/文档/DataStructure/CourseDesign/num.txt");

    //生成升序数
    int num = 1;
    int x = rand();
    out << x << " ";
    while (true) {
        int f = rand();
        if (f > x) {
            out << f << " ";
            num++;
        }
        if (num == 20000) {
            out << endl;
            break;
        }
    }

    //生成降序数


    num = 1;
    x = rand();
    out << x << " ";
    while (true) {
        int f = rand();
        if (f < x) {
            out << f << " ";
            num++;
        }
        if (num == 20000) {
            out << endl;
            break;
        }
    }


    for (int i = 0; i < 8; ++i) {
        num = 20000;
        while (num > 0) {
            out << rand() << " ";
            num--;
        }

        out << endl;
    }

    cout << "生成成功！" << endl;
}


void show(vector<int> v) {
    /*for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;*/
}

/*
 * 直接插入排序
 * T(n)=O(n^2)
 * S(n)=O(1)
 * 稳定
 */
void InsertSort(vector<int> v) {

    for (int i = 1; i < v.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (v[j] > v[i]) {
                int t = v[i];
                for (int k = i; k > j; --k) {
                    v[k] = v[k - 1];
                }
                v[j] = t;
            }
        }
    }
    show(v);

}


/*
 * 希尔排序
 * T(n)=O(n^1.5)
 * S(n)=O(1)
 * 不稳定
 */


void ShellSort(vector<int> v) {
    int d[3] = {5, 3, 1};
    for (int i = 0; i < 3; ++i) {
        ShellInsert(v, d[i]);
    }
    show(v);
}


void ShellInsert(vector<int> &v, int d) {
    for (int l = 0; l < d; ++l) {
        for (int i = l + 1; i < v.size(); i += d) {
            for (int j = l; j < i; j += d) {
                if (v[j] > v[i]) {
                    int t = v[i];
                    v[i] = v[j];
                    v[j] = t;
                }
            }
        }
    }
}


/*
 * 冒泡排序
 * T(n)=O(n^2)
 * S(n)=O(1)
 * 稳定
 */

void BubbleSort(vector<int> v) {

    for (int i = 0; i < v.size(); ++i) {
        int flag = 1;
        for (int j = 0; j < v.size() - i && j < v.size() - 1; ++j) {
            if (v[j] > v[j + 1]) {
                int t;
                t = v[j];
                v[j] = v[j + 1];
                v[j + 1] = t;
                flag = 0;
            }
        }

        if (flag == 1) {//说明已经有序了
            break;
        }
    }

    show(v);
}


/*
 * 快速排序
 * T(n)=O(nlog2->n)
 * S(n)=O(log2->n)
 * 不稳定
 */

void QuickSort(vector<int> v) {
    QSort(v, 0, v.size() - 1);
    show(v);
}

void QSort(vector<int> &v, int low, int high) {

    if (low >= high) {
        return;
    }
    int t = Partition(v, low, high);
    QSort(v, low, t - 1);
    QSort(v, t + 1, high);
}

int Partition(vector<int> &v, int low, int high) {
    int pivotkey;
    pivotkey = v[low];

    while (low < high) {
        while (low < high && v[high] >= pivotkey) {
            --high;
        }
        int t;
        t = v[low];
        v[low] = v[high];
        v[high] = t;

        while (low < high && v[low] <= pivotkey) {
            ++low;
        }
        t = v[low];
        v[low] = v[high];
        v[high] = t;
    }

    return low;
}


/*
 * 选择排序
 * S(n)=O(1)
 * T(n)=O(n^2)
 * 不稳定
 */

void SelectSort(vector<int> v) {
    for (int i = 0; i < v.size(); ++i) {
        int min;
        min = i;
        for (int j = i + 1; j < v.size(); ++j) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        int t;
        t = v[min];
        v[min] = v[i];
        v[i] = t;
    }
    show(v);
}


/*
 * 堆排序
 * T(n)=O(nlog2-->n)
 * S(n)=O(1)
 * 不稳定
 */

void HeapSort(vector<int> v) {
    vector<int> n_v;
    int size = v.size();
    for (int k = v.size(); k > 0; --k) {
        v[k] = v[k - 1];
    }
    //建堆
    for (int i = size / 2; i > 0; --i) {
        HeapAdjust(v, i, size);
    }

    for (int j = size; j > 1; --j) {
        int t;
        t = v[1];
        n_v.push_back(t);
        v[1] = v[j];
        v[j] = t;
        HeapAdjust(v, 1, j - 1);
    }
    int t = v[1];
    n_v.push_back(t);

    /*
     * n_v即为排好序的vector
     */
    show(n_v);
}

void HeapAdjust(vector<int> &v, int s, int m) {
    /*
     * 已知v[s..m]除v[s]之外均满足堆的定义，本函数调整v[s]，使得v[s..m]成为一个大顶堆
     */

    int rc;
    rc = v[s];
    for (int i = 2 * s; i <= m; i = 2 * i) {
        if (i < m && v[i] > v[i + 1]) {
            i++;//i为较小数据的下标
        }
        if (rc <= v[i]) {
            break;
        }

        v[s] = v[i];
        s = i;
    }
    v[s] = rc;
}


/*
 * 归并排序
 * T(n)=O(nlog2-->n)
 * S(n)=O(n)
 * 稳定
 */


void MSort(vector<int> v) {


    vector<int> h;
    h = v;

    int start, seg;


    for (seg = 1; seg < v.size(); seg *= 2) {
        int k = 0;
        for (start = 0; start < v.size(); start = start + seg * 2) {
            int end;
            end = start + seg;
            int low = start;
            while (low < start + seg && end < start + seg + seg && low < v.size() && end < v.size()) {
                if (v[low] <= v[end]) {
                    h[k++] = v[low];
                    low++;
                } else {
                    h[k++] = v[end];
                    end++;
                }
            }

            while (low < start + seg && low < v.size()) {
                h[k++] = v[low++];
            }
            while (end < start + seg + seg && end < v.size()) {
                h[k++] = v[end++];
            }

        }

        v = h;
    }
    show(v);

}


/*
 * 基数排序
 * T(n)=O(d*n) d为排序数中最大数的位数
 * S(n)=O(n)
 * 稳定
 *
 */

void radixSort(vector<int> v) {

    int d = GetMaxBit(v);

    int *count = new int[10];
    queue<int> q[10];

    int radix = 1;
    for (int i = 0; i < d; ++i) {
        for (int j = 0; j < v.size(); ++j) {
            int t;
            t = (v[j] / radix) % 10;
            q[t].push(v[j]);
        }

        int p = 0;
        for (int k = 0; k < 10; ++k) {
            while (!q[k].empty()) {
                v[p++] = q[k].front();
                q[k].pop();
            }
        }
        radix *= 10;
    }
    show(v);

}

int GetMaxBit(vector<int> v) {
    int max = v[0];
    for (int i = 1; i < v.size(); ++i) {
        max = v[i] > max ? v[i] : max;
    }

    int d = 1;
    while (max >= 10) {
        max /= 10;
        d++;
    }
    return d;

}


