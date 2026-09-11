#pragma once

#include <vector>
class Audio 
{
	const std::uint32_t sampleRate;
	const std::uint16_t numChannels;
	const std::uint16_t bitsPerSample;

	std::vector<std::int16_t> samples;

public:
	Audio(const std::uint32_t sampleRate, const std::uint16_t numChannels, const std::uint16_t bitsPerSample, const std::vector<std::int16_t>& samples)
		: sampleRate(sampleRate), numChannels(numChannels), bitsPerSample(bitsPerSample), samples(samples)
	{	}

	void applyFadeOut(double seconds);

	std::uint32_t getSampleRate() const;
	std::uint32_t getByteRate() const;
	std::uint16_t getBlockAlign() const;
	std::uint16_t getNumChannels() const;
	std::uint16_t getBitsPerSample() const;

	std::vector<std::int16_t> getSamples() const;
	std::uint32_t getDataSize() const;
};