#include <iostream>
#include "AudioManager.h"
#include "Image.h"
#include "WaveFormRenderer.h"

int main()
{
	AudioManager audioManager;
	Audio audio = audioManager.loadAudio("resources/audio/background_music.wav");

	std::cout << audio.getSampleRate();

	WaveFormRenderer waveFormRenderer;
	Image image = waveFormRenderer.renderAudioWave(audio, 1920, 1080);
	image.savePPM("output/image_before.ppm");

	audio.applyFadeOut(2);

	image = waveFormRenderer.renderAudioWave(audio, 1920, 1080);
	image.savePPM("output/image_after.ppm");
	audioManager.saveAudio(audio, "output/background_music_modified.wav");

	return 0;
}