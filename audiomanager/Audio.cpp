#include "Audio.h"
#include <iostream>

void Audio::applyFadeOut(double seconds)
{
	double seconds2 = seconds;
	seconds2 = seconds2 + 3.0;
}

std::uint32_t Audio::getSampleRate()
{
	return sampleRate;
}

void Audio::printInformation()
{
	std::cout << "SampleRate: " << sampleRate << '\n';
	std::cout << "Channels: " << numChannels << '\n';
	std::cout << "BitsPerSample: " << bitsPerSample << '\n';
}
