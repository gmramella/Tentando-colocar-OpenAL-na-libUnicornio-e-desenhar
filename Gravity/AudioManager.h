#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Utils.h"
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
	void writeToFiles(const char* title)
	{
		std::ofstream headerFile("./Files/header.txt");
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

		std::ofstream samplesFile("./Files/samples.txt");
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

class AudioManager
{
public:
	void playWav(const char* title, sample* samples, unsigned int& numSamples);
	Wav* loadWAV(const char* title);
private:
	void checkError(ALCenum& error);
};