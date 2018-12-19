#pragma once

/**********************************************************
IMAGE PROCESSOR
command.h
author: austin herman
last update: 9/20/2018
changelog:
typed up some comments
**********************************************************/

#include <iostream>
#include <string>

#include "imagetypes.h"

//used to prompt the GUI's and get user input.
//makes things generally more clean, nothing fancy here
class Command
{
public:
	Command();
	bool getcmd(std::string, int&, int);
	bool getfile(std::string, std::string&, std::string, int);

	void newQuit(std::string);
	void newTab(std::string);

private:
	std::string quit, tab;
	std::string command_err = "::COMMAND::error : ";
};