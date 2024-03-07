#pragma once
#include "Mesh.h"
#include "../GeneralData.h"
#include <iostream>
#include <math.h>



void GenerateMesh(Mesh & mesh)
{
	// ���������� �� ��� X.
	for (int i(0); i < nodes_x.size() - 1; i++)
	{
		double x0(nodes_x[i]);
		double x1(nodes_x[i + 1]);

		mesh.nodes_x.push_back(x0);
		double h0(step0_x[i]);
		int direct = direction_x[i];
		if (direction_x[i] == -1)
		{
			double x_curr = x0 + h0;
			int j(1);
			while (x_curr < x1)
			{
				x_curr += h0 * pow(coef_x[i], j);
				j++;
			}
			h0 *= pow(coef_x[i], --j);
		}
		double x_curr = x0 + h0;
		int j(1);
		while (x_curr < x1)
		{
			mesh.nodes_x.push_back(x_curr);
			if (direction_x[i] == -1)
			{
				h0 /= coef_x[i];
				x_curr += h0;

			}
			else
				x_curr += h0 * pow(coef_x[i], j);
			j++;
		}
	}
	mesh.nodes_x.push_back(nodes_x.back());


	// ���������� �� ��� Y.
	for (int i(0); i < nodes_y.size() - 1; i++)
	{
		double y0(nodes_y[i]);
		double y1(nodes_y[i + 1]);

		mesh.nodes_y.push_back(y0);
		double h0(step0_y[i]);
		if (direction_y[i] == -1)
		{
			double y_curr = y0 + h0;
			int j(1);
			while (y_curr < y1)
			{
				y_curr += h0 * pow(coef_y[i], j);
				j++;
			}
			h0 *= pow(coef_y[i], --j);
		}
		int direct = direction_y[i];

		double y_curr = y0 + h0;
		int j(1);
		while (y_curr < y1)
		{
			mesh.nodes_y.push_back(y_curr);
			if (direction_y[i] == -1)
			{
				h0 /= coef_y[i];
				y_curr += h0;

			}
			else
				y_curr += h0 * pow(coef_y[i], j);
			j++;
		}
	}
	mesh.nodes_y.push_back(nodes_x.back());
	cout << "Mesh generated" << endl;
}

void generateArrayOfPoints(Mesh& mesh)
{
	for (auto& y : mesh.nodes_y)
		for (auto& x : mesh.nodes_x)
			mesh.points.push_back(pair<double, double>{ x, y });
	cout << "Array of points created" << endl;
}

void generateArrayOfElems(Mesh& mesh)
{
	for (int i(0); i < mesh.nodes_y.size() - 1; i++)
		for (int j(0); j < mesh.nodes_x.size() - 1; j++)
			mesh.elems.push_back(Elem(i * mesh.nodes_x.size() + j,
									 (i * mesh.nodes_x.size() + j) + 1, 
									 (i + 1) * mesh.nodes_x.size() + j, 
									 (i + 1) * mesh.nodes_x.size() + j + 1));
	cout << "Array of elems created" << endl;
}

