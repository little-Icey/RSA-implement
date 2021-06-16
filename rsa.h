#pragma once
#ifndef _RSA_H__
#define _RSA_H__

#include<string>
#include<iostream>

using namespace std;

class Rsa {
public:
	Rsa(){}
	void generalKey(string nfile, string efile, string dfile);
	string encrypt(string plainfile, string cipherfile, string nfile, string efile);
	string decrypt(string cipherfile, string plainfile, string nfile, string dfile);
	Rsa(Rsa& e);
	~Rsa() {};
};

#endif // !_RSA_H__
