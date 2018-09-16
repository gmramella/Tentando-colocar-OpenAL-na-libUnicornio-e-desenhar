#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "AL/al.h"
#include "AL/alc.h"

struct Wav {
	char* ChunkID;
	unsigned int ChunkSize;
	char* Format;
	char* Subchunk1ID;
	unsigned int Subchunk1Size;
	unsigned int AudioFormat;
	unsigned int NumChannels;
	unsigned int SampleRate;
	unsigned int ByteRate;
	unsigned int BlockAlign;
	unsigned int BitsPerSample;
	char* Subchunk2ID;
	unsigned int Subchunk2Size;
	unsigned int NumSamples;
	char* CharData;
	short int* IntData;

	Wav(char* ChunkID, unsigned int ChunkSize, char* Format, char* Subchunk1ID, unsigned int Subchunk1Size, unsigned int AudioFormat, unsigned int NumChannels, unsigned int SampleRate, unsigned int ByteRate, unsigned int BlockAlign, unsigned int BitsPerSample, char* Subchunk2ID, unsigned int Subchunk2Size, unsigned int NumSamples, char* CharData)
	{
		this->ChunkID = ChunkID;
		this->ChunkSize = ChunkSize;
		this->Format = Format;
		this->Subchunk1ID = Subchunk1ID;
		this->Subchunk1Size = Subchunk1Size;
		this->AudioFormat = AudioFormat;
		this->NumChannels = NumChannels;
		this->SampleRate = SampleRate;
		this->ByteRate = ByteRate;
		this->BlockAlign = BlockAlign;
		this->BitsPerSample = BitsPerSample;
		this->Subchunk2ID = Subchunk2ID;
		this->Subchunk2Size = Subchunk2Size;
		this->NumSamples = NumSamples;
		this->CharData = CharData;
		this->IntData = parseData();
	}

	void printHeader()
	{
		printf("ChunkID: %s\r\n", ChunkID);
		printf("ChunkSize: %d\r\n", ChunkSize);
		printf("Format: %s\r\n", Format);
		printf("Subchunk1ID: %s\r\n", Subchunk1ID);
		printf("Subchunk1Size: %d\r\n", Subchunk1Size);
		printf("AudioFormat: %d\r\n", AudioFormat);
		printf("NumChannels: %d\r\n", NumChannels);
		printf("SampleRate: %d\r\n", SampleRate);
		printf("ByteRate: %d\r\n", ByteRate);
		printf("BlockAlign: %d\r\n", BlockAlign);
		printf("BitsPerSample: %d\r\n", BitsPerSample);
		printf("Subchunk2ID: %s\r\n", Subchunk2ID);
		printf("Subchunk2Size: %d\r\n", Subchunk2Size);
		printf("NumSamples: %d\r\n", NumSamples);
	}
	void printCharData()
	{
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
			std::cout << CharData[i] << std::endl;
		}
	}
	void printIntData()
	{
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
			std::cout << (short int)CharData[i] << std::endl;
		}
	}
	short int* parseData()
	{
		short int* output = new short int[NumSamples * NumChannels];
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
			output[i] = (short int)CharData[i];
		}
		return output;
	}
	void writeToFile()
	{
		std::ofstream headerFile("header.txt");
		headerFile << "ChunkID: " << ChunkID << std::endl;
		headerFile << "ChunkSize: " << ChunkSize << std::endl;
		headerFile << "Format: " << Format << std::endl;
		headerFile << "Subchunk1ID: " << Subchunk1ID << std::endl;
		headerFile << "Subchunk1Size: " << Subchunk1Size << std::endl;
		headerFile << "AudioFormat: " << AudioFormat << std::endl;
		headerFile << "NumChannels: " << NumChannels << std::endl;
		headerFile << "SampleRate: " << SampleRate << std::endl;
		headerFile << "ByteRate: " << ByteRate << std::endl;
		headerFile << "BlockAlign: " << BlockAlign << std::endl;
		headerFile << "BitsPerSample: " << BitsPerSample << std::endl;
		headerFile << "Subchunk2ID: " << Subchunk2ID << std::endl;
		headerFile << "Subchunk2Size: " << Subchunk2Size << std::endl;
		headerFile << "NumSamples: " << NumSamples << std::endl;
		headerFile.close();

		std::ofstream samplesFile("samples.txt");
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
			samplesFile << (short int)CharData[i] << std::endl;
		}
		samplesFile.close();
	}

	void Clear()
	{
		ChunkID = NULL;
		delete[] ChunkID;
		Format = NULL;
		delete[] Format;
		Subchunk1ID = NULL;
		delete[] Subchunk1ID;
		Subchunk2ID = NULL;
		delete[] Subchunk2ID;
		CharData = NULL;
		delete[] CharData;
		IntData = NULL;
		delete[] IntData;
	}
};

