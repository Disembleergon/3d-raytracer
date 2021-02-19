#pragma once

#include "Color.h"
#include <string>
#include <vector>

class Canvas {

private:
	const int m_width;
	const int m_height;

	using pixel_row_t = std::vector<Color>;
	using pixel_canvas_t = std::vector<pixel_row_t>;
	pixel_canvas_t m_pixels;

public:
	Canvas(const int& w, const int& h);
	void write_pixel(const int& x, const int& y, const Color& clr);
	Color pixel_at(const int& x, const int& y);
	void toPPM(const std::string& filepath);

};