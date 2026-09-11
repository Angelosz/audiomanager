#pragma once
#include <string>
#include "Audio.h"

class AudioManager
{
public:
	Audio loadAudio(const std::string filePath) const;
	void saveAudio(Audio& audio, std::string filepath);
};
