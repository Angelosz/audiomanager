#include "Audio.h"
#include <iostream>

void Audio::applyFadeOut(double seconds)
{
	double seconds2 = seconds;
	seconds2 = seconds2 + 3.0;
}

std::uint32_t Audio::getSampleRate() const
{
	return sampleRate;
}

std::uint32_t Audio::getByteRate() const
{
	return sampleRate * getBlockAlign();
}

std::uint16_t Audio::getBlockAlign() const
{
	return static_cast<std::uint16_t>((bitsPerSample / 8) * numChannels);
}

std::uint16_t Audio::getNumChannels() const
{
	return numChannels;
}

std::uint16_t Audio::getBitsPerSample() const
{
	return bitsPerSample;
}

std::vector<std::int16_t> Audio::getSamples() const
{
	return samples;
}

std::uint32_t Audio::getDataSize() const
{
	return static_cast<std::uint32_t>(samples.size() * sizeof(std::int16_t));
}
