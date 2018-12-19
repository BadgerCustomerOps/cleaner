#pragma once

/**********************************************************
IMAGE PROCESSOR
image.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

#include "imagetypes.h"
#include "command.h"

//basic image class, must be pgm
//these are pretty self explainatory nothing magical happening
class Image 
{
public:
	Image();
	~Image();
	bool load(const std::string&);
	void write(const std::string&);
	
	void printmenu();
	
	pixel*& getpixels();
	data&   getImageData();

private:
	void loadP2(std::ifstream&, std::string&);
	void loadP5(std::ifstream&, std::string&);

	void print();
	void printChoice();
	void print(const int);

	bool	dataLoaded;
	data	data;
	pixel * pixels;
	Command cmd;

	std::string image_err = "::IMAGE::error : ";
	std::string image_msg = "::IMAGE::message : ";
};