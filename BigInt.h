#pragma once
#ifndef _BIGINT_H__
#define _BIGINT_H__

#include<iostream>
#include<string>

using namespace std;

// ����������
// ʵ���˴������ļӼ��˳��Լ���ģ����
// ʵ�������������������
// ʵ������չŷ������Լ���˷���Ԫ��ͬʱʹ�ÿ�����ȡģ������RSA�ӽ���
class BigInt {
public:
	BigInt(){}
	inline int compare(string a, string b); //��ȷ���0�����ڷ���1��С�ڷ���-1
	string SUB(string a, string b); // ����
	string SUB_unsigned(string a, string b); // ��������
	string ADD(string a, string b); // �ӷ�
	string MUL(string a, string b); // �˷�
	string DIVIDE(string str1, string str2, int flag); // ������flag==1,������;flag==0ʱ����������
	string QUOTIENT(string a, string b); // ����
	string MOD(string a, string b); // ����
	string exGcd(string a, string b, string& x, string& y); // ��չŷ�����
	string gcd(string a, string b); // ���������
	string dec_2_hex(string dec); // ʮ����תʮ������
	string hex_2_dec(string hex); // ʮ������תʮ����
	string POW(string str, int pow); // ������
	string inv(string n, string p); // ��˷���Ԫ
	string fast_pow(string a, string b, string c); // ������ȡģ
	BigInt(BigInt& e);
	~BigInt() {}; // ��������
};


#endif // !_BIGINT_H__
