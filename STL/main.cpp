#include <iostream>
#include <array>
#include <vector>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T> void vector_properties(const std::vector<T>& vec);

//#define STL_ARRAY
#define STL_VECTOR

void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY
	// array - это контейнер, который хранит данные в виде статического массива
	const int N = 5;
	std::array<int, N> arr = { 3, 5, 8 };
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // STL_ARRAY

#ifdef STL_VECTOR
	// vector - это контейнер, который хранит данные в виде динамического массива
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
	vector_properties(vec);
	vec.push_back(55);
	vector_properties(vec);
#endif // STL_VECTOR


}

template<typename T> void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:\t" << vec.size() << endl;
	cout << "Capacity:\t" << vec.capacity() << endl;
	cout << "Max size:\t" << vec.max_size() << endl;
}