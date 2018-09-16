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
	gRecursos.descarregarFonte("fonte1");
	uniFinalizar();
}

void Jogo::executar()
{
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();
		texto.setString("A libUnicórnio é D+\nEla tem textos coloridos e com quebra de linha!");
		texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);
		uniTerminarFrame();
	}
}

