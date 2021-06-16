#pragma once
#ifndef _BIGINT_H__
#define _BIGINT_H__

#include<iostream>
#include<string>

using namespace std;

// 大数运算类
// 实现了大整数的加减乘除以及驱模运算
// 实现了求两数的最大公因数
// 实现了扩展欧几里得以及求乘法逆元，同时使用快速幂取模来加速RSA加解密
class BigInt {
public:
	BigInt(){}
	inline int compare(string a, string b); //相等返回0，大于返回1，小于返回-1
	string SUB(string a, string b); // 减法
	string SUB_unsigned(string a, string b); // 正正减法
	string ADD(string a, string b); // 加法
	string MUL(string a, string b); // 乘法
	string DIVIDE(string str1, string str2, int flag); // 除法，flag==1,返回商;flag==0时，返回余数
	string QUOTIENT(string a, string b); // 求商
	string MOD(string a, string b); // 求余
	string exGcd(string a, string b, string& x, string& y); // 扩展欧几里得
	string gcd(string a, string b); // 求最大公因数
	string dec_2_hex(string dec); // 十进制转十六进制
	string hex_2_dec(string hex); // 十六进制转十进制
	string POW(string str, int pow); // 幂运算
	string inv(string n, string p); // 求乘法逆元
	string fast_pow(string a, string b, string c); // 快速幂取模
	BigInt(BigInt& e);
	~BigInt() {}; // 析构函数
};


#endif // !_BIGINT_H__
