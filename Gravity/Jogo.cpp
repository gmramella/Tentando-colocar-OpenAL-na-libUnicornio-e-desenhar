#include "Jogo.h"

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

void Jogo::executar(unsigned int numChannels, unsigned int sampleRate, unsigned int bitsPerSample, unsigned int numSamples, sample* samples, double* amplitudes, double highestAmplitude)
{
	float max = (float)pow(2, 8) - 1;
	while(!gTeclado.soltou[TECLA_ESC] && !gEventos.sair)
	{
		uniIniciarFrame();
		long long seconds = timer.update() / 1e9;
		if (samples == NULL)
			texto.setString("No samples");
		else
			texto.setString(std::to_string(numChannels) + " channels\n" + std::to_string(sampleRate) + " samples/s\n" + std::to_string(numSamples) + " total samples");
		texto.setCor(Cor(255, 0, 0, 255));
		texto.setString(std::to_string(seconds));
		texto.desenhar(gJanela.getLargura() / 2, gJanela.getAltura() / 2);

		int frameFirst = (int)round(sampleRate * seconds);
		if (frameFirst <= numSamples)
		{
			for (unsigned int j = 0; j < numChannels; j++)
			{
				for (unsigned int i = 0; i < sampleRate; i++)
				{
					Cor cor(255, 255, 255, 255);
					int x1 = i;
					int x2 = x1;
					int y1 = gJanela.getAltura() / 8 + j * (gJanela.getAltura() / 4);
					int y2 = y1 - (frameFirst > numSamples * numChannels ? 0 : (gJanela.getAltura() / 4) * samples[frameFirst + numChannels * i + j] / max);
					gGraficos.desenharLinha(x1, y1, x2, y2, cor.r, cor.g, cor.b, cor.a);

					int x3 = i;
					int x4 = x3;
					int y3 = 5 * gJanela.getAltura() / 8 + j * (gJanela.getAltura() / 4);
					int y4 = y3 - (gJanela.getAltura() / 4) * amplitudes[frameFirst + numChannels * i + j] / highestAmplitude;
					gGraficos.desenharLinha(x3, y3, x4, y4, cor.r, cor.g, cor.b, cor.a);
				}
			}
		}

		uniTerminarFrame();
	}
}

