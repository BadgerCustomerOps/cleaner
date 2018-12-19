#include "image.h"

Image::Image()
	: pixels(NULL), dataLoaded(false)
{}
Image::~Image()
{ //selecting to load a new image > quit load > reload - tries to delete, not set to null
	if (pixels != NULL) {
		delete[] pixels;
		pixels = NULL;
	}
}
bool Image::load(const std::string& filename)
{
	std::ifstream infile(filename, std::ios_base::binary);
	std::stringstream ss;
	std::string inputline = "";

	if (!infile) {
		std::cout << image_err << "could not open file: " << filename << "\n";
		return false;
	}

	//first line is always version
	getline(infile, inputline);

	data.filetype = inputline.substr(0,2);
	if (!(data.filetype != "P5" || data.filetype != "P2")) {
		std::cout << image_err << "invalid file type: " << data.filetype << "\n";
		return false;
	}

	//ignore comments
	while (true) {
		getline(infile, inputline);
		if (inputline[0] != '#') break;
	}

	//get width, height, and total
	ss << inputline;
	ss >> data.width >> data.height;
	data.totalpixels = data.width * data.height;

	//get maximum grey value in file
	getline(infile, inputline);
	std::stringstream s(inputline);
	s >> data.maxgreyval;

	//get image data
	if (data.filetype == "P2") loadP2(infile, inputline);
	else loadP5(infile, inputline);

	infile.close();
	std::cout << "successfully loaded...\n";
	dataLoaded = true;
	return true;
}
void Image::write(const std::string& filename)
{
	if (!dataLoaded) { std::cout << image_err << "image data not loaded\n"; return; }

	if (data.filetype == "P2")
	{
		std::ofstream ofile;
		ofile.open(filename);

		ofile << data.filetype << "\n" << data.width << " " << data.height << "\n" << data.maxgreyval << "\n";

		for (int i = 0; i < data.totalpixels; i++)
			ofile << pixels[i].value << "\n";
	}
	else {
		std::ofstream ofile;
		ofile.open(filename, std::ios_base::out|std::ios_base::binary|std::ios_base::trunc);

		ofile << data.filetype << "\n" << data.width << " " << data.height << "\n" << data.maxgreyval << "\n";

		for (int i = 0; i < data.totalpixels; i++) //ofile >> std::hex >> pixels[i].value;
			ofile.write(reinterpret_cast<char*>(&pixels[i].value), sizeof(unsigned char));
	}
}
void Image::loadP2(std::ifstream& infile, std::string& inputline)
{
	//get image data
	pixels = new pixel[data.totalpixels];

	int i = 0, val;
	while (infile >> val)	//while (getline(infile, inputline))
	{
		//std::stringstream s(inputline);
		//s >> val;
		pixels[i].value = val;
		pixels[i].id = i;
		i++;
	}
}
void Image::loadP5(std::ifstream& infile, std::string& inputline)
{
	//get image data - NEEDS TO READ BYTES THIS WAY DUE TO CHAR CONVERSION ERRORS
	pixels = new pixel[data.totalpixels];
	
	char * buffer = new char[data.totalpixels];

	infile.read(buffer, data.totalpixels);

	for (int i = 0; i < data.totalpixels; i++) {
		pixels[i].value = uint8_t(buffer[i]);
		pixels[i].id = i;
	}

}
void Image::printmenu()
{
	if (!dataLoaded) { std::cout << image_err << "image data not loaded\n"; return; }

	std::string u = "";
	int n;

	if (cmd.getcmd("[1]print all, [2]image data menu, [q]quit - ", n, 1))
	{
		switch (n)
		{
		case 1: print(); break;
		case 2: printChoice(); break;
		}
	}
}
void Image::print()
{
	for (int i = 0; i < data.totalpixels; i++)
		std::cout << std::setw(4) << int(pixels[i].value) << " ";
}
void Image::printChoice()
{
	int n;

	if (cmd.getcmd("[1]all [2]file type, [3]dimensions, [4]total pixels, [5]max grey value - ", n, 2))
		print(n - 1);
}
void Image::print(const int i)
{
	switch (i)
	{
		case 0: {
			print(FILETYPE);
			print(DIMENSIONS);
			print(TOTALPIXELS);
			print(MAXGREYVAL);
			break;
		}
		case 1: std::cout << "file type: " << data.filetype << "\n"; break;
		case 2: printf("width: %i, height: %i\n", data.width, data.height); break;
		case 3: printf("total pixels: %i\n", data.totalpixels); break;
		case 4: printf("max grey value: %i\n", data.maxgreyval); break;
	}
}
pixel*& Image::getpixels()
{
	return pixels;
}
data& Image::getImageData()
{
	return data;
}