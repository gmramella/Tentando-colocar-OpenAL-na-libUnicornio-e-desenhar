#pragma once
#include <fstream>
#include <string>
#include "libUnicornio.h"
#include "fftw3.h"

#define REAL 0
#define IMAG 1

typedef short int sample;

class Utils
{
public:
	static bool isBigEndian();
	static int Utils::convertToInt(char* buffer, int len);
	static std::string convertToString(char* buffer, int len);
	static double* fft(unsigned int numSamples, sample* samples);
};