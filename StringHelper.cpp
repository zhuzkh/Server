#include "StringHelper.h"

std::vector<std::string> StringHelper::Split(const string& s, const string& delimiters /*= " "*/)
{
	vector<string> tokens;
	string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		tokens.push_back(s.substr(lastPos, pos - lastPos));
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
	return tokens;
}

// c++17
// std::vector<string_view> StringHelper::SplitStringView(const string& s, const string& delimiters /*= " "*/)
// {
// 	vector<string_view> tokens;
// 	string_view view(s);
// 	string::size_type lastPos = view.find_first_not_of(delimiters, 0);
// 	string::size_type pos = view.find_first_of(delimiters, lastPos);
// 	while (string::npos != pos || string::npos != lastPos)
// 	{
// 		tokens.push_back(view.substr(lastPos, pos - lastPos));
// 		lastPos = view.find_first_not_of(delimiters, pos);
// 		pos = view.find_first_of(delimiters, lastPos);
// 	}
// 	return tokens;
// }
