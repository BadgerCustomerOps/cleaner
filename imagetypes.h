#pragma once

/**********************************************************
IMAGE PROCESSOR
imagetypes.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include <string>
#include <vector>

//the .pgm file's basic data
struct data {
	std::string filetype;
	int width, height, maxgreyval;
	int totalpixels;
};
//used for the menu's when the user selects to print certain data
enum info {
	ALL, FILETYPE, DIMENSIONS, TOTALPIXELS, MAXGREYVAL
};
//a basic pixel structure
struct pixel {
	bool selected = false;	//used for selection
	bool found = false;
	uint8_t value = 255;	//grey value
	int id = -1;			//ID [0->totalpixels]
};
//edge and filler use this for navigation around the pixel map
enum direction {
	none, up, down, left, right
};
//same deal, a little more abstract
struct pathDirection {
	direction dir = none;
	int id = -1;

	pathDirection(direction d, int i) { dir = d; id = i; }
};
//each pixel has eight neighbors
struct octan {
	int tl = -1, t = -1, tr = -1,
		l = -1, r = -1,
		bl = -1, b = -1, br = -1;
};
//same deal, different use
enum neighbor {
	tl, t, tr,
	l, r,
	bl, b, br
};
//confidence structure
struct conf {
	double obj = 0.0, dust = 0.0;
	double o_size = 0.0, d_size = 0.0;
	double o_edge = 0.0, d_edge = 0.0;
	double o_val = 0.0, d_val = 0.0;
	bool isObj;
};
//don't remember, too scared to delete
struct tup {
	int s, e;
	tup(int st, int en) { s = st, e = en; }
};