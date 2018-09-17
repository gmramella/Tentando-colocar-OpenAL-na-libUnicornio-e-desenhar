#include "Utils.h"

bool Utils::isBigEndian()
{
	int a = 1;
	return !((char*)&a)[0];
}

int Utils::Utils::convertToInt(char* buffer, int len)
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

std::string Utils::Utils::convertToString(char* buffer, int len)
{
	return std::string(buffer, len);
}

double* Utils::fft(unsigned int numSamples, sample* samples)
{
	//https://www.youtube.com/watch?v=CMyG4hsKCJo
	//https://www.youtube.com/watch?v=mkGsMWi_j4Q&index=11&list=PLT5_DQAJJLh-ogHjHcLtFYMQy7SkZ7-3i
	fftw_complex* x = new fftw_complex[numSamples];
	fftw_complex* y = new fftw_complex[numSamples];
	fftw_complex* z = new fftw_complex[numSamples / 2];
	double* amplitudes = new double[numSamples / 2];
	double* phases = new double[numSamples / 2];
	//double frequencyStep = samplingFrequency / nSamples;

	for (unsigned int i = 0; i < numSamples; i++)
	{
		x[i][REAL] = samples[i];//sin(i * 2 * PI / numSamples);
		x[i][IMAG] = 0;
	}
	fftw_plan plan = fftw_plan_dft_1d(numSamples, x, y, FFTW_FORWARD, FFTW_ESTIMATE);//FFTW_FORWARD = -1, FFTW_ESTIMATE = (1U << 6)
	fftw_execute(plan);
	fftw_destroy_plan(plan);
	fftw_cleanup();

	for (unsigned int i = 0; i < numSamples / 2; i++)
	{
		//k(a + bi) = (ka + kbi)
		z[i][REAL] = 2 * y[i][REAL];
		z[i][IMAG] = 2 * y[i][IMAG];
	}

	for (unsigned int i = 0; i < numSamples / 2; i++)
	{
		//amplitude = r
		//phase = theta
		amplitudes[i] = sqrt(z[i][REAL] * z[i][REAL] + z[i][IMAG] * z[i][IMAG]) / numSamples;
		phases[i] = atan2(z[i][IMAG], z[i][REAL]);
	}

	/*std::ofstream myfile("./Files/fft.txt");
	for (unsigned int i = 0; i < numSamples; i++)
	{
		if (x[i][IMAG] < 0)
			myfile << x[i][REAL] << " - " << abs(x[i][IMAG]) << "i" << std::endl;
		else
			myfile << x[i][REAL] << " + " << abs(x[i][IMAG]) << "i" << std::endl;
	}
	myfile << std::endl;
	for (unsigned int i = 0; i < numSamples; i++)
	{
		if (y[i][IMAG] < 0)
			myfile << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i" << std::endl;
		else
			myfile << y[i][REAL] << " + " << abs(y[i][IMAG]) << "i" << std::endl;
	}
	myfile << std::endl;
	for (unsigned int i = 0; i < numSamples / 2; i++)
	{
		if (z[i][IMAG] < 0)
			myfile << z[i][REAL] << " - " << abs(z[i][IMAG]) << "i" << std::endl;
		else
			myfile << z[i][REAL] << " + " << abs(z[i][IMAG]) << "i" << std::endl;
	}
	myfile << std::endl;
	for (unsigned int i = 0; i < numSamples / 2; i++)
	{
		myfile << "frequency " << i << " amplitude " << amplitudes[i] << " phase " << phases[i] << " rad = " << (180 * phases[i] / PI) << " deg" << std::endl;
	}
	myfile.close();*/

	return amplitudes;
}