#pragma once

/**********************************************************
IMAGE PROCESSOR
selection.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include <iostream>
#include <vector>

#include "imagetypes.h"
#include "filler.h"
#include "edge.h"

const uint8_t VALUE_THRESHOLD = 255;

//these functions do a lot, so i won't explain all of them.
//selection class basically gets a non-white pixel and moves around the pixel 
//to fill out the object
class Selection
{
public:
	Selection();
	Selection(pixel*, const int, const int);
	bool get(const int); //takes a non-white pixel and does work on it

	std::vector<int>& getBuffer(); //return the buffer i.e. the full selection
	std::vector<int>& getPerimeter(); //return the perimeter i.e the edges of the selection (a subset of buffer)
	int getEdges();	//basically the size of the perimeter
	void clearBuffer();

private:
	void iterate(const int);
	void nextPixel(const int, const int);
	bool checkPixel(pixel&, const int);
	void fillPixels();
	void findEdges();

	pixel * pixels;
	int width, total;

	std::vector<int> buffer, perimeter;
	int bufferSize, numEdges;

	node * buff;

	std::string selection_err = "::SELECTION::error : ";
};