#include "selection.h"

Selection::Selection()
{
	std::cout << selection_err << "initialized without pixels\n";
}
Selection::Selection(pixel* p, const int w, const int t)
	: pixels(p), width(w), total(t), bufferSize(0)
{}
bool Selection::get(const int i)
{
	if (checkPixel(pixels[i], VALUE_THRESHOLD))
	{
		iterate(VALUE_THRESHOLD);

		if (bufferSize > 0 && bufferSize < 2700)
		{
			fillPixels();
			findEdges();

			return true;
		}
	}

	return false;
}
void Selection::iterate(const int value)
{
	for (int i = 0; i < bufferSize; i++)
		nextPixel(buffer[i], value);
}
void Selection::nextPixel(const int i, const int value)
{
	if ((i - width) > 0) {
		checkPixel(pixels[i - width - 1], value);	//top left
		checkPixel(pixels[i - width], value);		//top center
		checkPixel(pixels[i - width + 1], value);	//top right
	}

	if (i % width != 0)
		checkPixel(pixels[i - 1], value);	//center left
	if (i % (width + 1) != 0)
		checkPixel(pixels[i + 1], value);	//center right

	if ((i + width) < total) {
		checkPixel(pixels[i + width - 1], value);	//bottom left
		checkPixel(pixels[i + width], value);		//bottom center
		checkPixel(pixels[i + width + 1], value);	//bottom right
	}
}
bool Selection::checkPixel(pixel& p, const int value)
{
	if (p.value < value)
	{
		if (!p.selected) {
			buffer.push_back(p.id);
			p.selected = true;
			bufferSize++;
			Tree::insert(buff, p.id);
			return true;
		}
	}
	return false;
}
void Selection::fillPixels()
{
	Filler fill(pixels, width, total);

	for (int i = 0; i < bufferSize; i++)
		fill.getBounds(buffer[i]);

	int count = 0;

	for (int i = 0; i < bufferSize; i++)
	{
		if (buffer[i] + width < total && !pixels[buffer[i] + width].selected  &&  pixels[buffer[i] + width].value >= VALUE_THRESHOLD)
		{
			fill.start(buffer[i] + width);

			std::vector<pathDirection> whitePixels = fill.getPath();

			if (!whitePixels.empty())
			{
				for (int i = 0; i < whitePixels.size(); i++) {
					buffer.push_back(whitePixels[i].id);
					Tree::insert(buff, whitePixels[i].id);
					count++;
				}
			}
		}
	}

	fill.clearFoundBuffer();

	bufferSize += count;
}
void Selection::findEdges()
{
	Edge e(width, total);

	e.detect(buffer, buff);

	perimeter = e.getPerimiter();
	numEdges = e.getEdges();
}
std::vector<int>& Selection::getBuffer()
{
	return buffer;
}
std::vector<int>& Selection::getPerimeter()
{
	return perimeter;
}
int Selection::getEdges()
{
	return numEdges;
}
void Selection::clearBuffer()
{
	buffer.clear();
	bufferSize = 0;
	Tree::deleteTree(buff);
	buff = NULL;
}