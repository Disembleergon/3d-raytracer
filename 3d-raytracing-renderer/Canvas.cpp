#include "Canvas.h"
//#include <sstream>
#include <fstream>

Canvas::Canvas(const int& w, const int& h) : m_width{w}, m_height{h} {	

	// Fill canvas with m_height * m_width pixels of default color
	for(int row = 0; row < m_height; row++) {
		pixel_row_t pixel_row{};		
		for(int col = 0; col < m_width; col++) {
			pixel_row.push_back(Color{});
		}
		m_pixels.push_back(pixel_row);
	}

}

void Canvas::write_pixel(const int& col, const int& row, const Color& clr) {
	m_pixels[row][col] = clr;
}

Color Canvas::pixel_at(const int& col, const int& row){
	return m_pixels[row][col];
}

void Canvas::toPPM(const std::string& fn) {

	std::ofstream outp(fn);
	outp << "P3\n" + std::to_string(this->m_width) + " " + std::to_string(this->m_height) + "\n255\n\n";

	for (int row = 0; row < this->m_height; row++) {

		for (int col = 0; col < this->m_width; col++) {

			Color clr = m_pixels[row][col];
			outp << clr.red << " " << clr.green << " " << clr.blue << "  ";

		}

		outp << "\n";

	}

	outp.close();

}