#include "toolbox.h"

Toolbox::Toolbox() :
	img(NULL), pixels(NULL)
{}
Toolbox::Toolbox(pixel *p, const int w, const int t) 
	: imageWidth(w), totalPixels(t)
{
	addPixels(p);
}
Toolbox::~Toolbox() 
{
	if (pixels != NULL) pixels = NULL;
}
void Toolbox::addPixels(pixel *p)
{
	pixels = p;
}
void Toolbox::clean()
{
	if (pixels == NULL) { std::cout << toolbox_err << "no pixels loaded\n"; return; }

	int n;
	ofilename = "none";

	if (cmd.getcmd("write data to .csv file? [1]yes, [2]no, [q]quit - ", n, 2))
	{
		if (n == 1)
			cmd.getfile("enter data output file name : ", ofilename, ".csv", 2);

		run();
	}
}
void Toolbox::quickrun()
{
	if (pixels == NULL) return;

	Selection s(pixels, imageWidth, totalPixels);

	for (int i = 0; i < totalPixels; i++)
	{
		if (s.get(i))
		{
			buffer = s.getBuffer();

			data[1] = buffer.size();
			data[2] = data[1] / s.getEdges();
			data[0] = getAverageValue(data[1]);

			conf c = confidence::getconfidence(data);

			if (!c.isObj)
				cleanSelection(uint8_t(255), data[1]);

			if (ofile.is_open())
				printcsv(c);
		}
		s.clearBuffer();
		buffer.clear();
	}
}
void Toolbox::run()
{
	auto start = std::chrono::high_resolution_clock::now();

	int per_25 = totalPixels / 4;
	int per_50 = totalPixels / 2;
	int per_75 = per_25 + per_50;

	bool b_25 = false, b_50 = false, b_75 = false;

	if (ofilename != "none") 
	{
		ofilename = "data/" + ofilename;
		ofile.open(ofilename.c_str(), std::fstream::out);
		ofile << "val, size, edge, dust, obj, res, type, c avg, c edge, c size\n";
	}

	Selection s(pixels, imageWidth, totalPixels);

	for (int i = 0; i < totalPixels; i++)
	{
		if (s.get(i))
		{
			buffer = s.getBuffer();
			//perimeter = s.getPerimeter();

			data[1] = buffer.size();
			data[2] = data[1] / s.getEdges();
			data[0] = getAverageValue(data[1]);

			conf c = confidence::getconfidence(data);

			if (!c.isObj)
				cleanSelection(uint8_t(255), data[1]);
			
			if (ofile.is_open())
				printcsv(c);
		}
		s.clearBuffer();
		buffer.clear();
		
		if (i > per_25 && !b_25) {
			std::cout << "25%...\n";
			b_25 = true;
		}
		if (i > per_50 && !b_50) {
			std::cout << "50%...\n";
			b_50 = true;
		}
		if (i > per_75 && !b_75) {
			std::cout << "75%...\n";
			b_75 = true;
		}
	}
	ofile.close();

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<int64_t, std::nano> elapsed = finish - start;

	std::cout << toolbox_msg << "finished in " << elapsed.count() << " nanoseconds.\n\n";
}
void Toolbox::cleanSelection(const uint8_t color, const int size)
{
	for (int i = 0; i < size; i++)
		pixels[buffer[i]].value = color;
}
void Toolbox::colorbuffer(const uint8_t color, const int size)
{
	for (int i = 0; i < size; i++)
		pixels[buffer[i]].value = color;
}
void Toolbox::coloredges(const uint8_t color, const int size)
{
	for (int i = 0; i < size; i++)
		pixels[perimeter[i]].value = color;
}
void Toolbox::printcsv(conf& c)
{
	ofile << data[0] << "," << data[1] << "," << data[2] << "," << c.dust << "," << c.obj << ",";

	if (c.isObj) {
		ofile << c.obj - c.dust << ",obj," << c.o_val - c.d_val << "," << c.o_edge - c.d_edge << "," << c.o_size - c.d_size << "\n";
	}
	else {
		ofile << c.dust - c.obj << ",dust," << c.d_val - c.o_val << "," << c.d_edge - c.o_edge << "," << c.d_size - c.o_size << "\n";
	}
}
double Toolbox::getAverageValue(const int size)
{
	double avg = 0;
	for (int i = 0; i < size; i++)
		avg += pixels[buffer[i]].value;

	return avg / size;
}