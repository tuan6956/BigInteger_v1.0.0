
#ifndef  _CONVERT_H
#define _CONVERT_H


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



#endif // ! _CONVERT.H
