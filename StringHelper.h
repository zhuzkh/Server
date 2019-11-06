#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class StringHelper
{
public:
	static vector<string> Split(const string& s, const string& delimiters = " ");

	//c++17
	//static vector<string_view> SplitStringView(const string& s, const string& delimiters = " ");

};
