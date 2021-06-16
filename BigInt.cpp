#include<iostream>
#include<string>
#include "BigInt.h"

//��ȷ���0�����ڷ���1��С�ڷ���-1
inline int BigInt::compare(string a, string b) { 
	if (a.size() > b.size()) {
		return 1;
	}
	else if (a.size() < b.size()) {
		return -1;
	}
	else return a.compare(b); //��������ȣ����ͷ��β��λ�Ƚ�
}

// �����ӷ�
string BigInt::ADD(string a, string b) {
	int sign = 1;// signΪ����Ϊ
	string str;
	if (a[0] == '-')
	{
		if (b[0] == '-')       //����
		{
			sign = -1;
			str = ADD(a.erase(0, 1), b.erase(0, 1));//erase(first,last);ɾ����first��last֮����ַ�
		}
		else             //����
		{
			str = SUB(b, a.erase(0, 1));
		}
	}
	else
	{
		if (b[0] == '-')        //����
		{
			str = SUB(a, b.erase(0, 1));
		}
		else                    //�������������������룬������ǰ���0����
		{
			string::size_type L1, L2;  //string::size_type���������ǳߴ絥λ����
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
	//������������
	if ((sign == -1) && (str[0] != '0'))str = "-" + str;
	return str;
}

// ������������
string BigInt::SUB_unsigned(string a, string b) {
	int sign = 1; //signΪ����λ
	string str;
	int i, j;

	int res = compare(a, b);
	if (res == 0)return "0";
	if (res < 0)
	{
		sign = -1; // ���Ӧ���Ǹ���
		string temp = a;
		a = b;
		b = temp;
	}
	string::size_type tempint;
	tempint = a.size() - b.size();
	for (i = b.size() - 1; i >= 0; i--)
	{
		if (a[i + tempint] < b[i])          //��λ
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

	//ȥ������ж����ǰ��0
	str.erase(0, str.find_first_not_of('0'));
	if (str.empty())str = "0";
	if ((sign == -1) && (str[0] != '0'))
		str = "-" + str;
	return str;
}

// ��������
string BigInt::SUB(string a, string b) {
	int sign = 1;
	char sign_a = a[0];
	char sign_b = b[0];
	string ans;

	int res = compare(a, b);
	if (res == 0)
		return "0";

	if (sign_a == '-') {
		if (sign_b == '-') { // �������൱��b-a
			ans = SUB_unsigned(b.erase(0,1), a.erase(0,1));
			return ans;
		}
		else { // �������൱��-(a+b)
			ans = ADD(a.erase(0,1), b);
			ans = '-' + ans;
			return ans;
		}
	}
	else {
		if (sign_b == '-') { // �������൱��a+b
			return ADD(a, b.erase(0,1));
		}
		else { // ������a-b
			return SUB_unsigned(a, b);
		}
	}

}

// �����˷�
string BigInt::MUL(string a, string b){
	int sign = 1;
	string str = "0";        //��¼��ǰֵ
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
	for (i = L2 - 1; i >= 0; i--)              //ģ���ֹ��˷���ʽ
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
	//ȥ������е�ǰ��0
	str.erase(0, str.find_first_not_of("0"));
	if (str.empty())str = "0";
	if ((sign == -1) && (str[0] != '0'))str = "-" + str;
	return str;
}

// ��������
string BigInt::DIVIDE(string str1, string str2, int flag) {
	string quotient, residue;  //�����̺�����
	int sign1 = 1, sign2 = 1;
	if (str2 == "0")   //�жϳ����Ƿ�Ϊ0
	{
		quotient = "ERROR!";
		residue = "ERROR!";
		if (flag == 1)return quotient;
		else return residue;
	}
	if (str1 == "0")     //�жϱ������Ƿ�Ϊ0
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
		tempstr.append(str1, 0, L2 - 1); //��str1��Ϊֵ0��L2-1���ַ���׷�ӵ�tempstr
		for (int i = L2 - 1; i < L1; i++)  //ģ���ֹ�������ʽ
		{
			tempstr = tempstr + str1[i];
			tempstr.erase(0, tempstr.find_first_not_of('0')); //���ַ����в��ҵ�һ����'0'��ƥ����ַ�����������λ��
			if (tempstr.empty())tempstr = "0";  //q.empty()�������п�ʱ������true
			for (char ch = '9'; ch >= '0'; ch--) //����
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
	//ȥ������е�ǰ��0
	quotient.erase(0, quotient.find_first_not_of("0"));
	if (quotient.empty())quotient = "0";
	if ((sign1 == -1) && (quotient[0] != '0'))quotient = "-" + quotient;
	if ((sign2 == -1) && (residue[0] != '0'))residue = "-" + residue;
	if (flag == 1)return quotient;
	else
		return residue;
}

// ����
string BigInt::QUOTIENT(string a, string b) {
	return DIVIDE(a, b, 1);
}

// ����
string BigInt::MOD(string a, string b) {
	return DIVIDE(a, b, 0);
}

// ������
string BigInt::POW(string str, int pow) {
	string temp = str;
	if (pow == 0)
		return "1";
	for (int i = 0; i < pow-1; i++) {
		temp = MUL(temp, str);
	}
	return temp;
}

// ��չŷ�����
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

// ���������
string BigInt::gcd(string a, string b) {
	if (b == "0")
		return a;
	else
		return gcd(b, MOD(a, b));
}

// ʮ����תʮ������
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

// ʮ������תʮ����
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

// ��n��ģp�µĳ˷���Ԫ
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

// ������ȡģ
string BigInt::fast_pow(string a, string b, string c) {
	string ans = "1";
	a = MOD(a, c); // Ԥ����ʹ��a����c�����ݷ�Χ֮��
	while (b != "0") {
		if (MOD(b, "2") == "1") { // ����
			ans = MOD(MUL(ans, a), c); //����ָ��Ϊ������Ӱ��
		}
		b = QUOTIENT(b, "2"); //�����Ƶ���λ����,���ϵı���b�Ķ�����λ
		a = MOD(MUL(a, a), c);  //���ϵļӱ�
	}
	return ans;
}