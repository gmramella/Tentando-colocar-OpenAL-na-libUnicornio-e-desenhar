#include "Jogo.h"

Jogo::Jogo()
{
}

Jogo::~Jogo()
{
}

void Jogo::inicializar()
{
	uniInicializar(800, 600, false);
	gRecursos.carregarFonte("fonte1", "arial.ttf", 32);
	texto.setFonte("fonte1");
	texto.setCor(255, 255, 255);
	texto.setAlinhamento(TEXTO_CENTRALIZADO);
}

void Jogo::finalizar()
{
	gRecursos.descarregarTudo();
	uniFinalizar();
}

void Jogo::executar(sample* samples, unsigned int numSamples)
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();
		texto.setString(std::to_string(numSamples));
		texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

		/*for (int i = 0; i < 44100; i++)
		{
			Cor cor(255, 255, 255, 255);
			int x1 = i;
			int y1 = gJanela.getAltura() / 2;
			int x2 = i;
			int y2 = gJanela.getAltura() / 2 - (gJanela.getAltura() / 2) * sin(i);
			gGraficos.desenharLinha(x1, y1, x2, y2, cor.r, cor.g, cor.b, cor.a);
		}*/

		uniTerminarFrame();
	}
}

