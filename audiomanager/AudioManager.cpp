#include <fstream>
#include "AudioManager.h"
#include "Audio.h"
#include <iostream>

namespace {
    void readHeader(std::ifstream& file) {
        char riff[4];
        std::uint32_t size;
        char format[4];

        file.read(riff, 4);
        file.read(reinterpret_cast<char*>(&size), sizeof(size));
        file.read(format, 4);
    }

    void moveToNextChunk(std::ifstream& file, const std::uint32_t& chunkSize)
    {
        if (chunkSize % 2 != 0) file.seekg(1, std::ios::cur);
        file.seekg(chunkSize, std::ios::cur);
    }
}

Audio AudioManager::loadAudio(std::string filePath) const
{
    std::ifstream file{
        filePath,
        std::ios::binary
    };

    readHeader(file);

    std::uint32_t sampleRate{ 0 };
    std::uint16_t numChannels{ 0 };
    std::uint16_t bitsPerSample{ 0 };
    std::vector<std::int16_t> samples;

    while (file)
    {
        char chunkId[4];
        std::uint32_t chunkSize;

        file.read(chunkId, 4);
        file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));

        std::string id(chunkId, 4);

        if (id == "fmt ")
        {
            std::uint16_t audioFormat;
            std::uint32_t byteRate;
            std::uint16_t blockAlign;

            file.read(reinterpret_cast<char*>(&audioFormat), sizeof(audioFormat));
            file.read(reinterpret_cast<char*>(&numChannels), sizeof(numChannels));
            file.read(reinterpret_cast<char*>(&sampleRate), sizeof(sampleRate));
            file.read(reinterpret_cast<char*>(&byteRate), sizeof(byteRate));
            file.read(reinterpret_cast<char*>(&blockAlign), sizeof(blockAlign));
            file.read(reinterpret_cast<char*>(&bitsPerSample), sizeof(bitsPerSample));
            
            continue;
        }

        if (id == "data")
        {
            samples.resize(chunkSize / sizeof(std::int16_t));

            file.read(
                reinterpret_cast<char*>(samples.data()),
                chunkSize
            );

            continue;
        }

        moveToNextChunk(file, chunkSize);
    }

    return Audio(sampleRate, numChannels, bitsPerSample, samples);
}

void AudioManager::saveAudio(Audio& audio, std::string filepath)
{
    std::ofstream file{filepath, std::ios::binary};

    if (!file)
    {
        std::cout << "No se pudo crear el archivo." << '\n';
        return;
    }

    const std::uint16_t audioFormat = 1;
    const std::uint32_t sampleRate = audio.getSampleRate();
    const std::uint16_t bitsPerSample = audio.getBitsPerSample();
    const std::uint16_t numChannels = audio.getNumChannels();
    const std::uint32_t byteRate = audio.getByteRate();
    const std::uint16_t blockAlign = audio.getBlockAlign();

    const std::vector<int16_t> samples = audio.getSamples();

    const std::uint32_t fmtChunkSize = 16;
    const std::uint32_t dataSize = audio.getDataSize();
    const std::uint32_t fileSize = 4 + (8 + fmtChunkSize) + (8 + dataSize);

    file.write("RIFF", 4);
    file.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));
    file.write("WAVE", 4);

    file.write("fmt ", 4);
    file.write(reinterpret_cast<const char*>(&fmtChunkSize), sizeof(fmtChunkSize));

    file.write(reinterpret_cast<const char*>(&audioFormat), sizeof(audioFormat));
    file.write(reinterpret_cast<const char*>(&numChannels), sizeof(numChannels));
    file.write(reinterpret_cast<const char*>(&sampleRate), sizeof(sampleRate));
    file.write(reinterpret_cast<const char*>(&byteRate), sizeof(byteRate));
    file.write(reinterpret_cast<const char*>(&blockAlign), sizeof(blockAlign));
    file.write(reinterpret_cast<const char*>(&bitsPerSample), sizeof(bitsPerSample));

    file.write("data", 4);
    file.write(reinterpret_cast<const char*>(&dataSize), sizeof(dataSize));
    file.write(reinterpret_cast<const char*>(samples.data()), dataSize);

    std::cout << "Audio saved at :" << filepath << '\n';
}
