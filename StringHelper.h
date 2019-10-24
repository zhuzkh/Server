#pragma once
#include <stdint.h>
#include <string>
#include <vector>
using namespace std;

class StringHelper
{
public:
	static vector<string> Split(const string& s, const string& delimiters = " ");

};
