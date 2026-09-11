#pragma once

#include <vector>
#include "Audio.h"
#include "Image.h"

class WaveFormRenderer
{
public:
	Image renderAudioWave(Audio& audio, int width, int height);
};