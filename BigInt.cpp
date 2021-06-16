#include<iostream>
#include<string>
#include "BigInt.h"

//相等返回0，大于返回1，小于返回-1
inline int BigInt::compare(string a, string b) { 
	if (a.size() > b.size()) {
		return 1;
	}
	else if (a.size() < b.size()) {
		return -1;
	}
	else return a.compare(b); //若长度相等，则从头到尾按位比较
}

// 大数加法
string BigInt::ADD(string a, string b) {
	int sign = 1;// sign为符号为
	string str;
	if (a[0] == '-')
	{
		if (b[0] == '-')       //负负
		{
			sign = -1;
			str = ADD(a.erase(0, 1), b.erase(0, 1));//erase(first,last);删除从first到last之间的字符
		}
		else             //负正
		{
			str = SUB(b, a.erase(0, 1));
		}
	}
	else
	{
		if (b[0] == '-')        //正负
		{
			str = SUB(a, b.erase(0, 1));
		}
		else                    //正正，把两个整数对齐，短整数前面加0补齐
		{
			string::size_type L1, L2;  //string::size_type抽象意义是尺寸单位类型
			int i;
			L1 = a.size();
			L2 = b.size();
			if (L1 < L2)
			{
				for (i = 0; i < L2 - L1; i++)
					a = "0" + a;
			}
			else
			{
				for (i = 0; i < L1 - L2; i++)
					b = "0" + b;
			}
			int int1 = 0, int2 = 0;
			for (i = a.size() - 1; i >= 0; i--)
			{
				int1 = (int(a[i]) - '0' + int(b[i]) - '0' + int2) % 10;
				int2 = (int(a[i]) - '0' + int(b[i]) - '0' + int2) / 10;
				str = char(int1 + '0') + str;
			}
			if (int2 != 0)str = char(int2 + '0') + str;
		}

	}
	//运算符处理符号
	if ((sign == -1) && (str[0] != '0'))str = "-" + str;
	return str;
}

// 两个正数减法
string BigInt::SUB_unsigned(string a, string b) {
	int sign = 1; //sign为符号位
	string str;
	int i, j;

	int res = compare(a, b);
	if (res == 0)return "0";
	if (res < 0)
	{
		sign = -1; // 结果应该是负号
		string temp = a;
		a = b;
		b = temp;
	}
	string::size_type tempint;
	tempint = a.size() - b.size();
	for (i = b.size() - 1; i >= 0; i--)
	{
		if (a[i + tempint] < b[i])          //借位
		{
			j = 1;
			while (1)
			{
				if (a[tempint - j + i] == '0')
				{
					a[i + tempint - j] = '9';
					j++;
				}
				else
				{
					a[i + tempint - j] = char(int(a[i + tempint - j]) - 1);
					break;
				}
			}
			str = char(a[i + tempint] - b[i] + ':') + str;
		}
		else
		{
			str = char(a[i + tempint] - b[i] + '0') + str;
		}
	}
	for (i = tempint - 1; i >= 0; i--)
		str = a[i] + str;

	//去出结果中多余的前导0
	str.erase(0, str.find_first_not_of('0'));
	if (str.empty())str = "0";
	if ((sign == -1) && (str[0] != '0'))
		str = "-" + str;
	return str;
}

// 大数减法
string BigInt::SUB(string a, string b) {
	int sign = 1;
	char sign_a = a[0];
	char sign_b = b[0];
	string ans;

	int res = compare(a, b);
	if (res == 0)
		return "0";

	if (sign_a == '-') {
		if (sign_b == '-') { // 负负，相当于b-a
			ans = SUB_unsigned(b.erase(0,1), a.erase(0,1));
			return ans;
		}
		else { // 负正，相当于-(a+b)
			ans = ADD(a.erase(0,1), b);
			ans = '-' + ans;
			return ans;
		}
	}
	else {
		if (sign_b == '-') { // 正负，相当于a+b
			return ADD(a, b.erase(0,1));
		}
		else { // 正正，a-b
			return SUB_unsigned(a, b);
		}
	}

}

// 大数乘法
string BigInt::MUL(string a, string b){
	int sign = 1;
	string str = "0";        //记录当前值
	if (a[0] == '-')
	{
		sign *= -1;
		a = a.erase(0, 1);
	}
	if (b[0] == '-')
	{
		sign *= -1;
		b = b.erase(0, 1);
	}
	int i, j;
	string::size_type L1, L2;
	L1 = a.size();
	L2 = b.size();
	for (i = L2 - 1; i >= 0; i--)              //模拟手工乘法竖式
	{
		string tempstr;
		int int1 = 0, int2 = 0, int3 = int(b[i]) - '0';
		if (int3 != 0)
		{
			for (j = 1; j <= (int)(L2 - 1 - i); j++)
				tempstr = "0" + tempstr;
			for (j = L1 - 1; j >= 0; j--)
			{
				int1 = (int3 * (int(a[j]) - '0') + int2) % 10;
				int2 = (int3 * (int(a[j]) - '0') + int2) / 10;
				tempstr = char(int1 + '0') + tempstr;
			}
			if (int2 != 0)tempstr = char(int2 + '0') + tempstr;
		}
		str = ADD(str, tempstr);
	}
	//去除结果中的前导0
	str.erase(0, str.find_first_not_of("0"));
	if (str.empty())str = "0";
	if ((sign == -1) && (str[0] != '0'))str = "-" + str;
	return str;
}

