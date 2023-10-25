#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{0, "Неопределено"},
	{1, "Превышение скорости" },
	{2, "Парковка в неположенном месте" },
	{3, "Проезд на красный" },
	{4, "Езда в нетрезвом состоянии" },
	{5, "Оскорбление офицера" },
	{6, "Неподчинение приказам офицера" },
	{7, "Пересечение сплошной" },
	{8, "Оставление места ДТП" },
	{9, "Ремень безопасности" },
};

class Crime
{
	int id;				//номер статьи
	std::string place;	//место нарушения
	time_t time;		//время нарушения
public:
	int get_id()const
	{
		return id;
	}
	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_place()const
	{
		return place;
	}
	const char* get_time()const
	{
		return ctime(&time);
	}
	time_t get_timestamp()const
	{
		return time;
	}
	void set_id(int id)
	{
		if (id >= VIOLATIONS.size()) id = 0;
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const char time_str[])
	{
		const int SIZE = 20;
		char time_str_buffer[SIZE] = {};
		strcpy(time_str_buffer, time_str);
		//hh:mm DD/MM/YY
		//hh:mm DD.MM.YY
		//YYYY/MM/DD hh:mm
		int units[5] = {};
		char* sz_units[5] = {};
		const char delimiters[] = ":./ ";
		int n = 0;
		for (char* pch = strtok(time_str_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			units[n++] = std::atoi(pch);
		for (int i : units) cout << i << tab; cout << endl;
		int colon_position = strchr(time_str, ':') - time_str;
		if (colon_position > 2)
		{
			std::reverse(units, units + 5);
			std::swap(units[0], units[1]);
		}
		for (int i : units) cout << i << tab; cout << endl;
		std::tm tm{};
		tm.tm_hour = units[0];
		tm.tm_min = units[1];
		tm.tm_mday = units[2];
		tm.tm_mon = units[3] - 1;
		tm.tm_year = units[4] - 1900;
		this->time = std::mktime(&tm);
	}

	Crime(int id, const std::string& place, const std::string& time)
	{
		set_id(id);
		set_place(place);
		set_time(time.c_str());
	}
	~Crime() {};
};
std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	const int SIZE = 32;
	char crime_time[SIZE]{};
	strcpy(crime_time, obj.get_time());
	crime_time[strlen(crime_time) - 1] = 0;
	return os << crime_time << ": " << obj.get_place() << ", " << obj.get_violation();
}

void main()
{
	setlocale(LC_ALL, "");
	/*Crime crime;
	crime.set_time("16:20 24/10/2023");
	cout << delimiter << endl;
	crime.set_time("2023/10/24 4:20");*/

	Crime crime(1, "ул. Ленина", "16:20 24/10/2023");
	cout << crime << endl;
}