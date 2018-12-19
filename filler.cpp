#include "filler.h"

Filler::Filler() : topmost(-1), bottommost(-1), leftmost(-1), rightmost(-1), pathSize(0), boundsError(false)
{
	std::cout << filler_warn << "object created with out passing pixels and information.\n";
}
Filler::Filler(pixel*& p, const int imageWidth, const int totalPixels) : 
	topmost(totalPixels), bottommost(-1), leftmost(imageWidth), rightmost(-1), pathSize(0), boundsError(false)
{
	getPixels(p);
	width = imageWidth;
	total = totalPixels;
}
void Filler::getPixels(pixel* p)
{
	this->p = p;
}
void Filler::getBounds(const int id)
{	
	if ((id % width) < leftmost) leftmost = id % width;

	if ((id % width) > rightmost) rightmost = id % width;

	if (id < topmost) topmost = id;

	if (id > bottommost) bottommost = id;

}
bool Filler::inbounds(const int id)
{
	if (id % width <= leftmost
	 || id % width >= rightmost
	 || id < topmost
	 || id > bottommost)
		return false;
	
	return true;
}
void Filler::start(const int id)
{
	path.clear();
	pathSize = 0;
	boundsError = false;

	addtoPath(pathDirection(none, id));

	if (boundsError) {
		clearPath();
		return;
	}

	iteratePath();
}
void Filler::addtoPath(pathDirection pd)
{
	if (!inbounds(pd.id))	boundsError = true;
	else {
		path.push_back(pd);
		pathSize++;
		p[pd.id].selected = true;
	}
}
void Filler::iteratePath()
{
	for (int i = 0; i < pathSize; i++) 
	{
		check(path[i]);
		
		if (boundsError) {
			clearPath();
			return;
		}
	}
}
void Filler::check(pathDirection pd)
{
	if (pd.id < 0) {
		std::cout << pd.id << "\n";
	}

	switch (pd.dir) //0 none, 1 up, 2 down, 3 left, 4 right
	{
		case 1: 
		{
			if (pd.id - width > 0) {
				if (!p[pd.id - width].selected	&& !p[pd.id - width].found)	addtoPath(pathDirection(up, pd.id - width));	//up
			}
			if (pd.id % width != 0) {
				if (!p[pd.id - 1].selected		&& !p[pd.id - 1].found)		addtoPath(pathDirection(left, pd.id - 1));		//left
			}
			if ((pd.id + 1) % width != 0) {
				if (!p[pd.id + 1].selected		&& !p[pd.id + 1].found)		addtoPath(pathDirection(right, pd.id + 1));		//right
			}
			break;
		}
		case 2:
		{
			if (pd.id + width < total) {
				if (!p[pd.id + width].selected	&& !p[pd.id + width].found)	addtoPath(pathDirection(down, pd.id + width));	//down
			}
			if (pd.id % width != 0) {
				if (!p[pd.id - 1].selected		&& !p[pd.id - 1].found)		addtoPath(pathDirection(left, pd.id - 1));		//left
			}
			if ((pd.id + 1) % width != 0) {
				if (!p[pd.id + 1].selected		&& !p[pd.id + 1].found)		addtoPath(pathDirection(right, pd.id + 1));		//right
			}
			break;
		}
		case 3:
		{
			if (pd.id - width > 0) {
				if (!p[pd.id - width].selected	&& !p[pd.id - width].found)	addtoPath(pathDirection(up, pd.id - width));	//up
			}
			if (pd.id + width < total) {
				if (!p[pd.id + width].selected	&& !p[pd.id + width].found)	addtoPath(pathDirection(down, pd.id + width));	//down
			}
			if (pd.id % width != 0) {
				if (!p[pd.id - 1].selected		&& !p[pd.id - 1].found)		addtoPath(pathDirection(left, pd.id - 1));		//left
			}
			break;
		}
		case 4:
		{
			if (pd.id - width > 0) {
				if (!p[pd.id - width].selected	&& !p[pd.id - width].found)	addtoPath(pathDirection(up, pd.id - width));	//up
			}
			if (pd.id + width < total) {
				if (!p[pd.id + width].selected	&& !p[pd.id + width].found)	addtoPath(pathDirection(down, pd.id + width));	//down
			}
			if ((pd.id + 1) % width != 0) {
				if (!p[pd.id + 1].selected		&& !p[pd.id + 1].found)		addtoPath(pathDirection(right, pd.id + 1));		//right
			}
		}
		case 0:
		{
			if (pd.id - width > 0) {
				if (!p[pd.id - width].selected	&& !p[pd.id - width].found)	addtoPath(pathDirection(up, pd.id - width));	//up
			}
			if (pd.id + width < total) {
				if (!p[pd.id + width].selected	&& !p[pd.id + width].found)	addtoPath(pathDirection(down, pd.id + width));	//down
			}
			if (pd.id % width != 0) {
				if (!p[pd.id - 1].selected		&& !p[pd.id - 1].found)		addtoPath(pathDirection(left, pd.id - 1));		//left
			}
			if ((pd.id + 1) % width != 0) {
				if (!p[pd.id + 1].selected		&& !p[pd.id + 1].found)		addtoPath(pathDirection(right, pd.id + 1));		//right
			}
		}
	}
}
void Filler::printBounds()
{
	int x, y;
	x = leftmost % width;
	y = leftmost / width;
	printf("\nl: %i(%i, %i),", leftmost, x, y);

	x = topmost % width;
	y = topmost / width;
	printf(" u: %i(%i, %i),", topmost, x, y);

	x = rightmost % width;
	y = rightmost / width;
	printf(" r: %i(%i, %i),", rightmost, x, y);

	x = bottommost % width;
	y = bottommost / width;
	printf(" b: %i(%i, %i)\n", bottommost, x, y);
}
std::vector<pathDirection>& Filler::getPath()
{
	return path;
}
void Filler::clearPath()
{
	for (int i = 0; i < path.size(); i++) 
	{
		if (p[path[i].id].value <= uint8_t(255)) {
			p[path[i].id].selected = false;
		}
		else {
			p[path[i].id].found = true;
			foundBuffer.push_back(path[i].id);
		}
	}
	
	path.clear();
	pathSize = 0;
}
void Filler::clearFoundBuffer()
{
	for (int i = 0; i < foundBuffer.size(); i++) {
		p[foundBuffer[i]].found = false;
		p[foundBuffer[i]].selected = false;
	}
	foundBuffer.clear();
}