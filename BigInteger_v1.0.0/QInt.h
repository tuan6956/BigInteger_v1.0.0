// Version 1.0.0
// Chỉ thao tác trên số dương

#ifndef _QINT_H
#define _QINT_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
using namespace std;



class QInt
{
private:
	/*
	Mảng arrayBits có 2 phần tử
	Phần tử arrayBits[0] lưu các bit từ 0 -> 63
	Phần tử arrayBits[1] lưu các bit từ 64->127
	*/
	__int64 arrayBits[2];
public:
#pragma region Hepler
	/*
	get bit ở vị trí pos
	nếu pos < 64 , get bit của  arrayBits[0];
	nếu  64 <= pos < 127, get bit của arrayBits[1];
	*/
	int GetBit(int pos);

	/*
	Set bit ở vị trí pos
	nếu pos < 64 , set vào arrayBits[0];
	nếu  64 <= pos < 127, set vào arrayBits[1];
	*/
	void SetBit(int bit, int pos);

	/*
	nhận vào ký tự chữ số từ '0' đến '9'
	trả về số
	*/
	int val(char chr)
	{
		return chr - '0';
	}

	/*
	nhận vào số từ 0 đến 9
	trả về ký tự chữ số
	*/
	char chr(int num)
	{
		return num + '0';
	}

	/*
	Nhân ký tự số a với ký tự số b
	*/
	char chrMul(char a, char b, int&carry)
	{
		int temp = val(a)*val(b) + carry;
		carry = temp / 10;
		return chr(temp % 10);
	}
#pragma endregion


#pragma region Constructor
	/*
	Hàm khởi tạo mặc định
	Khởi tạo 0 cho 2 phần tử
	*/
	QInt();

	/*
	Hàm khởi tạo từ một chuỗi nhị phân cho trước tại vị trí pos
	*/
	QInt(string binaryString, int pos);

	/*
	Hàm khởi tạo từ một chuỗi số thập phân
	*/
	QInt(string decimalString);

	

#pragma endregion

#pragma region Main
	/*
	Hàm đổi chuỗi nhị phân sang dạng bù 2
	*/
	string ConvertToMinusBinary(string binary);
	/*
	Hàm cộng 2 chuỗi số thập phân
	*/
	string stringAdd(string a, string b);

	/*
	Hàm nhân 2 chuỗi số thập phân
	*/
	string stringMulti(string a, string b);

	/*
	Hàm chia chuỗi số thập phân cho 2
	*/
	string stringDiv2(string str);
	/*
	Hàm cộng 2 chuỗi nhị phân
	*/
	string BinaryAdd(string binarya,string binaryb);
	/*
	Hàm chia 2 chuỗi nhị phân
	*/
	string BinaryDivBinary(string& binaryQ, string binaryM);
	/*
	Hàm xoá ký tự thừa
	ví dụ : '000001010101'
	sau khi xoá : '1010101'
	*/
	string Strim(string str);
	/*
	Chuyển đổi từ QInt sang Binary
	*/
	string convertToBinary();

	/*
	Chuyển đổi chuỗi nhị phân sang chuỗi thập phân
	*/
	string convertFormBinaryToDecimal();
	

	/*
	Chuyển đổi chuỗi nhị phân sang thập lục phân
	*/
	string convertFromBinaryToHexa(string binaryString);

	/*
	Chuyển đổi QInt sang thập lục phân
	*/
	string convertToHexa();
#pragma endregion
#pragma region Operator
	QInt operator= (QInt Q2);
	QInt operator+ (QInt Q2);
	QInt operator- (QInt Q2);
	QInt operator* (QInt Q2);
	QInt operator/ (QInt Q2);
	QInt operator% (QInt Q2);
	QInt operator& (QInt Q2);
	QInt operator|(QInt Q2);
	QInt operator~();
	QInt operator^(QInt Q2);
	QInt operator<<(int count);
	QInt operator>>(int count);


#pragma endregion





};



#endif
