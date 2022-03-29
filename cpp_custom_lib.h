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

/// <summary>
/// Chứa các hàm cơ bản thường dùng nhất
/// </summary>
namespace Custom {
	/// <summary>
	/// Kiểm tra kiểu dữ liệu của biến, class, struct,...
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value: kiểu dữ liệu bất kỳ"></param>
	/// <returns>string</returns>
	template<typename T>
	string GetType(T value) {
		return typeid(value).name();
	}

	/// <summary>
	/// Tìm giá trị nhỏ nhất của mảng
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a[]: kiểu dữ liệu bất kỳ"></param>
	/// <returns>class T</returns>
	template<typename T>
	T Min(T a[]) {
		T min = a[0];
		for (int i = 0; i < (sizeof(a) / sizeof(T)) - 1; i++)
			if (a[i + 1] < a[i]) min = a[i + 1];
		return min;
	}

	/// <summary>
	/// Tìm giá trị lớn nhất của mảng
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="a[]: kiểu dữ liệu bất kỳ"></param>
	/// <returns>class T</returns>
	template<typename T>
	T Max(T a[]) {
		T max = a[0];
		for (int i = 0; i < (sizeof(a) / sizeof(T)) - 1; i++)
			if (a[i + 1] > a[i]) max = a[i + 1];
		return max;
	}

	/// <summary>
	/// Thực thi lệnh trong CMD và lấy văn bản xuất ra từ nó
	/// </summary>
	/// <param name="cmd: lệnh cần chạy trong CMD"></param>
	/// <returns>string</returns>
	string GetCmdOutput(const char* cmd) {
		shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
		if (!pipe) return "ERROR";
		char buffer[128];
		string result = "";
		while (!feof(pipe.get())) {
			if (fgets(buffer, 128, pipe.get()) != NULL)
				result += buffer;
		}
		return result;
	}
}

/// <summary>
/// Chứa các hàm xử lý về chuỗi
/// </summary>
namespace String {
	/// <summary>
	/// Chuyển đổi một số thuộc kiểu dữ liệu bất kỳ sang chuỗi
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="value: kiểu dữ liệu bất kỳ"></param>
	/// <returns>string</returns>
	template<typename T>
	string Parse(T value) {
		return to_string(value);
	}

	/// <summary>
	/// Chuyển đổi mảng con trỏ ký tự sang chuỗi
	/// </summary>
	/// <param name="value"></param>
	/// <returns>string</returns>
	string Parse(const char* value) {
		string str(value);
		return str;
	}

	/// <summary>
	/// Chuyển đổi mảng ký tự sang chuỗi
	/// </summary>
	/// <param name="value"></param>
	/// <returns>string</returns>
	string Parse(char value[]) {
		string str(value);
		return str;
	}

	/// <summary>
	/// Tách chuỗi lớn thành các chuỗi con
	/// </summary>
	/// <param name="str: chuỗi cần tách"></param>
	/// <param name="separator: dấu phân cách"></param>
	/// <returns>vector&lt;string&gt;</returns>
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

	/// <summary>
	/// Tách chuỗi lớn thành các chuỗi con (tối ưu hơn)
	/// </summary>
	/// <param name="str: chuỗi cần tách"></param>
	/// <param name="separator: dấu phân cách"></param>
	/// <returns>vector&lt;string&gt;</returns>
	vector<string> Split(string str, char separator)
	{
		vector<string> sout;
		istringstream ss(str);
		string token;
		while (std::getline(ss, token, separator)) {
			sout.push_back(token);
		}
		return sout;
	}

	/// <summary>
	/// Sắp xếp các chuỗi theo thứ tự a-z
	/// </summary>
	/// <param name="strVec"></param>
	/// <returns>vector&lt;string&gt;</returns>
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

	/// <summary>
	/// Chèn thêm chuỗi vào vị trí bất kỳ
	/// </summary>
	/// <param name="str: chuỗi đầu vào"></param>
	/// <param name="insert_str: chuỗi cần chèn"></param>
	/// <param name="start: vị trí chèn"></param>
	void Insert(string& str, string insert_str, int start) {
		unsigned int len_str = str.length() + insert_str.length();
		while (str.length() < len_str) str.insert(start, insert_str);
	}

	bool replaceCall(string& str, const string& from, const string& to) {
		size_t start_pos = str.find(from);
		if (start_pos == std::string::npos) return false;
		str.replace(start_pos, from.length(), to);
		return true;
	}

	/// <summary>
	/// Thay thế chuỗi tại vị trí bất kỳ
	/// </summary>
	/// <param name="str: chuỗi đầu vào"></param>
	/// <param name="from: chuỗi cần thay thế"></param>
	/// <param name="to: chuỗi thay thế"></param>
	void Replace(string& str, const string& from, const string& to) {
		while (replaceCall(str, from, to));
	}
}

/// <summary>
/// Chứa các hàm xử lý về double
/// </summary>
namespace Double {
	/// <summary>
	/// Chuyển đổi chuỗi thành double \
	/// </summary>
	/// <param name="value"></param>
	/// <returns>double</returns>
	double Parse(string value) {
		return stod(value);
	}

