#pragma once

#include <sstream>
#include <vector>
#include "image.h"

struct pgmData {
	std::string filetype = "";
	std::vector<std::string> comment;
	int width, height, totalpixels, maxgreyval;
};
struct pgmPixel : pixel {
	int value;
};
enum pgmInfo {
	FILETYPE, COMMENTS, DIMENSIONS, TOTALPIXELS, MAXGREYVAL
};


class pgmImage : public Image
{
public:
	pgmImage();
	~pgmImage();
	bool checkExtension(const std::string);
	void load(const std::string);
	void write(const std::string);
	void print();
	void print(pixel);
	void printChoice();
	pixel* getpixels();

private:
	void print(int);

	pgmData data;
	pgmPixel * pixels;
};