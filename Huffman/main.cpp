#include <iostream>
#include <fstream>
#include <vector>
#include "BiTree.h"


using namespace std;
string testjjj;
typedef struct {
    char m;
    int n;
} Content;

void EnCode();

vector<int> CharToNumber(char c);

void DeCode();

void HuffmanCode(vector<Content> v);

void DoCode();

void Select(BiNode *b, int i, int &s1, int &s2);

int main() {


    /*   FILE *te;
       te=fopen("/home/dmrf/文档/DataStructure/CourseDesign/test.txt","w");
       char c=' ';
       char d=32;
       fputc(c,te);
       //fputc(d,te);

       fflush(te);
       fclose(te);*/


    /* ofstream o("/home/dmrf/文档/DataStructure/CourseDesign/test.txt");
     o<<' ';*/
    /* ifstream i("/home/dmrf/文档/DataStructure/CourseDesign/test.txt");
     char c;
     c=20;
     i>>c;
     cout<<(int)c;*/


    EnCode();
    DeCode();

    return 0;
}


void EnCode() {//编码

    FILE *in;
    in = fopen("/home/dmrf/文档/DataStructure/CourseDesign/HuffmanData.txt", "r");


    vector<Content> c;
    while (!feof(in)) {
        char d;
        d = fgetc(in);


        bool flag = false;
        for (int i = 0; i < c.size(); ++i) {
            if (c[i].m == d) {
                c[i].n++;
                flag = true;
            }
        }
        if (!flag) {
            Content t;
            t.m = d;
            t.n = 1;
            c.push_back(t);
        }
    }

    fclose(in);

    //排序
    for (int j = 0; j < c.size() - 1; ++j) {
        for (int i = j + 1; i < c.size(); ++i) {
            if (c[j].n > c[i].n) {
                Content content;
                content = c[j];
                c[j] = c[i];
                c[i] = content;
            } else if (c[j].n == c[i].n && c[j].m > c[i].m) {
                Content content;
                content = c[j];
                c[j] = c[i];
                c[i] = content;
            }

        }
    }

    HuffmanCode(c);

    DoCode();


    /*for (int k = 0; k < c.size(); ++k) {
        cout << c[k].m << " " << c[k].n << endl;
    }*/
}

void DeCode() {//解码




    FILE *in;
    in = fopen("/home/dmrf/文档/DataStructure/CourseDesign/NewHuffmanData.txt", "r");


    string in_data;


    int j = 0;
    char ct;
    string code_data = "";

    vector<char> cc;
    cout << endl;
    while (!feof(in)) {
        ct = fgetc(in);
        cc.push_back(ct);
    }


    for (int l = 0; l < cc.size(); ++l) {
        //cout << (int) cc[l] << " ";
        vector<int> con;
        if (l == 37) {
            cout << "d";
        }
        if (cc[l] == 0) {
            if (cc[l + 1] == 0) {
                code_data += "0";
            } else if (cc[l + 1] == 1) {
                code_data += "1";
            }
            for (int i = 0; i < 7; ++i) {
                code_data += "0";
            }
            l++;
        } else {
            con = CharToNumber(cc[l]);
            for (int i = 0; i < 8; ++i) {
                if (con[i] == 0) {
                    code_data += "0";
                } else {
                    code_data += "1";
                }
            }
        }


    }


    // cout << endl << "j:" << cc.size() - 1 << endl;
    //  cout << "code_data:" << endl;
  //  cout << code_data;

    vector<string> val;
    for (int j = 0; j <= 256; ++j) {
        val.push_back("");
    }
    fstream incode("/home/dmrf/文档/DataStructure/CourseDesign/HuffmanCode.txt");

    int n = 0;
    int c;
    string co;
    while (incode >> c >> co) {


        int index;
        if (c < 0) {
            index = -c + 127;
        } else {
            index = c;
        }
        val[index] = co;
    }


    incode.close();


    FILE *ou;
    ou = fopen("/home/dmrf/文档/DataStructure/CourseDesign/EnCodeHuffmanData.txt", "w");

    //int et=0;
    cout << endl;
    string tim_str;
    string fi = "";
    // code_data=testjjj;
    string gs = "";
    for (int m = 0; m <= code_data.size() - 10; ++m) {
        gs += code_data[m];
    }
    // cout<<"gs:"<<gs.size()<<endl;
    cout << gs << endl;

    for (int i1 = 0; i1 < gs.size(); ++i1) {
        if (gs[i1] != testjjj[i1]) {
            cout << "s";
        }
    }

    for (int k = 0; k < gs.size(); ++k) {
        tim_str += gs[k];


        for (int i = 0; i < val.size(); ++i) {
            if (tim_str == val[i]) {
                char c;

                if (i > 127) {
                    c = i - 127;
                    c = -c;
                } else {
                    c = i;
                }

                if (k>=gs.size()-8){
                    break;
                }
                fi += c;
                fputc(c, ou);
                tim_str = "";
                break;
            }
        }

    }

    fflush(ou);
    fclose(ou);

}


vector<int> CharToNumber(char c) {//将ascill转化为二进制
    vector<int> bin;
    int n;
    if (c <= 0) {
        bin.push_back(0);
        n = -c;
    } else {
        bin.push_back(1);
        n = c;
    }
    int temp[7];
    for (int i = 0; i < 7; ++i) {
        int a;
        a = n % 2;
        n = n / 2;
        temp[i] = a;
    }

    for (int j = 0; j <= 7; ++j) {
        bin.push_back(temp[6 - j]);
    }
    return bin;
}

