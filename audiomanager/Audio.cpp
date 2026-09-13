#include "Audio.h"
#include <iostream>

void Audio::applyFadeOut(double seconds)
{
    std::size_t lastSecondsFrames = static_cast<std::size_t>(seconds * sampleRate);
    const std::size_t totalFrames = samples.size() / numChannels;

    if (lastSecondsFrames > totalFrames)
        lastSecondsFrames = totalFrames;

    const std::size_t startingFrame = totalFrames - lastSecondsFrames;

    for (std::size_t frame = startingFrame; frame < totalFrames; ++frame)
    {
        const double alphaProgress = static_cast<double>(frame - startingFrame) / static_cast<double>(lastSecondsFrames);
        const double volume = 1.0 - alphaProgress;

        for (std::size_t channel = 0; channel < numChannels; ++channel)
        {
            const std::size_t sampleIndex = frame * numChannels + channel;

            samples[sampleIndex] = static_cast<std::int16_t>(samples[sampleIndex] * volume);
        }
    }
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
