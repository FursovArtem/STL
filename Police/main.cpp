#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<fstream>
#include<string>
#include<ctime>
#include<list>
#include<map>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------------------\n"

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
	int id;
	std::string place;
	time_t time;
public:
	int get_id()const
	{
		return id;
	}
	const std::string get_vilation()const
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
		if (id >= VIOLATIONS.size())id = 0;
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(time_t time)
	{
		this->time = time;
	}
	void set_time(const char time_str[])
	{
		const int SIZE = 20;
		char time_str_buffer[SIZE] = {};
		strcpy(time_str_buffer, time_str);
		//hh:mm DD/MM/YYYY
		//hh:mm DD.MM.YYYY
		//YYYY/MM/DD hh:mm
		int units[5] = {};
		char* sz_units[5] = {};
		const char delimiters[] = ":./ ";
		int n = 0;
		for (char* pch = strtok(time_str_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			units[n++] = std::atoi(pch);
		//for (int i : units)cout << i << tab; cout << endl;
		//for (char* i : sz_units)cout << i << tab; cout << endl;
		int colon_position = strchr(time_str, ':') - time_str;
		if (colon_position > 2)
		{
			std::reverse(units, units + 5);
			std::swap(units[0], units[1]);
		}
		//for (int i : units)cout << i << tab; cout << endl;
		//for (char* i : sz_units)cout << i << tab; cout << endl;
		std::tm tm{};
		tm.tm_hour = units[0];
		tm.tm_min = units[1];
		tm.tm_mday = units[2];
		tm.tm_mon = units[3] - 1;
		tm.tm_year = units[4] - 1900;
		this->time = std::mktime(&tm);
	}

	Crime()
	{
		id = 0;
		place = "undefined";
		time = 0;
	}
	Crime(int id, const std::string& place, const std::string& time)
	{
		set_id(id);
		set_place(place);
		set_time(time.c_str());
	}
	~Crime() {}
};
std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	const int SIZE = 32;
	char crime_time[SIZE]{};
	strcpy(crime_time, obj.get_time());
	crime_time[strlen(crime_time) - 1] = 0;
	return os << crime_time << ": " << obj.get_place() << ", " << obj.get_vilation();
}
std::ofstream& operator<<(std::ofstream& ofs, const Crime& obj)
{
	ofs << obj.get_timestamp() << " " << obj.get_place() << " " << obj.get_id();
	return ofs;
}

class LicencePlate
{
	std::string plate;
public:
	const std::string& get_plate()const
	{
		return plate;
	}
	void set_plate(const std::string& plate)
	{
		if (plate.size() < 10)this->plate = plate;
		else this->plate = "BadFormat";
	}
	LicencePlate() {}
	LicencePlate(const std::string& plate)
	{
		set_plate(plate);
	}
	~LicencePlate() {}

	bool operator<(const LicencePlate& other)const
	{
		return this->plate < other.plate;
	}
	bool operator>(const LicencePlate& other)const
	{
		return this->plate > other.plate;
	}

};

std::ostream& operator<<(std::ostream& os, const LicencePlate& obj)
{
	return os << obj.get_plate();
}
std::ifstream& getline(std::ifstream& ifs, LicencePlate& obj, char delim)
{
	std::string plate;
	std::getline(ifs, plate, delim);
	obj.set_plate(plate);
	return ifs;
}

void print(const std::map<LicencePlate, std::list<Crime>>& base);
void save(const std::map<LicencePlate, std::list<Crime>>& base, const std::string& filename);
std::map<LicencePlate, std::list<Crime>> load(const std::string& filename);

void main()
{
	setlocale(LC_ALL, "");
	/*Crime crime;
	crime.set_time("16:20 24/10/2023");
	cout << delimiter << endl;
	crime.set_time("2023/10/24 4:20");*/

	/*Crime crime(1, "ул. Ленина", "16:20 24/10/2023");
	cout << crime << endl;*/

	/*LicencePlate plate("m777ab"); cout << plate << endl;
	LicencePlate plate_1("VasyaTupenko"); cout << plate_1 << endl;*/

	/*std::map<LicencePlate, std::list<Crime>> base =
	{
		{LicencePlate("m777ab"), {Crime(1, "ул. Ленина", "12:20 18.05.2023"), Crime(3, "ул. Ленина", "12:20 18.05.2023")}},
		{LicencePlate("m001bb"), {Crime(4, "ул. Космонавтов", "22:20 20.10.2023"), Crime(5, "ул. Космонавтов", "22:30 20.10.2023"), Crime(6, "ул. Космонавтов", "22:33 20.10.2023")}},
		{LicencePlate("a121bc"), {Crime(2, "ул. Пушкина", "14:25 22.10.2023"), Crime(9, "ул. Пушкина", "14:25 22.10.2023")}},
	};
	print(base);
	save(base, "base.txt");*/
	std::map<LicencePlate, std::list<Crime>> base = load("base.txt");
}

void print(const std::map<LicencePlate, std::list<Crime>>& base)
{
	for (std::map<LicencePlate, std::list<Crime>>::const_iterator bit = base.begin(); bit != base.end(); ++bit)
	{
		cout << bit->first << ":\n";
		for (std::list<Crime>::const_iterator it = bit->second.begin(); it != bit->second.end(); ++it)
		{
			cout << tab << *it << ";\n";
		}
		cout << endl;
	}
}
void save(const std::map<LicencePlate, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<LicencePlate, std::list<Crime>>::const_iterator bit = base.begin(); bit != base.end(); ++bit)
	{
		fout << bit->first << ":";
		for (std::list<Crime>::const_iterator it = bit->second.begin(); it != bit->second.end(); ++it)
		{
			fout << *it << ", ";
		}
		int position = fout.tellp();
		fout.seekp(position - 2);
		fout << ";\n";
	}
	fout.close();
	std::string command = "start notepad " + filename;
	system(command.c_str());
}
std::map<LicencePlate, std::list<Crime>> load(const std::string& filename)
{
	std::map<LicencePlate, std::list<Crime>> base;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			LicencePlate plate;
			getline(fin, plate, ':');
			std::string all_crimes;
			std::getline(fin, all_crimes);
			cout << plate << tab << all_crimes << endl;
		}
		fin.close();
	}
	else std::cerr << "Error: file not found";
	return base;
}