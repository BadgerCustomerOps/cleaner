#include "pgmImage.h"

pgmImage::pgmImage()
{
	pixels = NULL;
	dataLoaded = false;
}
pgmImage::~pgmImage()
{
	delete pixels;
}
bool pgmImage::checkExtension(const std::string f)
{
	std::string ext = f.substr(f.length() - 4, 4);
	if (ext != ".pgm") {
		std::cout << "Bad filetype:" << ext << "\n";
		return false;
	}
	return true;
}
void pgmImage::load(const std::string filename)
{
	if (!checkExtension(filename)) return;

	std::ifstream infile(filename);
	std::stringstream ss;
	std::string inputline = "";

	if (!infile) {
		std::cout << "could not open file: " << filename << "\n";
		return;
	}

	//first line is always version
	getline(infile, inputline);

	data.filetype = inputline.substr(0, 2);
	if (data.filetype == "P5") {
		std::cout << "filetype is P5\n";
		//raw format
	}
	else if (data.filetype == "P2") {
		std::cout << "filetype is P2\n";
		//plain format
	}
	else {
		std::cout << "Invalid file type: " << data.filetype << "\n";
		return;
	}
	
	//get comments
	while (true)
	{
		getline(infile, inputline);
		if (inputline[0] == '#') {
			data.comment.push_back(inputline);
			std::cout << inputline;
			std::cout << "\n";
		}
		else break;
	}
	
	//get width, height, and total
	ss << inputline;
	ss >> data.width >> data.height;

	std::cout << "width/height: " << data.width << " " << data.height << "\n";
	data.totalpixels = data.width * data.height;

	//get maximum grey value in file
	getline(infile, inputline);
	std::stringstream s(inputline);
	s >> data.maxgreyval;
	std::cout << "max grey val = " << data.maxgreyval << "\n";
	
	//get image data
	pixels = new pgmPixel[data.totalpixels];

	int i = 0;
	int val;

	while (getline(infile, inputline))
	{
		std::stringstream s(inputline);
		s >> val;
		pixels[i].value = val;
		i++;
	}

	std::cout << "stored: " << i << " values\n";

	infile.close();

	dataLoaded = true;
}
void pgmImage::write(const std::string filename)
{
	if (!checkExtension(filename)) return;
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }
	
	std::ofstream ofile;
	ofile.open(filename);

	if (data.filetype == "P2") 
	{
		ofile << data.filetype << "\n";

		for (int i = 0; i < data.comment.size(); i++)
			ofile << data.comment[i] << "\n";

		ofile << data.width << " " << data.height << "\n";
		ofile << data.maxgreyval << "\n";

		for (int i = 0; i < data.totalpixels; i++)
			ofile << pixels[i].value << "\n";
	}
}
void pgmImage::print()
{
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }

	int c = 0;
	for (int i = 0; i < data.totalpixels; i++) {
		std::cout << pixels[i].value;
		if (c == data.width - 1) {
			std::cout << "\n"; 
			c = 0;
		}
		else c++;
	}
}
void pgmImage::print(pixel p)
{
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }
	if (p.x > data.width - 1 || p.y > data.height - 1) { std::cout << "(" << p.x << "," << p.y << ") exceeds image bounds of (" << data.width << "," << data.height << ")\n"; return; }

	std::cout << pixels[p.x + p.y * data.width].value << "\n";
}
void pgmImage::printChoice()
{
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }

	std::string c;
	std::cout << ">>>> [1]ALL\n";
	std::cout << ">>>> [2]FILETYPE, [3]COMMENTS, [4]DIMENSIONS, [5]TOTALPIXELS, [6]MAXGREYVAL\n";

	while (true) {
		std::cout << ">>>> : ";
		std::cin >> c;
		if (c == "q") break;
		else {
			try { print(std::stoi(c) - 1); }
			catch (const std::invalid_argument& bad) { std::cout << "invalid command\n"; }
		}
	}
}
void pgmImage::print(int i)
{
	if (!dataLoaded) { std::cout << "Image data not loaded\n"; return; }

	switch (i)
	{
		case 0: {
			print(FILETYPE);
			print(COMMENTS);
			print(DIMENSIONS);
			print(TOTALPIXELS);
			print(MAXGREYVAL);
			break;
		}
		case 1: printf("File Type: %i\n", data.filetype); break;
		case 2: {
			for (int i = 0; i < data.comment.size(); i++) 	printf("Comment: %i\n", data.comment[i]);
			break;
		}
		case 3: printf("Width: %i, Height: %i\n", data.width, data.height); break;
		case 4: printf("Total Pixels: %i\n", data.totalpixels); break;
		case 5: printf("Max Grey Value: %i\n", data.maxgreyval); break;
	}
}
pixel* pgmImage::getpixels()
{
	return pixels;
}