//Header library for C++, syntax is similar to C# for easy manipulation
//https://github.com/trietta1999/CPP-Custom-Library

#ifndef cpp_custom_lib_h
#define cpp_custom_lib_h
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <windows.h>

using namespace std;

namespace Custom {
	template<typename T>
	string GetType(T value) {
		return typeid(value).name();
	}

	template<typename T>
	T Min(T a[]) {
		T min = a[0];
		for (int i = 0; i < sizeof(a) - 1; i++)
			if (a[i + 1] < a[i]) min = a[i + 1];
		return min;
	}

	template<typename T>
	T Max(T a[]) {
		T max = a[0];
		for (int i = 0; i < sizeof(a) - 1; i++)
			if (a[i + 1] > a[i]) max = a[i + 1];
		return max;
	}
}

namespace String {
	template<typename T>
	string Parse(T value) {
		return to_string(value);
	}

	string Parse(const char* value) {
		string str(value);
		return str;
	}

	string Parse(char value[]) {
		string str(value);
		return str;
	}

	vector<string> Split(string str, string separator)
	{
		int start = 0, i = 0;
		int end = str.find(separator);
		vector<string> sout;
		while (end != -1) {
			sout.push_back(str.substr(start, end - start));
			i++;
			start = end + separator.size();
			end = str.find(separator, start);
		}
		return sout;
	}

	vector<string> Sort(vector<string> strVec) {
		vector<string> strOut;
		vector<string> tempVec;

		vector<string>::iterator istr;
		int i = 0;
		for (istr = strVec.begin(); istr != strVec.end(); istr++) {
			tempVec.push_back((*istr) + "_" + to_string(i) + "_");
			i++;
		}
		sort(tempVec.begin(), tempVec.end());

		i = 0;
		for (istr = tempVec.begin(); istr != tempVec.end(); istr++) {
			auto str = Split((*istr), "_");
			strOut.push_back(str.at(0));
			i++;
		}
		return strOut;
	}

	void Insert(string& str, string insert_str, int start, int len_str) {
		while (str.length() < len_str) str.insert(start, insert_str);
	}
}

namespace Double {
	double Parse(string value) {
		return stod(value);
	}

	bool TryParse(string value, double& out) {
		auto result = double();
		auto i = std::istringstream(value);
		i >> result;
		if (!i.fail() && i.eof()) {
			out = Parse(value);
			return true;
		}
		return false;
	}
}

namespace Int {
	int Parse(string value) {
		return stoi(value);
	}

	bool TryParse(string value, int& out) {
		string::const_iterator it = value.begin();
		while (it != value.end() && isdigit(*it)) ++it;
		if (!value.empty() && it == value.end()) {
			out = Parse(value);
			return true;
		}
		return false;
	}
}

namespace LongLong {
	long long Parse(string value) {
		return stoll(value);
	}

	bool TryParse(string value, long long& out) {
		string::const_iterator it = value.begin();
		while (it != value.end() && isdigit(*it)) ++it;
		if (!value.empty() && it == value.end()) {
			out = Parse(value);
			return true;
		}
		return false;
	}
}

namespace File {
	vector<string> ReadLine(string fileName) {
		ifstream file;
		vector<string> read;

		file.open(fileName);
		if (!file) {
			read.push_back("No File");
			return read;
		}
		string line;
		while (getline(file, line))
		{
			read.push_back(line);
		}
		file.close();

		return read;
	}

	bool WriteFile(string fileName, enum std::_Iosb<int>::_Openmode ios_base, string data) {
		ofstream file;

		file.open(fileName, ios_base);
		if (!file) return false;
		file << data << endl;
		file.close();
		return true;
	}

	bool WriteFileMulti(string fileName, enum std::_Iosb<int>::_Openmode ios_base, vector<string> data) {
		ofstream file;

		file.open(fileName, ios_base);
		if (!file) return false;
		vector<string>::iterator writer;
		for (writer = data.begin(); writer != data.end(); writer++) file << *writer << endl;
		file.close();
		return true;
	}

	void WriteLine(string fileName, int lineNum, string data) {
		auto read = ReadLine(fileName);
		read.at(lineNum) = data;
		WriteFileMulti(fileName, ios_base::out, read);
	}

	template<class T>
	void SaveClass(string fileName, enum std::_Iosb<int>::_Openmode ios_base, T object) {
		ofstream file_obj;
		file_obj.open(fileName, ios_base | ios_base::binary);
		file_obj.write((char*)&object, sizeof(object));
		file_obj.close();
	}

	template<class T>
	vector<T> ReadClassList(string fileName, T& object) {
		ifstream file_obj;
		vector<T> _object;
		file_obj.open(fileName, ios::in);
		while (!file_obj.eof()) {
			try {
				_object.push_back(object);
				file_obj.read((char*)&object, sizeof(object));
			}
			catch (int a) {}
		}
		file_obj.close();
		return _object;
	}
}

class DateTime {
private:
	string weekDayLong[7] = {
		"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
	};
	string weekDayShort[7] = {
		"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
	};
public:
	int day, month, year, hour, minute, second, weekday;

	DateTime() {
		SYSTEMTIME lt;
		GetLocalTime(&lt);

		day = lt.wDay; month = lt.wMonth; year = lt.wYear; weekday = lt.wDayOfWeek + 1;
		hour = lt.wHour; minute = lt.wMinute; second = lt.wSecond;
	}

	DateTime(int day, int month, int year, int hour, int minute, int second) :
		day(day), month(month), year(year), hour(hour), minute(minute), second(second) {
		SYSTEMTIME lt;
		GetLocalTime(&lt);
		weekday = lt.wDayOfWeek + 1;
	}

	DateTime(int day, int month, int year) : day(day), month(month), year(year) {
		SYSTEMTIME lt;
		GetLocalTime(&lt);

		hour = lt.wHour; minute = lt.wMinute; second = lt.wSecond; weekday = lt.wDayOfWeek + 1;
	}

	/*DateTime(INT16 hour, int minute, int second) : hour(hour), minute(minute), second(second) {
		SYSTEMTIME lt;
		GetLocalTime(&lt);

		day = lt.wDay; month = lt.wMonth; year = lt.wYear; weekday = lt.wDayOfWeek + 1;
	}*/

	void Now() {
		SYSTEMTIME lt;
		GetLocalTime(&lt);

		hour = lt.wHour; minute = lt.wMinute; second = lt.wSecond;
		day = lt.wDay; month = lt.wMonth; year = lt.wYear; weekday = lt.wDayOfWeek + 1;
	}

	string ToString() {
		return to_string(weekday) + " " + to_string(day) + "/" + to_string(month) + "/" +
			to_string(year) + " " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
	}

	string ShortDay() {
		return weekDayShort[this->weekday - 1];
	}

	string LongDay() {
		return weekDayLong[this->weekday - 1];
	}
};

#endif
