#pragma once

/**********************************************************
IMAGE PROCESSOR
home.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include "Image.h"
#include "toolbox.h"
#include "command.h"
#include "imagetypes.h"

//called by main, this is the driver for all of the tools
//mostly a bunch of menu displaying
class Home
{
public:
	Home();
	void run(); //runs the menus
	void quickrun(std::string);

private:
	void startmenu();		//initial menu when no image is loaded
	void fullmenu();		//menu with all options, only when image is loaded
	void loadfile();		//loads a pgm
	void loadfile(std::string);
	void writefile();		//writes to a pgm
	void writefile(std::string);
	void deleteimage();		//deletes the loaded image (only within the program)

	bool good;
	Command cmd;
	Toolbox* t;
	Image* img;

	std::string home_err = "::HOME::error : ";
};