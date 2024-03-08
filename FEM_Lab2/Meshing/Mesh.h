#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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
			fout << elem[0] << " " << elem[1] << " " << elem[2] << " " << elem[3] << endl;
		fout.close();
	}

public:
	vector<double> nodes_x;

	vector<double> nodes_y;

	vector<pair<double, double>> points;

	vector<vector<int>> elems;

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