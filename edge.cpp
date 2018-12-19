#include "edge.h"

Edge::Edge()
{
	std::cout << edge_warn << "edge initialized with no pixels\n";
}
Edge::Edge(const int w, const int t)
	: sel(NULL), per(NULL), edg(NULL), numEdges(0), tolerance(0), perimSize(0), fieldSet(false), width(w), total(t)
{}
void Edge::detect(std::vector<int>& selection, node* buff)
{
	/*
	node * temp = NULL;
	std::vector<int> balance;
	for (int i = 0; i < size; i++)
		Tree::insert(temp, selection[i]);

	Tree::getInOrder(temp, balance);
	
	Tree::deleteTree(temp);
	
	Tree::buildTree(balance, sel);
	*/

	sel = buff;

	stack.push_back(selection[0]);
	perimeter.push_back(selection[0]);
	Tree::insert(per, selection[0]);
	perimSize++;
	numEdges++;

	iterateEdges();

	//Tree::deleteTree(sel);
	Tree::deleteTree(per);

	sel = NULL;

	//std::cout << numEdges << "\n";
}
void Edge::iterateEdges()
{
	while (!stack.empty())
	{
		int id = stack.back();
		stack.pop_back();
		getOctan(id);
	}
}
void Edge::getOctan(const int id)
{
	octan oct;

	if ((id - width) > 0) {
		oct.tl = Tree::findNode(sel, id - width - 1);
		oct.t  = Tree::findNode(sel, id - width);
		oct.tr = Tree::findNode(sel, id - width + 1);
	}

	if (id % width != 0)
		oct.l  = Tree::findNode(sel, id - 1);
	if ((id + 1) % width != 0)
		oct.r  = Tree::findNode(sel, id + 1);

	if ((id + width) < total) {
		oct.bl = Tree::findNode(sel, id + width - 1);
		oct.b  = Tree::findNode(sel, id + width);
		oct.br = Tree::findNode(sel, id + width + 1);
	}

	if ((id - width) > 0) { //read: "check if top left is an edge"
		check(oct.tl, oct.t, oct.l, tl);
		check(oct.t, oct.tl, oct.tr, t);
		check(oct.tr, oct.t, oct.r, tr);
	}

	if (id % width != 0)
		check(oct.l, oct.tl, oct.bl, l);
	if ((id + 1) % width != 0)
		check(oct.r, oct.tr, oct.br, r);

	if ((id + width) < total) {
		check(oct.bl, oct.l, oct.b, bl);
		check(oct.b, oct.bl, oct.br, b);
		check(oct.br, oct.b, oct.r, br);
	}
}
void Edge::check(const int p, const int p1, const int p2, neighbor n)
{
	if ((p + 1) && !((p1 + 1) && (p2 + 1))) 
	{ 
		if (Tree::insert(per, p)) 
		{
			stack.push_back(p);
			perimeter.push_back(p);
			perimSize++;

			if (!fieldSet) {
				setField(n);
				numEdges++;
			}
			else
			{
				tolerance += field[n];
				
				if (tolerance < -4 || tolerance > 4) {
					tolerance = 0;
					numEdges++;
					setField(n);
				}
			}
		}
	}
}
void Edge::setField(neighbor n)
{
	if(n == t || n == b) {	//vertical
		field[tl] = -1;
		field[l]  = -2;
		field[bl] = -1;

		field[t] = 0;
		field[b] = 0;

		field[tr] = 1;
		field[r]  = 2;
		field[br] = 1;

		fieldSet = true;
	}
	else if (n == l || n == r) { //horizontal
		field[tl] = -1;
		field[t]  = -2;
		field[tr] = -1;

		field[l] = 0;
		field[r] = 0;

		field[bl] = 1;
		field[b]  = 2;
		field[br] = 1;

		fieldSet = true;
	}
	else if (n == tl || n == br) { //leftslant
		field[t]  = -1;
		field[tr] = -2;
		field[r]  = -1;

		field[tl] = 0;
		field[br] = 0;

		field[l]  = 1;
		field[bl] = 2;
		field[b]  = 1;

		fieldSet = true;
	}
	else { //rightslant
		field[l]  = -1;
		field[tl] = -2;
		field[t]  = -1;

		field[tr] = 0;
		field[bl] = 0;

		field[b]  = 1;
		field[br] = 2;
		field[r]  = 1;

		fieldSet = true;
	}
}
std::vector<int>& Edge::getPerimiter()
{
	return perimeter;
}
int Edge::getSizeofPerimeter()
{
	return perimSize;
}
int Edge::getEdges()
{
	return numEdges;
}