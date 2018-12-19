#include "tree.h"

bool Tree::insert(node*& n, const int i)
{
	if (n == NULL) {
		n = new node(i);
		return true;
	}
	
	node * r = n;

	while (n != NULL)
	{
		if (i < n->id) {
			if (n->left != NULL)
				n = n->left;
			else {
				n->left = new node(i);
				n = r;
				return true;
			}
		}
		else if (i > n->id) {
			if (n->right != NULL)
				n = n->right;
			else {
				n->right = new node(i);
				n = r;
				return true;
			}
		}
		else {
			break;
		}
	}
	
	n = r;
	return false;
}
int Tree::findNode(node*& n, int id)
{
	if (n == NULL) return -1;

	node * r = n;

	while (n != NULL)
	{
		if (id == n->id) {
			n = r;
			return id;
		}
		if (id < n->id) n = n->left;
		else if (id > n->id) n = n->right;
	}

	n = r;
	return -1;
}
void Tree::deleteTree(node*& n)
{
	if (n == NULL) return;

	std::vector<node*> leafs;

	leafs.push_back(n);

	while (!leafs.empty()) {
		node * s = leafs.back();

		leafs.pop_back();

		if (s->left != NULL)
			leafs.push_back(s->left);
		if (s->right != NULL)
			leafs.push_back(s->right);

		delete s;
	}
}
void Tree::buildTree(std::vector<int> &v, node*& r)
{
	std::vector<tup> stack;
	int m, s, e;
	
	m = (0 + v.size() - 1) / 2;

	Tree::insert(r, v[m]);
	stack.push_back(tup(m + 1, v.size()));
	stack.push_back(tup(0, m));

	while (!stack.empty())
	{
		s = stack.back().s;
		e = stack.back().e;
		stack.pop_back();

		if (s < e) {
			m = (s + e) / 2;
			Tree::insert(r, v[m]);

			stack.push_back(tup(m + 1, e));
			stack.push_back(tup(s, m));
		}

	}
}
void Tree::getInOrder(node*& n, std::vector<int> &v)
{
	node * r = n;
	std::vector<node*> s;

	while (n != NULL || !s.empty())
	{
		while (n != NULL) {
			s.push_back(n);
			n = n->left;
		}
		n = s.back();
		s.pop_back();
		v.push_back(n->id);
		n = n->right;
	}

	n = r;
}
/*
void Tree::print(node*& n)
{
	if (n == NULL) return;

	print(n->left);
	std::cout << n->id << " ";
	print(n->right);
}
int Tree::total(node*& n)
{
	if (n == NULL) return 0;

	int lt = total(n->left);
	int rt = total(n->right);

	return rt + lt + 1;
}
int tree::get(node * n, pixel& c)
{
	switch (c) {
	case 1: return height(n);
	case 2: return min(n);
	case 3: return max(n);
	case 4: return total(n);
	}

	return -1;
}
int tree::min(node* n)
{
	if (n->left != NULL) return min(n->left);
	return n->data[0];
}
int tree::max(node* n)
{
	if (n->right != NULL) return max(n->right);
	return n->data[0];
}
*/