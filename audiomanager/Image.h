#pragma once

#include <vector>
#include <string>

class Image
{
	struct Pixel
	{
		std::uint8_t r;
		std::uint8_t g;
		std::uint8_t b;

		Pixel(std::uint8_t r = 255, std::uint8_t g = 255, std::uint8_t b = 255)
			: r(r), g(g), b(b) {
		}
	};

	std::size_t width, height;
	std::vector<Pixel> pixels;

public:
	Image(std::size_t width, std::size_t height)
		: width(width), height(height), pixels(width* height)
	{
	}

	void markPixel(std::size_t x, std::size_t y);

	void savePPM(const std::string& filePath) const;
};