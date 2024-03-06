#pragma once
#include<string>
#include<vector>
#include<fstream>
#include "../GeneralData.h"

using namespace std;

void ReadData(string file)
{
	ifstream fin(file);
	fin >> elems_amount;

	// ��������� ������� ���������, ��, ��������� ���� � ����� �������.
	list_of_elems.resize(elems_amount);
	list_of_mu0.resize(elems_amount);
	list_of_J.resize(elems_amount);
	material_number.resize(elems_amount);

	for (int i(0); i < elems_amount; i++)
	{
		list_of_elems[i].resize(4);
		fin >> list_of_elems[i][0] >> list_of_elems[i][1] >> list_of_elems[i][2] >> list_of_elems[i][3] >> list_of_mu0[i] >> list_of_J[i] >> material_number[i];
	}

	// ��������� ��������� �� ��� x.
	double x0;
	fin >> x0 >> nodes_x_amount;
	nodes_x_amount++;
	nodes_x.resize(nodes_x_amount);
	step0_x.resize(nodes_x_amount - 1);
	coef_x.resize(nodes_x_amount - 1);
	direction_x.resize(nodes_x_amount - 1);
	nodes_x[0] = x0;
	for (int i(1); i < nodes_x.size(); i++)
		fin >> nodes_x[i];
	for (int i(0); i < nodes_x_amount - 1; i++)
		fin >> step0_x[i];
	for (int i(0); i < nodes_x_amount - 1; i++)
		fin >> coef_x[i];
	for (int i(0); i < nodes_x_amount - 1; i++)
		fin >> direction_x[i];


	// ��������� ��������� �� ��� x.
	double y0;
	fin >> y0 >> nodes_y_amount;
	nodes_y_amount++;
	nodes_y.resize(nodes_y_amount);
	step0_y.resize(nodes_y_amount - 1);
	coef_y.resize(nodes_y_amount - 1);
	direction_y.resize(nodes_y_amount - 1);
	nodes_y[0] = y0;
	for (int i(1); i < nodes_y.size(); i++)
		fin >> nodes_y[i];
	for (int i(0); i < nodes_y_amount - 1; i++)
		fin >> step0_y[i];
	for (int i(0); i < nodes_y_amount - 1; i++)
		fin >> coef_y[i];
	for (int i(0); i < nodes_y_amount - 1; i++)
		fin >> direction_y[i];
}