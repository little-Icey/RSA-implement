#include<iostream>
#include<fstream>
#include<string>
#include<gmp.h>
#include<gmpxx.h>
#include<ctime>
#include "rsa.h"
#include "BigInt.h"

// ʹ����gmp�����������ɴ�����
void Rsa::generalKey(string nfile, string efile, string dfile) {
    clock_t start, end;
    BigInt big;
    string pStr, qStr, nStr, dStr, eStr;
    ofstream out;

    // mpz_t ΪGMP���ô�������
    // ������p��q����Կe
    mpz_t p, q, e; 
    mpz_init(p);
    mpz_init(q);
    mpz_init(e);
    gmp_randstate_t randNum;
    gmp_randinit_default(randNum);
    gmp_randseed_ui(randNum, time(NULL)); // ��������

    mpz_urandomb(p, randNum, 512); // �������0~2^512-1֮���һ����
    mpz_urandomb(q, randNum, 512);
    mpz_urandomb(e, randNum, 128);

    // ���ɴ�����������eҲΪ������������fai_n������С��fai_n
    mpz_nextprime(p, p); // �õ�512bit�Ĵ�����
    mpz_nextprime(q, q); // �õ�512bit�Ĵ�����
    mpz_nextprime(e, e); // �õ�128bit������

    gmp_printf("p = %ZX\n\n", p);

    start = clock();
    char* tmp = mpz_get_str(NULL, 10, p);
    pStr = tmp;
    cout << "p: " << pStr << "\n\n";
    out.open("data/p.txt");
    out << big.dec_2_hex(pStr); // ��ʮ��������д���ļ�
    out.close();

    tmp = mpz_get_str(NULL, 10, q);
    qStr = tmp;
    cout << "q: " << qStr << "\n\n";
    out.open("data/q.txt");
    out << big.dec_2_hex(qStr);
    out.close();

    tmp = mpz_get_str(NULL, 10, e);
    eStr = tmp;
    cout << "e: " << eStr << "\n\n";
    out.open(efile);
    out << big.dec_2_hex(eStr);
    out.close();

    nStr = big.MUL(pStr, qStr);
    cout << "n: " << nStr << "\n\n";
    out.open(nfile);
    out << big.dec_2_hex(nStr);
    out.close();

    // ����fai_n = (p-1)*(q-1)
    string fai_n = big.MUL(big.SUB(pStr , "1"), big.SUB(qStr , "1"));
    cout << "fai_n:" << fai_n << "\n\n";

    dStr = big.inv(eStr, fai_n); // ��eģfai_n����Ԫd
    cout << "d: " << dStr << "\n\n";
    out.open(dfile);
    out << big.dec_2_hex(dStr);
    out.close();
    end = clock();

    cout << "[*] running time: " << (end - start) / 1000 << "s\n";

    mpz_clear(p); // �ڴ����
    mpz_clear(q);
    mpz_clear(e);
}

// RSA����
// Ҫʵ�����ݼ���ʱ���ø÷���
// ���ݼ�����ָ�ù�Կ{e, n}��ָ�������Ľ��м���
string Rsa::encrypt(string plainfile, string cipherfile, string nfile, string efile) {
    BigInt big;
    ifstream in;
    ofstream out;
    string plainStr, eStr, nStr, cipherStr;

    in.open(plainfile);
    in >> plainStr; // ��������
    in.close();
    cout << "���ģ�"<<plainStr << endl;

    in.open(nfile);
    in >> nStr; // ���빫Կ
    in.close();
    cout << "n: "<<nStr << endl;

    in.open(efile);
    in >> eStr; // ���빫Կ
    in.close();
    cout << "e: "<<eStr << endl;

    plainStr = big.hex_2_dec(plainStr);
    eStr = big.hex_2_dec(eStr);
    nStr = big.hex_2_dec(nStr);

    cipherStr = big.fast_pow(plainStr, eStr, nStr); // �����Ľ��м���
    cipherStr = big.dec_2_hex(cipherStr);
    cout << "���ܽ����"<<cipherStr << endl; 

    out.open(cipherfile);
    out << cipherStr;
    out.close();

    return cipherStr;
}

// RSA����
// Ҫʵ������ǩ��ʱ���ô˷���
// ����ǩ����ָ��˽Կ{d, n}��ָ�������Ľ��м���
string Rsa::decrypt(string cipherfile, string plainfile, string nfile, string dfile) {
    BigInt big;
    ifstream in;
    ofstream out;
    string plainStr, dStr, nStr, cipherStr;

    in.open(cipherfile);
    in >> cipherStr; // ��������
    in.close();
    cout << "���ģ�"<<cipherStr << endl;

    in.open(nfile);
    in >> nStr; // ����˽Կ
    in.close();
    cout << "n: "<<nStr << endl;


    in.open(dfile);
    in >> dStr; // ����˽Կ
    in.close();
    cout << "d: "<<dStr << endl;

    cipherStr = big.hex_2_dec(cipherStr);
    nStr = big.hex_2_dec(nStr);
    dStr = big.hex_2_dec(dStr);

    plainStr = big.fast_pow(cipherStr, dStr, nStr); // �����Ľ��м���
    plainStr = big.dec_2_hex(plainStr);
    cout << "���ܽ����"<<plainStr << endl;

    out.open(plainfile);
    out << plainStr;
    out.close();

    return plainStr;
}