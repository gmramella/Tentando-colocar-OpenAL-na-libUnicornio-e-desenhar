#include "Jogo.h"
#include "AL/al.h"
#include "AL/alc.h"

bool die = false;

bool isBigEndian();
int convertToInt(char* buffer, int len);
char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size);
void playSound(const char* title);

int counter = 0;
int errorCounter = 0;

int main(int argc, char* argv[])
{
	std::thread playSoundThread1(playSound, "../Baba O'Riley.wav");
	playSoundThread1.detach();
	
	Jogo jogo;
	jogo.inicializar();
	jogo.executar();
	jogo.finalizar();
	die = true;
	return 0;
}

void checkError(ALCenum& error)
{
	errorCounter++;
	error = alGetError();
	if (error != AL_NO_ERROR)
	{
	}
}

bool isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int convertToInt(char* buffer, int len)
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i<len; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i<len; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size)
{
	char buffer[4];
	std::ifstream in(fn, std::ios::binary);
	in.read(buffer, 4);
	if (strncmp(buffer, "RIFF", 4) != 0)
	{
		return NULL;
	}
	in.read(buffer, 4);
	in.read(buffer, 4);      //WAVE
	in.read(buffer, 4);      //fmt
	in.read(buffer, 4);      //16
	in.read(buffer, 2);      //1
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);      //data
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);
	char* data = new char[size];
	in.read(data, size);
	return data;
}

void playSound(const char* title)
{
	int channel, sampleRate, bps, size;
	char* data = loadWAV(title, channel, sampleRate, bps, size);
	ALCenum error;
	ALCdevice* device = alcOpenDevice(NULL);
	if (device == NULL)
	{
	}
	else
	{
		ALCcontext* context = alcCreateContext(device, NULL);
		if (context == NULL)
		{
		}
		else
		{
			alcMakeContextCurrent(context);
			checkError(error);

			unsigned int bufferid, format;
			alGenBuffers(++counter, &bufferid);
			checkError(error);
			if (channel == 1)
			{
				if (bps == 8)
				{
					format = AL_FORMAT_MONO8;
				}
				else {
					format = AL_FORMAT_MONO16;
				}
			}
			else {
				if (bps == 8)
				{
					format = AL_FORMAT_STEREO8;
				}
				else {
					format = AL_FORMAT_STEREO16;
				}
			}
			alBufferData(bufferid, format, data, size, sampleRate);
			checkError(error);
			unsigned int sourceid;
			alGenSources(1, &sourceid);
			checkError(error);
			alSourcei(sourceid, AL_BUFFER, bufferid);
			checkError(error);
			alSourcePlay(sourceid);
			checkError(error);

			ALint source_state;
			alGetSourcei(sourceid, AL_SOURCE_STATE, &source_state);
			checkError(error);
			
			while (source_state == AL_PLAYING && !die) {
				alGetSourcei(sourceid, AL_SOURCE_STATE, &source_state);
				checkError(error);
			}

			alDeleteSources(1, &sourceid);
			alDeleteBuffers(1, &bufferid);
			alcMakeContextCurrent(NULL);
			alcDestroyContext(context);
			alcCloseDevice(device);
			delete[] data;
		}
	}
}