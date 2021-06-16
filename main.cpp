#include<gmpxx.h>
#include<gmp.h>
#include<iostream>
#include<fstream>
#include<ctime>
#include "BigInt.h"
#include "rsa.h"

using namespace std;

typedef struct commandline { // �����в����Ľṹ��
    string plainfile;
    string nfile;
    string efile="";
    string dfile="";
    string cipherfile;

}commands;

commandline com;

int exGcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;  //�ݹ鵽��ײ�ʱ����x��y��ֵ  
        y = 0;
        return a;
    }
    int g = exGcd(b, a % b, x, y);
    int temp = x;
    x = y;
    y = temp - a / b * y;
    return g;
}

void test() {
    BigInt demo;
    string a;
    string b;
    string c;
    string x, y;
    cout << (-345) % (1234) << endl; // ����ȡ��

    while (1) {
        cin >> a;
        cin >> b;
        cin >> c;
        cout << "+: " << demo.ADD(a, b) << endl;
        cout << "-: " << demo.SUB(a, b) << endl;
        cout << "*: " << demo.MUL(a, b) << endl;
        cout << "/: " << demo.QUOTIENT(a, b) << endl;
        cout << "%: " << demo.MOD(a, b) << endl << endl;
        demo.exGcd(a, b, x, y);
        cout << x << "\t" << y << endl;
        cout << "�����ݽ����" << demo.fast_pow(a, b, c) << endl;
    }
}

int main(int argc, char* argv[]) {
    //clock_t start, end;
    BigInt demo;
    Rsa rsa;
    ofstream out;
    string pStr, qStr, nStr, dStr, eStr;

    for (int i = 1; i < argc; i+=2) { // ��������������в����Խṹ���Ա���и�ֵ
        if (!strcmp(argv[i], "-p"))
            com.plainfile = argv[i + 1];
        else if (!strcmp(argv[i], "-n"))
            com.nfile = argv[i + 1];
        else if (!strcmp(argv[i], "-e"))
            com.efile = argv[i + 1];
        else if (!strcmp(argv[i], "-d"))
            com.dfile = argv[i + 1];
        else if (!strcmp(argv[i], "-c"))
            com.cipherfile = argv[i + 1];
    }
    //rsa.generalKey(com.nfile, com.efile, com.dfile);
    //test();

    if ((com.plainfile == "") && (com.cipherfile == "")) {
        cout << "��Կ����\n";
        rsa.generalKey(com.nfile, com.efile, com.dfile);
        return 0;
    }

    if (com.efile != "") { // ��������в�������-e����������ݼ���
        cout << "[+] ���ݼ��ܣ�" << endl;
        rsa.encrypt(com.plainfile, com.cipherfile, com.nfile, com.efile);
    }
    else if(com.dfile!=""){ // ��������в�������-d�����������ǩ��
        cout << "[+] ����ǩ����\n";
        rsa.decrypt(com.plainfile, com.cipherfile, com.nfile, com.dfile);
    }    
    
    return 0;
}