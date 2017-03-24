#include "QInt.h"
/*
Hàm khởi tạo mặc định
Khởi tạo 0 cho 2 phần tử
*/
QInt::QInt()
{
	arrayBits[0] = arrayBits[1] = 0;
}

/*
Hàm khởi tạo từ một chuỗi nhị phân cho trước
*/
QInt::QInt(string binaryString, int pos)
{
	arrayBits[0] = arrayBits[1] = 0;
	int length = binaryString.length();
	for (int i = length - 1; i > -1; i--)
	{
		SetBit(val(binaryString[i]), pos);
		pos++;
	}
}

/*
Hàm khởi tạo từ một chuỗi số thập phân
*/
QInt::QInt(string decimalString)
{
	arrayBits[0] = arrayBits[1] = 0;
	int pos = 0;
	while (decimalString != "0")
	{
		int bit = (decimalString[decimalString.length() - 1] - 48) % 2;
		SetBit(bit, pos);
		pos++;
		decimalString = stringDiv2(decimalString);
	}
}
/*
Hàm đổi chuỗi nhị phân sang dạng bù 2
*/
string QInt::ConvertToMinusBinary(string binary)
{
	for (int i = 0; i < binary.length(); i++)
	{
		if (binary[i] == '0')
			binary[i] = '1';
		else
			binary[i] = '0';
	}
	binary = BinaryAdd(binary, "1");
	return binary;
}

/*
Hàm cộng 2 chuỗi số thập phân
*/
string QInt::stringAdd(string a, string b)
{
	int alen = a.length();
	int blen = b.length();
	if (blen > alen)
	{
		string t = a;
		a = b;
		b = t;
		int tmp = alen;
		alen = blen;
		blen = tmp;
	}
	char *c = new char[alen];
	int carry = 0;//Bien nho khi cong vao lon hon 10.
	for (int i = alen - 1; i >= 0; i--)
	{
		int dva = a[i] - 48;
		int j = i - (alen - blen);
		int dvb;
		if (j < 0) dvb = 0;
		else dvb = b[j] - 48;

		int s = dva + dvb + carry;
		if (s >= 10)
		{
			c[i] = s % 10 + 48;
			carry = 1;
		}
		else
		{
			c[i] = s + 48;
			carry = 0;
		}
	}
	if (carry == 1)
	{
		char *kq = new char[alen + 1];
		kq[0] = '1';
		for (int i = 0; i < alen; i++)
		{
			kq[i + 1] = c[i];
		}
		string rs(kq, alen + 1);
		return rs;
	}
	else
	{
		string rs(c, alen);
		return rs;
	}
}


/*
Hàm nhân 2 chuỗi số thập phân
*/
string QInt::stringMulti(string a, string b)
{
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	string c;
	int a_length = a.length();
	int b_length = b.length();
	int ib = 0;
	string temp;
	do
	{
		temp = "";
		int ia = 0;
		int carry = 0;
		do
		{
			temp.push_back(chrMul(a[ia], b[ib], carry));
			ia++;
		} while (ia != a_length);
		if (carry)
			temp.push_back(chr(carry));

		reverse(temp.begin(), temp.end());

		if (ib == 0)
			c = temp;
		else
		{
			temp.insert(temp.end(), ib, '0');
			c = stringAdd(c, temp);
		}
		ib++;
	} while (ib != b_length);
	return c;
}


