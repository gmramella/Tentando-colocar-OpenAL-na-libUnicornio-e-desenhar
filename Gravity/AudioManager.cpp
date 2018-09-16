#include "AudioManager.h"

int counter = 0;
int errorCounter = 0;

void AudioManager::checkError(ALCenum& error)
{
	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		printf("Something wrong happened");
	}
}

Wav* AudioManager::loadWAV(const char* title)
{
	const char* ChunkID;
	int ChunkSize;
	const char* Format;
	const char* Subchunk1ID;
	int Subchunk1Size;
	int AudioFormat;
	int NumChannels;
	int SampleRate;
	int ByteRate;
	int BlockAlign;
	int BitsPerSample;
	const char* Subchunk2ID;
	int Subchunk2Size;
	int NumSamples;
	char* charData;

	std::cout << "Title: " << title << std::endl;
	char buffer[4];
	std::ifstream in(title, std::ios::binary);
	if (!in.is_open())
	{
		std::cout << "Title not found: " << title << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	ChunkID = _strdup(Utils::convertToString(buffer, 4).c_str());
	if (strncmp(ChunkID, "RIFF", 4) != 0)
	{
		std::cout << "Invalid ChunkID: " << ChunkID << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	ChunkSize = Utils::convertToInt(buffer, 4);
	if (ChunkSize <= 8)
	{
		std::cout << "Invalid ChunkSize: " << ChunkSize << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	Format = _strdup(Utils::convertToString(buffer, 4).c_str());
	if (strncmp(Format, "WAVE", 4) != 0)
	{
		std::cout << "Invalid Format: " << Format << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	Subchunk1ID = _strdup(Utils::convertToString(buffer, 4).c_str());
	if (strncmp(Subchunk1ID, "fmt ", 4) != 0)
	{
		std::cout << "Invalid Subchunk1ID: " << Subchunk1ID << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	Subchunk1Size = Utils::convertToInt(buffer, 4);
	if (Subchunk1Size != 16)
	{
		std::cout << "Invalid Subchunk1Size: " << Subchunk1Size << std::endl;
		return NULL;
	}
	in.read(buffer, 2);
	AudioFormat = Utils::convertToInt(buffer, 2);
	if (AudioFormat != 1)
	{
		std::cout << "Invalid AudioFormat: " << AudioFormat << std::endl;
		return NULL;
	}
	in.read(buffer, 2);
	NumChannels = Utils::convertToInt(buffer, 2);
	if (NumChannels > 2)
	{
		std::cout << "Invalid NumChannels: " << NumChannels << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	SampleRate = Utils::convertToInt(buffer, 4);
	if (SampleRate <= 0)
	{
		std::cout << "Invalid SampleRate: " << SampleRate << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	ByteRate = Utils::convertToInt(buffer, 4);
	if (ByteRate < SampleRate * NumChannels)
	{
		std::cout << "Invalid ByteRate: " << ByteRate << std::endl;
		return NULL;
	}
	in.read(buffer, 2);
	BlockAlign = Utils::convertToInt(buffer, 2);
	if (BlockAlign < NumChannels)
	{
		std::cout << "Invalid BlockAlign: " << BlockAlign << std::endl;
		return NULL;
	}
	in.read(buffer, 2);
	BitsPerSample = Utils::convertToInt(buffer, 2);
	if (BitsPerSample / 8 > 2)
	{
		std::cout << "Invalid BitsPerSample: " << BitsPerSample << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	Subchunk2ID = _strdup(Utils::convertToString(buffer, 4).c_str());
	if (strncmp(Subchunk2ID, "data", 4) != 0)
	{
		std::cout << "Invalid Subchunk2ID: " << Subchunk2ID << std::endl;
		return NULL;
	}
	in.read(buffer, 4);//NumSamples * NumChannels * BitsPerSample/8
	Subchunk2Size = Utils::convertToInt(buffer, 4);
	if (Subchunk2Size < NumChannels * BitsPerSample / 8)
	{
		std::cout << "Invalid Subchunk2Size: " << Subchunk2Size << std::endl;
		return NULL;
	}
	NumSamples = 8 * Subchunk2Size / NumChannels / BitsPerSample;
	charData = new char[Subchunk2Size];
	in.read(charData, Subchunk2Size);

	return new Wav(_strdup(ChunkID), ChunkSize, _strdup(Format), _strdup(Subchunk1ID), Subchunk1Size, AudioFormat, NumChannels, SampleRate, ByteRate, BlockAlign, BitsPerSample, _strdup(Subchunk2ID), Subchunk2Size, NumSamples, charData);
}

void AudioManager::playWav(const char* title, sample* samples, unsigned int& numSamples)
{
	Wav* wav = loadWAV(title);
	if (wav != NULL)
	{
		//wav->printHeader();
		//wav->printCharData();
		//wav->printIntData();
		//wav->writeToFiles(title);

		if (samples != NULL)
		{
			numSamples = NULL;
			delete[] samples;
			samples = NULL;
		}
		samples = new sample[wav->NumSamples];
		memcpy(samples, wav->IntData, wav->NumSamples * sizeof(sample));

		ALCenum error;
		ALCdevice* device = NULL;
		ALCcontext* context = NULL;
		unsigned int bufferid, format;
		unsigned int sourceid;
		ALint source_state;

		device = alcOpenDevice(NULL);
		if (device == NULL)
		{
			std::cout << "Cannot open sound card" << std::endl;
			return;
		}
		context = alcCreateContext(device, NULL);
		if (context == NULL)
		{
			std::cout << "Cannot open context" << std::endl;
			return;
		}
		alcMakeContextCurrent(context);
		checkError(error);

		alGenBuffers(1, &bufferid);
		checkError(error);
		format = ((wav->NumChannels + wav->BitsPerSample) == 9) * AL_FORMAT_MONO8 + ((wav->NumChannels + wav->BitsPerSample) == 10) * AL_FORMAT_STEREO8 + ((wav->NumChannels + wav->BitsPerSample) == 17) * AL_FORMAT_MONO16 + ((wav->NumChannels + wav->BitsPerSample) == 18) * AL_FORMAT_STEREO16;
		alBufferData(bufferid, format, wav->CharData, wav->Subchunk2Size, wav->SampleRate);
		checkError(error);
		alGenSources(1, &sourceid);
		checkError(error);
		alSourcei(sourceid, AL_BUFFER, bufferid);
		checkError(error);
		alSourcePlay(sourceid);
		checkError(error);

		alGetSourcei(sourceid, AL_SOURCE_STATE, &source_state);
		checkError(error);
		while (source_state == AL_PLAYING) {
			alGetSourcei(sourceid, AL_SOURCE_STATE, &source_state);
			checkError(error);
		}

		alDeleteSources(1, &sourceid);
		alDeleteBuffers(1, &bufferid);
		alcDestroyContext(context);
		alcCloseDevice(device);

		wav->Clear();
		wav = NULL;
		delete[] wav;
		error = NULL;
		device = NULL;
		context = NULL;
		bufferid = NULL;
		format = NULL;
		sourceid = NULL;
		source_state = NULL;
	}
}