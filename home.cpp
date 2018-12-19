#include "home.h"

Home::Home() 
	: good(true), t(NULL), img(NULL)
{}
void Home::run()
{
	while (good) 
	{
		if (img == NULL)
			startmenu();
		else
			fullmenu();
	}

	deleteimage();
}
void Home::startmenu()
{
	int n;
	if (cmd.getcmd("[1]load - ", n, 0))
	{
		if (n == 1)
			loadfile();
		else 
			std::cout << home_err << "invalid command\n";
	}
	else
		good = false;
}
void Home::fullmenu()
{
	int n;
	if (cmd.getcmd("[1]load, [2]save, [3]print menu, [4]clean [q]quit - ", n, 0))
	{
		switch (n)
		{
			case 1: loadfile(); break;
			case 2: writefile(); break;
			case 3: {
				if (img != NULL)
					img->printmenu();
				else
					std::cout << home_err << "image not loaded\n";
				break;
			}
			case 4: {
				if (t != NULL)
					t->clean();
				else
					std::cout << home_err << "toolbox not loaded\n";
				break;
			}
		}
	}
	else good = false;
}
void Home::loadfile()
{
	std::string f = "";
	int n;

	if (img != NULL) {
		if (cmd.getcmd("delete loaded image? [1]yes, [q]quit - ", n, 1))
			deleteimage();
		else return;
	}

	if(cmd.getfile("enter file name : ", f, ".pgm", 1))
	{
		img = new Image();

		f = "images/" + f;

		if(img->load(f))
			t = new Toolbox(img->getpixels(), img->getImageData().width, img->getImageData().totalpixels);
		else {
			deleteimage();
		}
	}
}
void Home::loadfile(std::string f)
{
	img = new Image();

	f = "images/" + f;

	if (img->load(f)) {
		t = new Toolbox(img->getpixels(), img->getImageData().width, img->getImageData().totalpixels);
		std::cout << "loaded " << f << "\n";
	}
	else {
		deleteimage();
		std::cout << "couldn't load " << f << "\n";
	}
}
void Home::writefile()
{
	if (img != NULL)
	{
		std::string f = "";
		if (cmd.getfile("enter file name : ", f, ".pgm", 1)) {
			f = "saves/" + f;
			img->write(f);
		}
	}
	else std::cout << home_err << "no image loaded to save";
}
void Home::writefile(std::string f)
{
	if (img != NULL) {
		img->write(f);
	}	
}
void Home::deleteimage()
{
	if (t != NULL) {
		delete t;
		t = NULL;
	}
	delete img;
	img = NULL;
}
void Home::quickrun(std::string f)
{
	loadfile(f);
	t->quickrun();
	writefile(f);
	deleteimage();
}