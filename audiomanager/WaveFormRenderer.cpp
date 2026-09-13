#include "WaveFormRenderer.h"
#include <iostream>


Image WaveFormRenderer::renderAudioWave(const Audio& audio, int width, int height)
{
	Image image(width, height);

	for (size_t x{ 0 }; x < width; ++x)
		image.markPixel(static_cast<int>(x), height / 2);

	const std::vector<std::int16_t> samples = audio.getSamples();
	const std::size_t audioSize = samples.size();
	std::size_t samplesPerPixel = audioSize / static_cast<size_t>(width);

	const int centerY = height / 2;

	for (int column{ 0 }; column < width; ++column)
	{
		std::int16_t highestPeak{ 0 };
		std::int16_t lowestPeak{ 0 }; 

		std::size_t startingPixel = samplesPerPixel * column;

		if (samplesPerPixel * column + samplesPerPixel > audioSize)
		{
			samplesPerPixel = audioSize - startingPixel;
		}

		for (std::size_t index{ 0 }; index < samplesPerPixel; ++index)
		{
			std::int16_t sample = samples[index + startingPixel];

			if (sample > highestPeak) highestPeak = sample;
			else if (sample < lowestPeak) lowestPeak = sample;
		}

		image.drawVerticalLine(column, centerY - static_cast<int>((static_cast<double>(highestPeak) / 32768.0) * centerY), centerY);
		image.drawVerticalLine(column, centerY - static_cast<int>((static_cast<double>(lowestPeak) / 32768.0) * centerY), centerY);
	}

	return image;
}
