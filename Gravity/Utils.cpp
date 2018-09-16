#include "Utils.h"

bool Utils::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int Utils::Utils::convertToInt(char* buffer, int len)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i<len; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i<len; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

std::string Utils::Utils::convertToString(char* buffer, int len)
{
	return std::string(buffer, len);
}