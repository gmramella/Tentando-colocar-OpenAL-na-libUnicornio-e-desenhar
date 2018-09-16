#pragma once
#include <string>

typedef short int sample;

class Utils
{
public:
	static bool isBigEndian();
	static int Utils::convertToInt(char* buffer, int len);
	static std::string Utils::convertToString(char* buffer, int len);
};