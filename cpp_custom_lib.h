//Header library for C++, syntax is similar to C# for easy manipulation

#ifndef cpp_custom_lib_h
#define cpp_custom_lib_h
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
}

namespace Double {
	double Parse(string value) {
		return stod(value);
	}
}

namespace Int {
	int Parse(string value) {
		return stoi(value);
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

	bool WriteFileMulti(string fileName, enum std::_Iosb<int>::_Openmode ios_base,
		vector<string> data) {
		ofstream file;

		file.open(fileName, ios_base);
		if (!file) return false;
		vector<string>::iterator writer;
		for (writer = data.begin(); writer != data.end(); writer++) file << *writer << endl;
		file.close();
		return true;
	}
}

#endif
