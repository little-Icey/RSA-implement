#include<iostream>
#include<fstream>
#include<string>
#include<gmp.h>
#include<gmpxx.h>
#include<ctime>
#include "rsa.h"
#include "BigInt.h"

// 使用了gmp大数库来生成大素数
void Rsa::generalKey(string nfile, string efile, string dfile) {
    clock_t start, end;
    BigInt big;
    string pStr, qStr, nStr, dStr, eStr;
    ofstream out;

    // mpz_t 为GMP内置大数类型
    // 大素数p和q，公钥e
    mpz_t p, q, e; 
    mpz_init(p);
    mpz_init(q);
    mpz_init(e);
    gmp_randstate_t randNum;
    gmp_randinit_default(randNum);
    gmp_randseed_ui(randNum, time(NULL)); // 设置种子

    mpz_urandomb(p, randNum, 512); // 随机生成0~2^512-1之间的一个数
    mpz_urandomb(q, randNum, 512);
    mpz_urandomb(e, randNum, 128);

    // 生成大素数，其中e也为素数，满足于fai_n互素且小于fai_n
    mpz_nextprime(p, p); // 得到512bit的大素数
    mpz_nextprime(q, q); // 得到512bit的大素数
    mpz_nextprime(e, e); // 得到128bit的素数

    gmp_printf("p = %ZX\n\n", p);

    start = clock();
    char* tmp = mpz_get_str(NULL, 10, p);
    pStr = tmp;
    cout << "p: " << pStr << "\n\n";
    out.open("data/p.txt");
    out << big.dec_2_hex(pStr); // 将十六进制数写入文件
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

    // 计算fai_n = (p-1)*(q-1)
    string fai_n = big.MUL(big.SUB(pStr , "1"), big.SUB(qStr , "1"));
    cout << "fai_n:" << fai_n << "\n\n";

    dStr = big.inv(eStr, fai_n); // 求e模fai_n的逆元d
    cout << "d: " << dStr << "\n\n";
    out.open(dfile);
    out << big.dec_2_hex(dStr);
    out.close();
    end = clock();

    cout << "[*] running time: " << (end - start) / 1000 << "s\n";

    mpz_clear(p); // 内存回收
    mpz_clear(q);
    mpz_clear(e);
}

// RSA加密
// 要实现数据加密时调用该方法
// 数据加密是指用公钥{e, n}对指定的明文进行加密
string Rsa::encrypt(string plainfile, string cipherfile, string nfile, string efile) {
    BigInt big;
    ifstream in;
    ofstream out;
    string plainStr, eStr, nStr, cipherStr;

    in.open(plainfile);
    in >> plainStr; // 读入明文
    in.close();
    cout << "明文："<<plainStr << endl;

    in.open(nfile);
    in >> nStr; // 读入公钥
    in.close();
    cout << "n: "<<nStr << endl;

    in.open(efile);
    in >> eStr; // 读入公钥
    in.close();
    cout << "e: "<<eStr << endl;

    plainStr = big.hex_2_dec(plainStr);
    eStr = big.hex_2_dec(eStr);
    nStr = big.hex_2_dec(nStr);

    cipherStr = big.fast_pow(plainStr, eStr, nStr); // 对明文进行加密
    cipherStr = big.dec_2_hex(cipherStr);
    cout << "加密结果："<<cipherStr << endl; 

    out.open(cipherfile);
    out << cipherStr;
    out.close();

    return cipherStr;
}

// RSA解密
// 要实现数字签名时调用此方法
// 数字签名是指用私钥{d, n}对指定的明文进行加密
string Rsa::decrypt(string cipherfile, string plainfile, string nfile, string dfile) {
    BigInt big;
    ifstream in;
    ofstream out;
    string plainStr, dStr, nStr, cipherStr;

    in.open(cipherfile);
    in >> cipherStr; // 读入明文
    in.close();
    cout << "明文："<<cipherStr << endl;

    in.open(nfile);
    in >> nStr; // 读入私钥
    in.close();
    cout << "n: "<<nStr << endl;


    in.open(dfile);
    in >> dStr; // 读入私钥
    in.close();
    cout << "d: "<<dStr << endl;

    cipherStr = big.hex_2_dec(cipherStr);
    nStr = big.hex_2_dec(nStr);
    dStr = big.hex_2_dec(dStr);

    plainStr = big.fast_pow(cipherStr, dStr, nStr); // 对明文进行加密
    plainStr = big.dec_2_hex(plainStr);
    cout << "加密结果："<<plainStr << endl;

    out.open(plainfile);
    out << plainStr;
    out.close();

    return plainStr;
}