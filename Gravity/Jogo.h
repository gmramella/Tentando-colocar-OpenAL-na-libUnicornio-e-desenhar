#pragma once
#include "libUnicornio.h"
#include "AudioManager.h"
#include <thread>
#include <chrono>

//https://stackoverflow.com/questions/31487876/getting-a-time-difference-in-milliseconds
class Timer
{
public:
	void start()
	{
		initial = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
	}

	long long update()
	{
		return (std::chrono::system_clock::now() - initial).count();
	}
private:
	std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> initial;
};

class Jogo
{
public:
	Jogo() { timer.start(); }
	void inicializar();
	void finalizar();
	void executar(unsigned int numChannels, unsigned int sampleRate, unsigned int bitsPerSample, unsigned int numSamples, sample* samples, double* amplitudes, double highestAmplitude);
	Texto texto;
	long long init;
	Timer timer;
};