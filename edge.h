#pragma once

/**********************************************************
IMAGE PROCESSOR
edge.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include<iostream>
#include<iomanip>
#include<vector>

#include "tree.h"
#include "imagetypes.h"

//used for determining the edge pixels of a selection.
//a lot of magic happening here.
class Edge
{
public:
	Edge();
	Edge(const int, const int);
	void detect(std::vector<int>&, node*);
	std::vector<int>& getPerimiter();
	int getSizeofPerimeter();
	int getEdges();

private:
	void iterateEdges();
	void getOctan(const int);
	void check(const int, const int, const int, neighbor);
	void setField(neighbor);

	node *sel, *per, *edg;
	int field[8];
	bool fieldSet;

	std::vector<int> perimeter, stack;
	int numEdges, perimSize, width, total, tolerance;

	std::string edge_err = "::EDGE::error : ";
	std::string edge_warn = "::EDGE::warning : ";
};