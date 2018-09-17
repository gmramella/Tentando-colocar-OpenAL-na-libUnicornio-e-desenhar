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
	double* Amplitudes;
	double HighestAmplitude;

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
		this->Amplitudes = Utils::fft(NumSamples, IntData);
		this->HighestAmplitude = Amplitudes[0];
		for (unsigned int i = 1; i < NumSamples / 2; i++) {
			if (this->HighestAmplitude < Amplitudes[i]) {
				this->HighestAmplitude = Amplitudes[i];
			}
		}
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
			std::cout << IntData[i] << std::endl;
		}
	}
	void printData()
	{
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
			std::cout << CharData[i] << " " << IntData[i] << std::endl;
		}
	}
	void writeToFiles()
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
			samplesFile << IntData[i] << std::endl;
		}
		samplesFile.close();
	}
	void writeHeader()
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
	}
	void writeSamples()
	{
		std::ofstream samplesFile("./Files/samples.txt");
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
			samplesFile << IntData[i] << std::endl;
		}
		samplesFile.close();
	}
	void writeConversion()
	{
		std::ofstream samplesFile("./Files/conversion.txt");
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
			samplesFile << CharData[i] << " " << IntData[i] << std::endl;
		}
		samplesFile.close();
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
	sample* parseData()
	{
		/*sample* output = new sample[NumSamples * NumChannels];
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
		output[i] = convertToInt(&(CharData[i]), BitsPerSample / 8);
		}
		return output;*/

		sample* output = new sample[NumSamples * NumChannels];
		for (int i = 0; i< NumSamples * NumChannels; i++)
		{
			output[i] = (sample)CharData[i];
		}
		return output;
	}

	void Clear()
	{
		delete[] ChunkID;
		ChunkID = NULL;
		delete[] Format;
		Format = NULL;
		delete[] Subchunk1ID;
		Subchunk1ID = NULL;
		delete[] Subchunk2ID;
		Subchunk2ID = NULL;
		delete[] CharData;
		CharData = NULL;
		delete[] IntData;
		IntData = NULL;
		delete[] Amplitudes;
		Amplitudes = NULL;
		HighestAmplitude = NULL;
	}
};

class AudioManager
{
public:
	void open();
	void close();
	void play(Wav* wav);
	void replay();
	Wav* loadWAV(const char* title);
private:
	void checkError(ALCenum& error);

	ALCenum error;
	ALCdevice* device = NULL;
	ALCcontext* context = NULL;
	unsigned int bufferid, format;
	unsigned int sourceid;
	ALint source_state;
};