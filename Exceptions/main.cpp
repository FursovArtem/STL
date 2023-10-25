#include <iostream>
#include <exception>
using std::cin;
using std::cout;
using std::endl;


void main()
{
	setlocale(LC_ALL, "");
	try
	{
		throw std::exception("throwing exception from main()");
		int a, b;
		cout << "������� ��� �����: "; cin >> a >> b;
		cout << a / b << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	catch (...)
	{
		std::cerr << "���-�� ����� �� ���..." << endl;
	}
}