#include "command.h"

Command::Command() 
	: quit("q"), tab(">> ")
{}
bool Command::getcmd(std::string question, int& cmd, int level)
{
	std::string u = "", t = "";
	int n = -1;
	bool good = false;

	for (int i = 0; i < level; i++) t += tab;

	std::cout << t << question;

	while (!good)
	{
		std::cin >> u;

		if (u == quit) break;
		else {
			try { n = stoi(u); }
			catch (const std::invalid_argument& bad) {
				std::cout << command_err << "invalid command\n";
				u = bad.what();	//avoid annoying warnings
				continue;
			}

			good = true;
			cmd = n;
		}
	}

	return good;
}
bool Command::getfile(std::string question, std::string& file, std::string filetype, int level)
{
	std::string u = "", t = "";
	bool good = false;

	for (int i = 0; i < level; i++) t += tab;

	std::cout << t << question;

	while (!good)
	{
		std::cin >> u;

		if (u == quit) break;
		else if (u.size() > filetype.size())
		{
			if (u.substr(u.length() - 4, 4) == filetype) {
				good = true;
			}
			else
				std::cout << tab << command_err << "bad filetype - " << u.substr(u.length() - 4, 4) << "\n";
		}
		else {
			std::cout << tab << command_err << "bad file name - " << u << "\n";
		}
	}

	file = u;

	return good;
}
void Command::newQuit(std::string q)
{
	quit = q;
}
void Command::newTab(std::string t)
{
	if (t.substr(t.size() - 1) != " ")
		tab = t + " ";
	else
		tab = t;
}