#include <iostream>
#include "AudioManager.h"

int main()
{
	AudioManager audioManager;

	Audio audio = audioManager.loadAudio("resources/audio/background_music.wav");

	audioManager.saveAudio(audio, "output/background_music_modified.wav");

	return 0;
}