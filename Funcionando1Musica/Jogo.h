#pragma once
#include "libUnicornio.h"
#include <thread>

class Jogo
{
public:
	Jogo();
	~Jogo();
	void inicializar();
	void finalizar();
	void executar();
	Texto texto;
};