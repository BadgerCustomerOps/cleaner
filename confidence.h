#pragma once

/**********************************************************
IMAGE PROCESSOR
confidence.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include <iostream>
#include "imagetypes.h"

//this guy makes a decision on whether the selection is
//dust or an object
class confidence
{
public:
	static conf getconfidence(const double[]);

private:
	static void edges(conf&, const double);
	static void size(conf&, const double);
	static void value(conf&, const double);
};