#include "strManip.h"

std::string shaveAstrerisks(std::string& str)
{
	while (str[0] == '*')
	{
		str = str.substr(1);
	}
	for (int count = 0; count < str.size(); count++)
	{
		if (str[count] == '*')
			str[count] = '\0';
	}
	return str;
}