#include "Image.h"

#include <fstream>
#include <iostream>

void Image::markPixel(int x, int y)
{
	if (
		x >= 0 && x < width &&
		y >= 0 && y < height
	) {
		pixels[static_cast<size_t>((width * y) + x)] = Pixel(0, 0, 0);
	}
}

void Image::drawVerticalLine(int x, int start, int end)
{
	if (
		x >= 0 && x < width &&
		start >= 0 && start < height &&
		end >= 0 && end < height
		) {
		int pixel = start;
		
		while (pixel != end) {
			if (pixel > end) pixel--;
			else if (pixel < end) pixel++;

			markPixel(x, pixel);
		}
	}
}

void Image::savePPM(const std::string& filePath) const
{
	std::ofstream file{
		filePath,
		std::ios::binary
	};

	if (!file) {
		std::cout << "Failed to create Image." << '\n';
		return;
	}

	file << "P6\n"
		<< width << ' ' << height << '\n'
		<< "255\n";

	for (const Pixel& pixel : pixels)
	{
		file.write(
			reinterpret_cast<const char*>(&pixel),
			sizeof(Pixel)
		);
	}
}