	/// <summary>
	/// Kiểm tra tính hợp lệ khi chuyển đổi chuỗi thành double
	/// </summary>
	/// <param name="value: chuỗi đầu vào"></param>
	/// <param name="out: double đầu ra"></param>
	/// <returns>true: nếu chuỗi đầu vào hợp lệ</returns>
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

/// <summary>
/// Chứa các hàm xử lý về số nguyên
/// </summary>
namespace Int {
	/// <summary>
	/// Chuyển đổi chuỗi thành số nguyên
	/// </summary>
	/// <param name="value"></param>
	/// <returns>int</returns>
	int Parse(string value) {
		return stoi(value);
	}

	/// <summary>
	/// Kiểm tra tính hợp lệ khi chuyển đổi chuỗi thành số nguyên
	/// </summary>
	/// <param name="value: chuỗi đầu vào"></param>
	/// <param name="out: int đầu ra"></param>
	/// <returns>true: nếu chuỗi đầu vào hợp lệ</returns>
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

/// <summary>
/// Chứa các hàm xử lý về số nguyên dài
/// </summary>
namespace LongLong {
	/// <summary>
	/// Chuyển đổi chuỗi thành longlong
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	long long Parse(string value) {
		return stoll(value);
	}

	/// <summary>
	/// Kiểm tra tính hợp lệ khi chuyển đổi chuỗi thành longlong
	/// </summary>
	/// <param name="value: chuỗi đầu vào"></param>
	/// <param name="out: longlong đầu ra"></param>
	/// <returns>true: nếu chuỗi đầu vào hợp lệ</returns>
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

/// <summary>
/// Chứa các hàm xử lý về tệp
/// </summary>
namespace File {
	/// <summary>
	/// Đọc chuỗi từng hàng trong tệp
	/// </summary>
	/// <param name="fileName"></param>
	/// <returns>vector&lt;string&gt;</returns>
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

	/// <summary>
	/// Ghi dữ liệu ra tệp
	/// </summary>
	/// <param name="fileName: tên tệp"></param>
	/// <param name="ios_base: chế độ ghi"></param>
	/// <param name="data: dữ liệu chuỗi"></param>
	/// <returns>true: nếu ghi thành công</returns>
	bool WriteFile(string fileName, enum std::_Iosb<int>::_Openmode ios_base, string data) {
		ofstream file;

		file.open(fileName, ios_base);
		if (!file) return false;
		file << data << endl;
		file.close();
		return true;
	}

	/// <summary>
	/// Ghi dữ liệu nhiều hàng ra tệp
	/// </summary>
	/// <param name="fileName: tên tệp"></param>
	/// <param name="ios_base: chế độ ghi"></param>
	/// <param name="data: vector chuỗi"></param>
	/// <returns>true: nếu ghi thành công</returns>
	bool WriteFileMulti(string fileName, enum std::_Iosb<int>::_Openmode ios_base, vector<string> data) {
		ofstream file;
		file.open(fileName, ios_base);
		if (!file) return false;
		vector<string>::iterator writer;
		for (writer = data.begin(); writer != data.end(); writer++) file << *writer << endl;
		file.close();
		return true;
	}

	/// <summary>
	/// Ghi ra tệp dữ liệu tại hàng bất kỳ
	/// </summary>
	/// <param name="fileName: tên tệp"></param>
	/// <param name="lineNum: hàng cần ghi"></param>
	/// <param name="data: dữ liệu chuỗi"></param>
	void WriteLine(string fileName, int lineNum, string data) {
		auto read = ReadLine(fileName);
		read.at(lineNum) = data;
		WriteFileMulti(fileName, ios_base::out, read);
	}
}

/// <summary>
/// Class lưu và xử lý về thời gian
/// </summary>
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

	/// <summary>
	/// Lấy thời gian hiện tại
	/// </summary>
	void Now() {
		SYSTEMTIME lt;
		GetLocalTime(&lt);

		hour = lt.wHour; minute = lt.wMinute; second = lt.wSecond;
		day = lt.wDay; month = lt.wMonth; year = lt.wYear; weekday = lt.wDayOfWeek + 1;
	}

	/// <summary>
	/// Chuyển thời gian thành chuỗi dễ đọc
	/// </summary>
	/// <returns></returns>
	string ToString() {
		return to_string(weekday) + " " + to_string(day) + "/" + to_string(month) + "/" +
			to_string(year) + " " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
	}

	/// <summary>
	/// Hiển thị thứ trong tuần dạng chuỗi ngắn
	/// </summary>
	/// <returns>string</returns>
	string ShortDay() {
		return weekDayShort[this->weekday - 1];
	}

	/// <summary>
	/// Hiển thị thứ trong tuần dạng chuỗi dài
	/// </summary>
	/// <returns>string</returns>
	string LongDay() {
		return weekDayLong[this->weekday - 1];
	}
};

#endif
