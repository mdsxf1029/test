/* 2354264 信11 谢雨霏 */
#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
	const double pi = 3.14159;
	double r, h;
	cout << "请输入半径和高度" << endl;
	cin >> r >> h;
	double c, s, S, v, V;
	c = 2 * pi * r;
	s = pi * r * r;
	S = 4 * pi * r * r;
	v = pi * r * r * r * 4 / 3;
	V = pi * r * r * h;
	cout << setiosflags(ios::fixed);
	cout << setprecision(2) << "圆周长     : " << c << endl;
	cout << setprecision(2) << "圆面积     : " << s << endl;
	cout << setprecision(2) << "圆球表面积 : " << S << endl;
	cout << setprecision(2) << "圆球体积   : " << v << endl;
	cout << setprecision(2) << "圆柱体积   : " << V << endl;
	return 0;
}