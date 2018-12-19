#pragma once

/**********************************************************
IMAGE PROCESSOR
tree.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include <iostream>
#include <vector>
#include <list>
#include "imagetypes.h"

struct node
{
	node *left, *right;
	int id;

	node(int i) { left = NULL; right = NULL; id = i; }
};
//self explainatory
class Tree
{
public:
	static bool insert(node*&, const int);
	static int	findNode(node*&, const int);
	static void deleteTree(node*&);
	static void buildTree(std::vector<int>&, node*&); //builds a balanced tree given a vector - can be a useful optimization
	static void getInOrder(node*&, std::vector<int>&); //helps build a balanced tree


	std::string tree_err = "::TREE::error : ";
};