/*
Hàm chia chuỗi số thập phân cho 2
*/
string QInt::stringDiv2(string str)
{

	string temp;
	unsigned short int i = 0, j = 0, k = 0;
	if (str == "1" || str == "0")
		return "0";

	temp.resize(str.length());
	if (str[0] - 48 < 2)
	{
		i = 1;
		j = 10;
	}
	for (; i < str.length(); i++)
	{
		temp[k++] = ((str[i] - 48 + j) / 2 + 48);
		j = ((str[i] - 48 + j) % 2) * 10;
	}
	temp.resize(k);
	return temp;
}
/*
hàm cộng 2 chuỗi nhị phân 128bit
*/
string QInt::BinaryAdd(string bit1, string bit2)
{
	std::stringstream ss;
	if (bit1.length() > bit2.length())
	{
		ss << std::setw(128) << std::setfill('0') << bit2;
		bit2 = ss.str();
	}
	else
	{
		ss << std::setw(128) << std::setfill('0') << bit1;
		bit1 = ss.str();
	}
	string result = "";
	char save = '0';
	for (int i = bit1.length() - 1; i >= 0; i--)
	{
		if (bit1[i] == '1' && bit2[i] == '1')
		{
			if (save == '0')
				result.insert(0, 1, '0');
			else
				result.insert(0, 1, '1');
			save = '1';

		}
		else if (bit1[i] == '0' && bit2[i] == '0')
		{
			if (save == '0')
				result.insert(0, 1, '0');
			else
				result.insert(0, 1, '1');
			save = '0';
		}
		else if (bit1[i] - bit2[i] != 0)
		{
			if (save == '0')
			{
				result.insert(0, 1, '1');
				save = '0';
			}
			else
			{
				result.insert(0, 1, '0');
				save = '1';
			}
		}
	}
	return Strim(result);
	//return string();
}
/*
Hàm chia 2 chuỗi nhị phân
*/
string QInt::BinaryDivBinary(string& binaryQ, string binaryM)
{
	//Đưa tất cả các chuỗi nhi phân về cùng độ dài
	std::stringstream ss;
	if (binaryQ.length() > binaryM.length())
	{
		ss << std::setw(binaryQ.length()) << std::setfill('0') << binaryM;
		binaryM = ss.str();
	}
	else
	{
		ss << std::setw(binaryM.length()) << std::setfill('0') << binaryQ;
		binaryQ = ss.str();
	}
	stringstream ss2;
	ss2 << std::setw(binaryQ.length()) << std::setfill('0') << "";
	std::string binaryA = ss2.str();
	char Q0 = '0';
	int count = binaryA.length();

	//Thuật toán chia
	while (count != 0)
	{
		//Dịch A Q

		binaryA.insert(binaryA.end(), binaryQ[0]);
		binaryA.erase(0, 1);
		binaryQ.erase(0, 1);
		//Hàm cộng 2 
		binaryA = BinaryAdd(binaryA, ConvertToMinusBinary(binaryM));

		if (binaryA[0] == '1')
		{
			binaryA = BinaryAdd(binaryA, binaryM);
			Q0 = '0';
			binaryQ.insert(binaryQ.end(), Q0);
		}
		else
		{
			Q0 = '1';
			binaryQ.insert(binaryQ.end(), Q0);
		}
		count--;
	}
	return binaryA;
}

/*
Hàm xoá ký tự thừa
ví dụ : '000001010101'
sau khi xoá : '1010101'
*/
string QInt::Strim(string str)
{
	int i = 0;
	while (str[i++] == '0');
	string res;
	res.insert(res.begin(), str.begin() + i - 1, str.end());
	return res;
}


/*
Chuyển đổi từ QInt sang Binary
*/
string QInt::convertToBinary()
{
	string temp = "";
	for (int i = 127; i >= 0; i--)
	{
		int bit = GetBit(i);
		temp.push_back(bit + '0');
	}
	return temp;
}

/*
Chuyển đổi chuỗi nhị phân sang chuỗi thập phân
*/
string QInt::convertFormBinaryToDecimal()
{
	string res;
	string temp = Strim(convertToBinary());
	string TwoMul = "1";
	reverse(temp.begin(), temp.end());
	if (temp[0] == '0')
	{
		res = "0";
	}
	else
	{
		res = "1";
	}
	for (int i = 1; i < temp.length(); i++)
	{
		TwoMul = stringMulti(TwoMul, "2");
		if (temp[i] == '1')
			res = stringAdd(res, TwoMul);
	}
	return res;
}

/*
Chuyển đổi chuỗi nhị phân sang thập lục phân
*/
string QInt::convertFromBinaryToHexa(string binaryString)
{
	map<string, char> HexaTable;
	HexaTable["0000"] = '0';
	HexaTable["0001"] = '1';
	HexaTable["0010"] = '2';
	HexaTable["0011"] = '3';
	HexaTable["0100"] = '4';
	HexaTable["0101"] = '5';
	HexaTable["0110"] = '6';
	HexaTable["0111"] = '7';
	HexaTable["1000"] = '8';
	HexaTable["1001"] = '9';
	HexaTable["1010"] = 'A';
	HexaTable["1011"] = 'B';
	HexaTable["1100"] = 'C';
	HexaTable["1101"] = 'D';
	HexaTable["1110"] = 'E';
	HexaTable["1111"] = 'F';

	string res = "";
	int n = binaryString.length();

	if (n % 4 != 0)
	{
		binaryString.insert(binaryString.begin(), 4 - (n % 4), '0');
	}

	n = binaryString.length();
	string _4Bit;
	_4Bit.resize(4);
	for (int i = 0; i < n; i = i + 4)
	{
		for (int j = 0; j < 4; j++)
			_4Bit[j] = binaryString[i + j];
		res.push_back(HexaTable[_4Bit]);
	}
	return res;
}