void DoCode() {


    vector<string> val;
    for (int j = 0; j <= 256; ++j) {
        val.push_back("");
    }
    fstream incode("/home/dmrf/文档/DataStructure/CourseDesign/HuffmanCode.txt");

    int n = 0;
    int c;
    string co;
    while (incode >> c >> co) {


        int index;
        if (c < 0) {
            index = -c + 127;
        } else {
            index = c;
        }
        val[index] = co;
    }


    incode.close();


    FILE *out;
    out = fopen("/home/dmrf/文档/DataStructure/CourseDesign/NewHuffmanData.txt", "w");


    FILE *huffman;
    huffman = fopen("/home/dmrf/文档/DataStructure/CourseDesign/HuffmanData.txt", "r");


    string finalcode;
    char d;

    while (!feof(huffman)) {
        d = fgetc(huffman);
        int c = d;
        n++;
        int index;

        if (c < 0) {
            index = -c + 127;
        } else {
            index = c;
        }

        finalcode += val[index];

    }


    //cout<<"et"<<et<<endl;
    /* cout << "总字数" << n << endl;

     cout << endl;*/
    cout << "finalcode:" << endl;
    cout << "size:" << finalcode.size() << endl;

    cout << finalcode;

    int bit[8];
    int flag_number = 0;
    int for_number = 0;

    int n1 = 0;

    int cont = 1;
    int g;

    while (true) {
        if (flag_number == 8) {
            int temp = bit[1] * (int) pow(2, 6) +
                       bit[2] * (int) pow(2, 5) +
                       bit[3] * (int) pow(2, 4) +
                       bit[4] * (int) pow(2, 3) +
                       bit[5] * (int) pow(2, 2) +
                       bit[6] * (int) pow(2, 1) +
                       bit[7] * (int) pow(2, 0);

            if (temp == 0) {
                if (bit[0] == 0) {
                    fputc(0, out);
                    fputc(0, out);
                } else {
                    fputc(0, out);
                    fputc(1, out);
                }
            } else {
                if (bit[0] == 0) {//0是负

                    temp *= -1;
                }

                char cs = temp;
                fputc(cs, out);
            }
            flag_number = 0;
            for_number++;
            int t = temp;
            // cout << t << " ";
            n1++;
            if (flag_number + for_number * 8 == finalcode.size()) {
                break;
            }
        } else {
            if (flag_number + for_number * 8 == finalcode.size()) {
                int temp = 0;
                for (int i = 0; i < flag_number; ++i) {
                    temp += bit[i] * pow(2, 7 - i);

                }


                if (bit[0] == 0) {//0是负
                    temp *= -1;
                }
                char cs = temp;
                fputc(cs, out);
                break;
            } else {
                char temp_c = finalcode[flag_number + for_number * 8];
                if (temp_c == 48) {//0
                    bit[flag_number] = 0;
                } else {
                    bit[flag_number] = 1;
                }

                flag_number++;
            }

        }
    }


    //cout << endl << "编码后的总字符数为：" << n1 << endl;


    fflush(out);
    fclose(out);


    fclose(huffman);

    testjjj = finalcode;
/*

    FILE *ou;
    ou = fopen("/home/dmrf/文档/DataStructure/CourseDesign/EnCodeHuffmanData.txt", "w");

    //int et=0;
    cout << endl;
    string tim_str;
    for (int k = 0; k < finalcode.size(); ++k) {
        tim_str += finalcode[k];

        for (int i = 0; i < val.size(); ++i) {
            if (tim_str == val[i]) {
                char c;

                if (i > 127) {
                    c = i - 127;
                    c = -c;
                } else {
                    c = i;
                }


                fputc(c, ou);
                tim_str = "";
                break;
            }
        }

    }

    fflush(ou);
    fclose(ou);*/

}


void HuffmanCode(vector<Content> v) {
    int n = v.size();


    int m = 2 * n;

    BiNode *biNode = new BiNode[2 * n];


    for (int k = 1; k <= n; ++k) {
        biNode[k].lchild = NULL;
        biNode[k].rchild = NULL;
        biNode[k].parent = NULL;
        biNode[k].c = v[k - 1].m;
        biNode[k].v = v[k - 1].n;
    }

    for (int i = n + 1; i < m; ++i) {
        biNode[i].lchild = NULL;
        biNode[i].rchild = NULL;
        biNode[i].parent = NULL;
    }

    for (int j = n + 1; j < m; ++j) {
        int s1;
        int s2;
        Select(biNode, j, s1, s2);
        biNode[j].v = biNode[s1].v + biNode[s2].v;
        biNode[j].lchild = &biNode[s1];
        biNode[j].rchild = &biNode[s2];
        biNode[s1].parent = &biNode[j];
        biNode[s2].parent = &biNode[j];
    }


    ofstream code("/home/dmrf/文档/DataStructure/CourseDesign/HuffmanCode.txt");
    if (!code.is_open()) {
        cout << "HuffmanCode.txt1打开失败！" << endl;
    }


    cout << "编码：" << endl;
    GetCode(&biNode[m - 1], "", code);
    code.close();
    free(biNode);


}

void Select(BiNode *b, int i, int &s1, int &s2) {

    int m2, m1;

    m2 = 10000;
    m1 = m2;
    i--;
    while (i > 0) {
        if (b[i].v < m1 && b[i].parent == NULL) {
            m2 = m1;
            s2 = s1;
            m1 = b[i].v;
            s1 = i;
        } else if (b[i].v == m1 && b[i].parent == NULL) {
            if (b[i].c < b[s1].c) {
                m2 = m1;
                s2 = s1;
                m1 = b[i].v;
                s1 = i;
            }
        } else if (b[i].v < m2 && b[i].parent == NULL) {
            m2 = b[i].v;
            s2 = i;
        } else if (b[i].v == m2 && b[i].parent == NULL) {
            if (b[i].c < b[s2].c) {
                m2 = b[i].v;
                s2 = i;
            }
        }
        i--;

    }
}
