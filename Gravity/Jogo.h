#pragma once
#include "libUnicornio.h"
#include "AudioManager.h"
#include <thread>

class Jogo
{
public:
	Jogo();
	~Jogo();
	void inicializar();
	void finalizar();
	void executar(sample* samples, unsigned int numSamples);
	Texto texto;
};