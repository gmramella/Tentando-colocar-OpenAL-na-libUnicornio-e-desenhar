#include "Jogo.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "AudioManager.h"

void run(AudioManager* audioWav, const char* title, sample* samples, unsigned int numSamples)
{
	audioWav->playWav(title, samples, numSamples);
}

int main(int argc, char* argv[])
{
	unsigned int numSamples;
	sample* samples = NULL;

	AudioManager audioWav;
	//std::thread(run, &audioWav, "./Musics/Baba O'Riley.wav").detach();
	//std::thread(run, &audioWav, "./Musics/Won't Get Fooled Again.wav").detach();
	//std::thread(run, &audioWav, "./Musics/Rock 'N' Roll Train.wav").detach();
	//std::thread(run, &audioWav, "./Musics/stereo.wav").detach();
	std::thread(run, &audioWav, "./Musics/test.wav", samples, numSamples).detach();
	
	Jogo jogo;
	jogo.inicializar();
	jogo.executar(samples, numSamples);
	jogo.finalizar();

	delete[] samples;
	samples = NULL;

	return 0;
}