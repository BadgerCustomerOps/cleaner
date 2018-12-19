#include "bmpimage.h"

bmpImage::bmpImage()
{
	pixels = NULL;
	dataLoaded	= false;
}
bmpImage::~bmpImage()
{
	delete[] pixels;
}
bool bmpImage::checkExtension(const std::string f)
{
	std::string ext = f.substr(f.length() - 4, 4);

	if (ext != ".bmp") {
		std::cout << "Bad filetype:" << ext << "\n";
		return false;
	}

	return true;
}
void bmpImage::load(const std::string fileName)
{
	if (!checkExtension(fileName)) return;

	//image I/O
	std::ifstream inFile(fileName);
	if (!inFile) {
		std::cout << "Can't open file: " << fileName << "\n";
		return;
	}

	unsigned char val;
	for (int i = 0; i < HEADER_SIZE; i++) {
		inFile >> std::hex >> val;
		imageHeader[i] = val;
	}

	mheader.headerInfo[0] = imageHeader[0];
	mheader.headerInfo[1] = imageHeader[1];
	mheader.filesize	= imageHeader[2];
	mheader.imageOffset = imageHeader[10];

	if (imageHeader[0] != 'B' || imageHeader[1] != 'M') {
		std::cout << "Header info may be different\n";
		return;
	}
	if (imageHeader[11] != 0 || imageHeader[12] != 0 || imageHeader[13] != 0) {
		std::cout << "Error::image.h{" << __LINE__ << "}\n";
		return;
	}

	//get header info	
	//       4 bytes,  4 bytes, 4 bytes, 2 bytes,      2 bytes,   4 bytes,     4 bytes,    4 bytes,               4 bytes,             4 bytes,     4 bytes
	//size of header,  width,   height,  color planes, bpp,       compression, image size, horizontal resolution, vertical resolution, # of colors, # of important colors
	for (int i = 0; i < HEADER_INFO_SIZE; i++) {
		inFile >> std::hex >> val;
		imageHeaderInfo[i] = val;
	}

	//get info
	data.headerInfoSize = imageHeaderInfo[0];
	data.width = imageHeaderInfo[4];
	data.height = imageHeaderInfo[8];
	data.bpp = imageHeaderInfo[14];
	data.compression = imageHeaderInfo[16];
	data.imageSize = imageHeaderInfo[20];


	if (data.bpp != 24) {
		std::cout << "Program will only work with 24bpp: current bpp=" << data.bpp << "\n";
		return;
	}

	//get compression type
	if (data.compression != 0) {
		std::cout << "Compression type issue::image.h{" << __LINE__ << "}\n";
		return;
	}

	//calculate padding, rowsize and image size
	data.rowpadding = 4 - ((data.width * 3) % 4);
	data.rowsize = floor((data.bpp * data.width + 31) / 32) * 4;
	data.totalBytes = data.rowsize * abs(data.height);

	//create image data array and give it values
	pixels = new bmpPixel[data.width];
	unsigned char * imageCharData = new unsigned char[data.totalBytes];
	inFile.seekg(mheader.imageOffset, std::ios::beg);

	int c = 0;
	char v;
	while (inFile >> std::hex >> v) {
		imageCharData[c] = v;
		c++;
	}

	int j = 0, x = 0, y = 0;
	for (int i = 0; i < data.totalBytes; i++)
	{
		if (i >= data.width) {
			x = 0;
			y++;
		}

		pixels[j].x = x;
		pixels[j].y = y;

		pixels[j].r = imageCharData[i];
		pixels[j].g = imageCharData[i++];
		pixels[j].b = imageCharData[i++];

		j++;
		x++;
	}

	dataLoaded = true;
}
void bmpImage::write(const std::string fileName)
{
	if (!checkExtension(fileName)) return;
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }

	std::ofstream ofile;
	ofile.open(fileName, std::ios::binary);

	for (int i = 0; i < HEADER_SIZE; i++)	ofile << imageHeader[i];
	for (int i = 0; i < HEADER_INFO_SIZE; i++)	ofile << imageHeaderInfo[i];

	ofile.seekp(mheader.imageOffset, std::ios::beg);	//go to where the image bytes should begin

	for (int i = 0; i < data.width; i ++) {
		ofile << pixels[i].r << pixels[i].g << pixels[i].b;
	}

	ofile.close();

}
void bmpImage::print()
{
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }

	for (int i = 0; i < data.width; i++) {
		std::cout << pixels[i].r << " " << pixels[i].g << " " << pixels[i].b << " ";
	}
	std::cout << "\n";

}
void bmpImage::print(pixel p)
{
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }
	if (p.x > data.width && p.y > data.height) { std::cout << "(" << p.x << "," << p.y << ") exceeds image bounds of (" << data.width << "," << data.height << ")\n"; return; }

	p.y = data.height - 1 - p.y;

	int pos = p.x + p.y * data.width;

	printf("%i,%i,%i\n", pixels[pos].r, pixels[pos].g, pixels[pos].b);

}
void bmpImage::printChoice()
{
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }

	std::string c;
	std::cout << ">>>> [1]ALL, [2]HEADER, [3]HEADERDATA\n";
	std::cout << ">>>> [4]HEADERINFO, [5]FILESIZE, [6]IMAGEOFFSET\n";
	std::cout << ">>>> [7]HEADERINFOSIZE, [8]PIXELDIMENSIONS, [9]BPP, [10]COMPRESSION, [11]IMAGESIZE, [12]ROWSIZE, [13]ROWPADDING, [14]TOTALBYTES\n";

	while (true) {
		std::cout << ">>>> : ";
		std::cin >> c;
		if (c == "q") break;
		else {
			try {
				print(std::stoi(c) - 1);
			}
			catch (const std::invalid_argument& bad) {
				std::cout << "invalid command\n";
			}
		}
	}
}
void bmpImage::print(int i)
{
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }

	switch (i)
	{
		case 0: {
			print(HEADER);
			print(HEADERDATA);
			break;
		}
		case 1: {
			printf("+Header+\n");
			print(HEADERINFO);
			print(FILESIZE);
			print(IMAGEOFFSET);
			break;
		}
		case 2: {
			printf("+Header Info+\n");
			print(HEADERINFOSIZE);
			print(PIXELDIMENSIONS);
			print(BPP);
			print(COMPRESSION);
			print(IMAGESIZE);
			print(ROWSIZE);
			print(ROWPADDING);
			print(TOTALBYTES);
			break;
		}
		case 3: printf("Header Field: %i%i\n", mheader.headerInfo[0], mheader.headerInfo[1]); break;
		case 4: printf("File size in bytes: %i\n", mheader.filesize); break;
		case 5: printf("Image Starting Offset: %i\n", mheader.imageOffset); break;

		case 6: printf("Header Info Size: %i\n", data.headerInfoSize); break;
		case 7: printf("Pixel Dimensions: w:%i, h:%i\n", data.width, data.height); break;
		case 8: printf("Bits Per Pixel: %i\n", data.bpp); break;
		case 9: printf("Compression: %i\n", data.compression); break;
		case 10: printf("Size of Raw Bitmap Data: %i\n", data.imageSize); break;
		case 11: printf("Size of one row: %i\n", data.rowsize); break;
		case 12: printf("Padding in one row: %i\n", data.rowpadding); break;
		case 13: printf("Image size in bits: %i\n", data.totalBytes); break;
	}

}