/*
Chuyển đổi QInt sang thập lục phân
*/
string QInt::convertToHexa()
{
	map<string, char> HexaTable;
	HexaTable["0000"] = '0';
	HexaTable["0001"] = '1';
	HexaTable["0010"] = '2';
	HexaTable["0011"] = '3';
	HexaTable["0100"] = '4';
	HexaTable["0101"] = '5';
	HexaTable["0110"] = '6';
	HexaTable["0111"] = '7';
	HexaTable["1000"] = '8';
	HexaTable["1001"] = '9';
	HexaTable["1010"] = 'A';
	HexaTable["1011"] = 'B';
	HexaTable["1100"] = 'C';
	HexaTable["1101"] = 'D';
	HexaTable["1110"] = 'E';
	HexaTable["1111"] = 'F';

	string res = "";
	string temp = Strim(convertToBinary());
	int n = temp.length();

	if (n % 4 != 0)
	{
		temp.insert(temp.begin(), 4 - (n % 4), '0');
	}

	n = temp.length();
	string _4Bit;
	_4Bit.resize(4);
	for (int i = 0; i < n; i = i + 4)
	{
		for (int j = 0; j < 4; j++)
			_4Bit[j] = temp[i + j];
		res.push_back(HexaTable[_4Bit]);
	}
	return res;
}
/*
Toán tử =
*/
QInt QInt::operator=(QInt Q2)
{
	this->arrayBits[0] = Q2.arrayBits[0];
	this->arrayBits[1] = Q2.arrayBits[1];
	return *this;
}
/*
Cộng hai QInt
*/
QInt QInt::operator+(QInt Q2)
{
	string binaryresult = BinaryAdd(this->convertToBinary(), Q2.convertToBinary());
	QInt temp(binaryresult, 0);
	return temp;
}
/*
Trừ hai QInt
*/
QInt QInt::operator-(QInt Q2)
{
	string binaryresult = BinaryAdd(this->convertToBinary(), ConvertToMinusBinary(Q2.convertToBinary()));
	QInt temp(binaryresult, 0);
	return temp;
}
/*
Chia lấy thương 2 QInt
*/
QInt QInt::operator/(QInt Q2)
{
	string binaryQ = this->convertToBinary();
	string binaryresult = BinaryDivBinary(binaryQ, Q2.convertToBinary());
	QInt temp(binaryQ, 0);
}
/*
Chia lấy dư 2 QInt
*/
QInt QInt::operator%(QInt Q2)
{
	string binaryQ = this->convertToBinary();
	string binaryresult = BinaryDivBinary(binaryQ, Q2.convertToBinary());
	QInt temp(binaryresult, 0);;
}
/*
Toán tử AND
*/
QInt QInt::operator&(QInt Q2)
{
	QInt temp;
	for (int i = 0; i < 128; i++)
		temp.SetBit(GetBit(i) & Q2.GetBit(i), i);
	return temp;
}
/*
Toán tử OR
*/
QInt QInt::operator|(QInt Q2)
{
	QInt temp;
	for (int i = 0; i < 128; i++)
		temp.SetBit(GetBit(i) | Q2.GetBit(i) , i);
	return temp;
}
/*
Toán tử NOT
*/
QInt QInt::operator~()
{
	for (int i = 0; i < 128; i++)
		SetBit(~GetBit(i), i);
	return *this;
}
/*
Toán tử XOR
*/
QInt QInt::operator^(QInt Q2)
{
	QInt temp;
	for (int i = 0; i < 128; i++)
		temp.SetBit(GetBit(i) ^ Q2.GetBit(i), i);
	return temp;
}

QInt QInt::operator<<(int count)
{
	return QInt();
}

/*
get bit ở vị trí pos
nếu pos < 64 , get bit của  arrayBits[0];
nếu  64 <= pos < 127, get bit của arrayBits[1];
*/
int QInt::GetBit(int pos)
{
	if ((pos < 64 && pos >= 0))
	{
		return (arrayBits[0] >> pos) & 1;
	}
	else if (pos >= 64 && pos < 128)
	{
		return (arrayBits[1] >> (pos - 64)) & 1;
	}
}

/*
Set bit ở vị trí pos
nếu pos < 64 , set vào arrayBits[0];
nếu  64 <= pos < 127, set vào arrayBits[1];
*/
void QInt::SetBit(int bit, int pos)
{
	if (pos < 64 && pos >= 0)
	{
		if (bit == 0)
		{
			arrayBits[0] = ~((__int64)1 << pos) & arrayBits[0];
		}
		else
		{
			arrayBits[0] = ((__int64)1 << pos) | arrayBits[0];
		}
	}
	else if (pos >= 64 && pos < 128)
	{
		if (bit == 0)
		{
			arrayBits[1] = ~((__int64)1 << (pos - 64)) & arrayBits[1];
		}
		else
		{
			arrayBits[1] = ((__int64)1 << (pos - 64)) | arrayBits[1];
		}
	}
}

