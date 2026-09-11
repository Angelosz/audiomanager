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

	int width, height;
	std::vector<Pixel> pixels;

public:
	Image(int width, int height)
		: width(width), height(height)
	{
		pixels.resize(static_cast<std::size_t>(width * height));
	}

	void markPixel(int x, int y);

	void savePPM(const std::string& filePath) const;
};