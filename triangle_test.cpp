#include <iostream>
#include <string>

using namespace std;

string classify_triangle(int a, int b, int c)
{
	if (a < 0 || b < 0 || c < 0 || a > 100 || b > 100 || c > 100)
	{
		return "Invalid Input";
	}
	if (a + b <= c || a + c <= b || b + c <= a)
	{
		return "Not a Triangle";
	}
	if (a == b && b == c)
	{
		return "Equilateral";
	}
	if (a == b || b == c || a == c)
	{
		return "Isosceles";
	}
	return "Scalene";
}

int main()
{
	int a, b, c;

	cout << "Nhap 3 canh tam giac (cach nhau boi khoang trang): ";

	if (cin >> a >> b >> c)
	{
		string result = classify_triangle(a, b, c);
		cout << "=> Ket qua phan loai: " << result << "\n";
	}
	else
	{
		cout << "=> Loi: Vui long nhap so nguyen!\n";
	}

	return 0;
}