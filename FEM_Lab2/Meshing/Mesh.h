#pragma once
#include <vector>
#include <iostream>
#include <fstream>



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
private:

	void logout_points(string path)
	{
		ofstream fout(path);
		fout.precision(15);
		for (auto point : points)
			fout << scientific << point.first << " " << point.second << endl;
		fout.close();
	}

	void logout_elems(string path)
	{
		ofstream fout(path);
		for (auto elem : elems)
			fout << elem.x0 << " " << elem.x1 << " " << elem.y0 << " " << elem.y1 << endl;
		fout.close();
	}


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

	~Mesh()
	{
		cout << "Mesh deleted" << endl;
	}

	void logout_data(string points_path, string elems_path)
	{
		logout_points(points_path);
		logout_elems(elems_path);
	}
};