// 大数除法
string BigInt::DIVIDE(string str1, string str2, int flag) {
	string quotient, residue;  //定义商和余数
	int sign1 = 1, sign2 = 1;
	if (str2 == "0")   //判断除数是否为0
	{
		quotient = "ERROR!";
		residue = "ERROR!";
		if (flag == 1)return quotient;
		else return residue;
	}
	if (str1 == "0")     //判断被除数是否为0
	{
		quotient = "0";
		residue = "0";
	}
	if (str1[0] == '-')
	{
		str1 = str1.erase(0, 1);
		sign1 *= -1;
		sign2 = -1;
	}
	if (str2[0] == '-')
	{
		str2 = str2.erase(0, 1);
		sign1 *= -1;
	}
	int res = compare(str1, str2);
	if (res < 0)
	{
		quotient = "0";
		residue = str1;
	}
	else if (res == 0)
	{
		quotient = "1";
		residue = "0";
	}
	else
	{
		string::size_type L1, L2;
		L1 = str1.size();
		L2 = str2.size();
		string tempstr;
		tempstr.append(str1, 0, L2 - 1); //将str1中为值0到L2-1的字符串追加到tempstr
		for (int i = L2 - 1; i < L1; i++)  //模拟手工除法竖式
		{
			tempstr = tempstr + str1[i];
			tempstr.erase(0, tempstr.find_first_not_of('0')); //在字符串中查找第一个与'0'不匹配的字符，返回它的位置
			if (tempstr.empty())tempstr = "0";  //q.empty()，当队列空时，返回true
			for (char ch = '9'; ch >= '0'; ch--) //试商
			{
				string str;
				str = str + ch;
				if (compare(MUL(str2, str), tempstr) <= 0)
				{
					quotient = quotient + ch;
					tempstr = SUB(tempstr, MUL(str2, str));
					break;
				}
			}
		}
		residue = tempstr;
	}
	//去除结果中的前导0
	quotient.erase(0, quotient.find_first_not_of("0"));
	if (quotient.empty())quotient = "0";
	if ((sign1 == -1) && (quotient[0] != '0'))quotient = "-" + quotient;
	if ((sign2 == -1) && (residue[0] != '0'))residue = "-" + residue;
	if (flag == 1)return quotient;
	else
		return residue;
}

// 求商
string BigInt::QUOTIENT(string a, string b) {
	return DIVIDE(a, b, 1);
}

// 求余
string BigInt::MOD(string a, string b) {
	return DIVIDE(a, b, 0);
}

// 幂运算
string BigInt::POW(string str, int pow) {
	string temp = str;
	if (pow == 0)
		return "1";
	for (int i = 0; i < pow-1; i++) {
		temp = MUL(temp, str);
	}
	return temp;
}

// 扩展欧几里得
string BigInt::exGcd(string a, string b, string& x, string& y) {
	if (compare(b,"0")==0) {
		x = "1";
		y = "0";
		return a;
	}
	
	string r = exGcd(b, MOD(a, b), x, y);
	string t = y;
	y = SUB(x, MUL(QUOTIENT(a, b), y));
	x = t;
	return r;
}

// 求最大公因数
string BigInt::gcd(string a, string b) {
	if (b == "0")
		return a;
	else
		return gcd(b, MOD(a, b));
}

// 十进制转十六进制
string BigInt::dec_2_hex(string dec) {
	string hex = "";
	string mod;
	while (dec != "0") {
		mod = MOD(dec, "16");
		if (mod.size() > 1) {
			hex.insert(0, 1, stoi(mod) - 10 + 'A');
		}
		else {
			hex = mod + hex;
		}
		dec = QUOTIENT(dec, "16");
	}
	return hex;
}

// 十六进制转十进制
string BigInt::hex_2_dec(string hex) {
	string dec = "0";
	char temp[5] = { '\x00' };
	string str;
	int num = 0;
	for (int i = hex.size() - 1, j = 0; i >= 0; i--, j++) {
		if ((hex[j] >= '0') && (hex[j] <= '9')) {
			num = hex[j] - 48;
		}
		else if ((hex[j] >= 'A') && (hex[j] <= 'F')) {
			num = hex[j] - 'A' + 10;
		}

		itoa(num, temp, 10);
		str = temp;
		dec = ADD(MUL(str, POW("16", i)), dec);
		str = "";
		memset(temp, '\x00', 5);
	}
	return dec;
}

// 求n在模p下的乘法逆元
string BigInt::inv(string n, string p) {
	string x, y;
	if (exGcd(n, p, x, y) == "1") {
		x = MOD(x, p);
		return compare(x, "0") ? x : ADD(p, x);
	}
	else {
		return "No inv";
	}
}

// 快速幂取模
string BigInt::fast_pow(string a, string b, string c) {
	string ans = "1";
	a = MOD(a, c); // 预处理，使得a处于c的数据范围之下
	while (b != "0") {
		if (MOD(b, "2") == "1") { // 奇数
			ans = MOD(MUL(ans, a), c); //消除指数为奇数的影响
		}
		b = QUOTIENT(b, "2"); //二进制的移位操作,不断的遍历b的二进制位
		a = MOD(MUL(a, a), c);  //不断的加倍
	}
	return ans;
}