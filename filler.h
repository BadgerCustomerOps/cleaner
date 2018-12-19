#pragma once

/**********************************************************
IMAGE PROCESSOR
filler.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include <iostream>
#include <vector>

#include "imagetypes.h"

//fill's in a selection's 'contained' white pixels
//a lot of magic here.
class Filler
{
public:
	Filler();
	Filler(pixel*&, const int, const int);
	void getPixels(pixel*);
	void getBounds(const int);
	void start(const int);
	void clearFoundBuffer();
	void printBounds();
	std::vector<pathDirection>& getPath();

private:
	bool inbounds(const int);
	void iteratePath();
	void check(pathDirection);
	void addtoPath(pathDirection);
	void clearPath();

	pixel * p;
	int width, total;
	int topmost, bottommost, leftmost, rightmost; 
	std::vector<pathDirection> path;
	std::vector<int> foundBuffer;
	int pathSize;
	bool boundsError;

	std::string filler_err = "::FILLER::error : ";
	std::string filler_warn = "::FILLER::warning : ";
};