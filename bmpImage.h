#pragma once

#include "image.h"
#include <cmath>
#include <stdio.h>

const int HEADER_SIZE = 14;
const int HEADER_INFO_SIZE = 40;

struct bmpheader {
	char headerInfo[2];
	int filesize = 0;
	unsigned int imageOffset = 0;
};
struct bmpPixel : pixel {
	unsigned int r;
	unsigned int g;
	unsigned int b;
};
struct bmpheaderinfo {
	int headerInfoSize = 0;
	int height = 0;
	int width = 0;
	int bpp = 0;
	int compression = 0;
	int imageSize = 0;
	int rowsize = 0;
	int rowpadding = 0;
	int totalBytes = 0;

};
enum info {
	ALL, HEADER, HEADERDATA,
	HEADERINFO, FILESIZE, IMAGEOFFSET,
	HEADERINFOSIZE, PIXELDIMENSIONS, BPP, COMPRESSION, IMAGESIZE, ROWSIZE, ROWPADDING, TOTALBYTES
};

class bmpImage : public Image
{
public:
	bmpImage();
	~bmpImage();
	bool checkExtension(std::string);
	void load(const std::string);
	void write(const std::string);
	void print();
	void print(pixel);
	void printChoice();

private:
	void print(int);

	unsigned char	imageHeader[HEADER_SIZE], imageHeaderInfo[HEADER_INFO_SIZE];
	bmpheader mheader;
	bmpheaderinfo data;
	bmpPixel * pixels;
};