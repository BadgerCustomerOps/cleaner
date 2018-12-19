#pragma once

/**********************************************************
IMAGE PROCESSOR
toolbox.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include <iostream>
#include <chrono>

#include "image.h"
#include "imagetypes.h"
#include "selection.h"
#include "confidence.h"

//does drives the algorithms for finding and "doing work" on pixels
class Toolbox
{
public:
	Toolbox();
	Toolbox(pixel *, const int, const int);
	~Toolbox();
	void addPixels(pixel *);		//send an array of pixel data
	void clean();					//gets some info for saving data, then taps run()

private:
	void run();	//the big boy, iterates through the pixels and drives algorithms

	void cleanSelection(const uint8_t, const int);	//cleans a selection of pixels
	void colorbuffer(const uint8_t, const int);		//colors a selection of pixels
	void coloredges(const uint8_t, const int);		//colors the edges of a selection of pixels
	void printcsv(conf&);	//writes some data to a csv, if the user wants
	
	double getAverageValue(const int);	//gets some data on the selection

	Image * img;
	pixel * pixels;
	Command cmd;

	int imageWidth, totalPixels;
	std::vector<int> buffer, perimeter;
	double data[3]; //average value, size, number of edges

	std::string ofilename;
	std::fstream ofile;
	
	std::string toolbox_err = "::TOOLBOX::error : ";
	std::string toolbox_msg = "::TOOLBOX::message : ";
};