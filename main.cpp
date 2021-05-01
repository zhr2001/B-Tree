#include "BPlusTree.cpp"
#include <stdlib.h>
#include <fstream>
using namespace std;

string strRand(int length) {			// length: 产生字符串的长度
    char tmp;							// tmp: 暂存一个随机数
    string buffer;						// buffer: 保存返回值

    for (int i = 0; i < length; i++) {
        tmp = rand() % 36;	// 随机一个小于 36 的整数，0-9、A-Z 共 36 种字符
        if (tmp < 10) {			// 如果随机数小于 10，变换成一个阿拉伯数字的 ASCII
            tmp += '0';
        } else {				// 否则，变换成一个大写字母的 ASCII
            tmp -= 10;
            tmp += 'A';
        }
        buffer += tmp;
    }
    return buffer;
}

void rand_file() {
    ofstream out("../test.txt");
    int a = rand() + 2000 ;
    out << a << endl;
    for(int i = 0; i < a-1000; i++) {
        out << 3 << " " << 6 << endl;
        out << rand()+100 << " ";
        int rand_len = rand()%35+5;
        string name = strRand(rand_len);
        out << name << " ";
        out << rand()%100+3 << endl;
    }
    out << 5 << endl;
}


int main() {
    BPlusTree t;
    int no, all;
    string name;
//    rand_file();
    ifstream in("../test.txt");
    int N; in >> N;
    for(int i = 0, opt; i < N; i++) {
        in >> opt;
        if (opt == 1) {
            in >> no >> name >> all;
            Book b(no, name);
            b.setStock(all);
            t.insertVal(b);
        }
        if (opt == 2) {
            in >> no;
            t.deleteVal(no);
        }
        if (opt == 3) {
            in >> no;
            t.lentFromBooks(no);
        }
        if(opt == 4) {
            in >> no;
            t.giveBackBook(no);
        }
        if (opt == 5) {
            t.print();
        }
    }
    return 0;
}
