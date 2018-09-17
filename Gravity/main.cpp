#include "Jogo.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "fftw3.h"
#include "AudioManager.h"

#define REAL 0
#define IMAG 1

//void run(AudioManager* audioManager, const char* title, unsigned int* numChannels, unsigned int* sampleRate, unsigned int *bitsPerSample, unsigned int* numSamples, sample* samples)
//{
//	audioManager->playWAV(title, numChannels, sampleRate, bitsPerSample, numSamples, samples);
//}

void open(AudioManager* audioManager)
{
	audioManager->open();
}

void play(AudioManager* audioManager, Wav* wav)
{
	audioManager->play(wav);
}

void write(Wav* wav)
{
	/*wav->printCharData();
	wav->printIntData();
	wav->printData();
	wav->writeToFiles();
	wav->writeHeader();
	wav->writeSamples();
	wav->writeConversion();*/
}

int main(int argc, char* argv[])
{
	Jogo jogo;
	jogo.inicializar();

	unsigned int numChannels = 0;
	unsigned int sampleRate = 0;
	unsigned int bitsPerSample = 0;
	unsigned int numSamples = 0;
	sample* samples = NULL;
	double* amplitudes = NULL;
	double highestAmplitude = 0;

	AudioManager audioManager;
	//std::thread(run, &audioManager, "./Musics/Baba O'Riley.wav", &numChannels, &sampleRate, &numSamples, samples).detach();
	//std::thread(run, &audioManager, "./Musics/Won't Get Fooled Again.wav", &numChannels, &sampleRate, &numSamples, samples).detach();
	//std::thread(run, &audioManager, "./Musics/Rock 'N' Roll Train.wav", &numChannels, &sampleRate, &numSamples, samples).detach();
	//std::thread(run, &audioManager, "./Musics/stereo.wav", &numChannels, &sampleRate, &numSamples, samples).detach();
	//std::thread(run, &audioManager, "./Musics/test.wav", &numChannels, &sampleRate, &numSamples, samples).detach();

	//audioManager.playWAV("./Musics/Baba O'Riley.wav", &numChannels, &sampleRate, &numSamples, samples);
	//audioManager.playWAV("./Musics/Won't Get Fooled Again.wav", &numChannels, &sampleRate, &numSamples, samples);
	//audioManager.playWAV("./Musics/Rock 'N' Roll Train.wav", &numChannels, &sampleRate, &bitsPerSample, &numSamples, samples);
	//audioManager.playWAV("./Musics/stereo.wav", &numChannels, &sampleRate, &numSamples, samples);
	//audioManager.playWAV("./Musics/test.wav", &numChannels, &sampleRate, &numSamples, samples);

	audioManager.open();
	Wav* wav = audioManager.loadWAV("./Musics/Rock 'N' Roll Train.wav");
	if (wav != NULL)
	{
		numChannels = wav->NumChannels;
		sampleRate = wav->SampleRate;
		bitsPerSample = wav->BitsPerSample;
		numSamples = wav->NumSamples;
		samples = wav->IntData;
		amplitudes = wav->Amplitudes;
		highestAmplitude = wav->HighestAmplitude;

		std::thread(play, &audioManager, wav).detach();
		std::thread(write, wav).detach();
	}

	jogo.executar(numChannels, sampleRate, bitsPerSample, numSamples, samples, amplitudes, highestAmplitude);
	jogo.finalizar();

	wav->Clear();
	delete[] wav;
	wav = NULL;
	audioManager.close();

	numChannels = NULL;
	sampleRate = NULL;
	numSamples = NULL;
	highestAmplitude = 0;

	return 0;
}