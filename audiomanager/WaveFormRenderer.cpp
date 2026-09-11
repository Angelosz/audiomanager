#include "WaveFormRenderer.h"
#include <iostream>

Image WaveFormRenderer::renderAudioWave(Audio& audio, int width, int height)
{
	Image image(width, height);

	for (size_t x{ 0 }; x < width; ++x)
		image.markPixel(static_cast<int>(x), height / 2);

	std::vector<std::int16_t> samples = audio.getSamples();
	int audioSize = static_cast<int>(samples.size());
	int samplesPerPixel = audioSize / width;

	// 1920 iteraciones
	// cada iteración, miramos un número igual a samplesPerPixel de los samples, y escogemos los picos altos y bajos
	// esos picos son los pixeles que marcaremos con los pixeles, despues de normalizarlos
	



	return image;
}
