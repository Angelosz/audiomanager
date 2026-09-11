#include <iostream>
#include "AudioManager.h"
#include "Image.h"

int main()
{
	AudioManager audioManager;

	Audio audio = audioManager.loadAudio("resources/audio/background_music.wav");

	audioManager.saveAudio(audio, "output/background_music_modified.wav");

	Image image(100, 100);
	image.markPixel(50, 50);

	image.savePPM("output/image.ppm");

	return 0;
}