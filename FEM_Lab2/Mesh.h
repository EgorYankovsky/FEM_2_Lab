#pragma once

#include<vector>
#include <iostream>

using namespace std;

struct Elem
{
public:
	int x0;
	int x1;
	int y0;
	int y1;

	Elem(int a, int b, int c, int d)
	{
		x0 = a;
		x1 = b;
		y0 = c;
		y1 = d;
	}
};

class Mesh
{
public:
	vector<double> nodes_x;

	vector<double> nodes_y;

	vector<pair<double, double>> points;

	vector<Elem> elems;


	Mesh(vector<double> nodes_x, vector<double> nodes_y)
	{
		this->nodes_x = nodes_x;
		this->nodes_y = nodes_y;
		cout << "Mesh with some data created" << endl;
	}

	Mesh()
	{
		cout << "Empty mesh created" << endl;
	}
};

