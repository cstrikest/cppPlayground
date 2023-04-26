#include"utils.h"

bool isNumeric(std::string& str)
{
	auto it = str.begin();
	while (it != str.end() && std::isdigit(*it))
	{
		it++;
	}
	return !str.empty() && it == str.end();
}

