#include "home.h"

/**********************************************************
IMAGE PROCESSOR
main
author: austin herman
email: ashe223@g.uky.edu || austin_herman@jabil.com
last update: 9/20/2018
changelog:
typed up some comments and created a distributable .exe
**********************************************************/

//there's a lot of magic in these that i won't really explain
//through comments, so just shoot me an email or something
//if you want to know details.
int main(int argc, char *argv[]) 
{
	std::cout << "\t\t//image processor\\\\ \n";
	
	Home h;
	
	if (argc > 0)	
		h.quickrun(argv[1]);
	else 
		h.run();

	system("pause");
	
	return 0;

}