void checkError(ALCenum& error);
bool isBigEndian();
int convertToInt(char* buffer, int len);
std::string convertToString(char* buffer, int len);
Wav* loadWAV(const char* title);

void checkError(ALCenum& error)
{
	error = alGetError();
	if (error != AL_NO_ERROR)
	{
		printf("Something wrong happened");
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

std::string convertToString(char* buffer, int len)
{
	return std::string(buffer, len);
}

Wav* loadWAV(const char* title)
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
	ChunkID = _strdup(convertToString(buffer, 4).c_str());
	if (strncmp(ChunkID, "RIFF", 4) != 0)
	{
		std::cout << "Invalid ChunkID: " << ChunkID << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	ChunkSize = convertToInt(buffer, 4);
	if (ChunkSize <= 8)
	{
		std::cout << "Invalid ChunkSize: " << ChunkSize << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	Format = _strdup(convertToString(buffer, 4).c_str());
	if (strncmp(Format, "WAVE", 4) != 0)
	{
		std::cout << "Invalid Format: " << Format << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	Subchunk1ID = _strdup(convertToString(buffer, 4).c_str());
	if (strncmp(Subchunk1ID, "fmt ", 4) != 0)
	{
		std::cout << "Invalid Subchunk1ID: " << Subchunk1ID << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	Subchunk1Size = convertToInt(buffer, 4);
	if (Subchunk1Size != 16)
	{
		std::cout << "Invalid Subchunk1Size: " << Subchunk1Size << std::endl;
		return NULL;
	}
	in.read(buffer, 2);
	AudioFormat = convertToInt(buffer, 2);
	if (AudioFormat != 1)
	{
		std::cout << "Invalid AudioFormat: " << AudioFormat << std::endl;
		return NULL;
	}
	in.read(buffer, 2);
	NumChannels = convertToInt(buffer, 2);
	if (NumChannels > 2)
	{
		std::cout << "Invalid NumChannels: " << NumChannels << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	SampleRate = convertToInt(buffer, 4);
	if (SampleRate <= 0)
	{
		std::cout << "Invalid SampleRate: " << SampleRate << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	ByteRate = convertToInt(buffer, 4);
	if (ByteRate < SampleRate * NumChannels)
	{
		std::cout << "Invalid ByteRate: " << ByteRate << std::endl;
		return NULL;
	}
	in.read(buffer, 2);
	BlockAlign = convertToInt(buffer, 2);
	if (BlockAlign < NumChannels)
	{
		std::cout << "Invalid BlockAlign: " << BlockAlign << std::endl;
		return NULL;
	}
	in.read(buffer, 2);
	BitsPerSample = convertToInt(buffer, 2);
	if (BitsPerSample / 8 > 2)
	{
		std::cout << "Invalid BitsPerSample: " << BitsPerSample << std::endl;
		return NULL;
	}
	in.read(buffer, 4);
	Subchunk2ID = _strdup(convertToString(buffer, 4).c_str());
	if (strncmp(Subchunk2ID, "data", 4) != 0)
	{
		std::cout << "Invalid Subchunk2ID: " << Subchunk2ID << std::endl;
		return NULL;
	}
	in.read(buffer, 4);//NumSamples * NumChannels * BitsPerSample/8
	Subchunk2Size = convertToInt(buffer, 4);
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

int main(int argc, char** argv)
{
	Wav* wav = loadWAV("../Rock 'N' Roll Train.wav");
	if (wav != NULL)
	{
		wav->printHeader();
		//wav->printCharData();
		//wav->printIntData();
		//wav->writeToFile();
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
			return 0;
		}
		context = alcCreateContext(device, NULL);
		if (context == NULL)
		{
			std::cout << "Cannot open context" << std::endl;
			return 0;
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
	system("pause");
	return 0;
}