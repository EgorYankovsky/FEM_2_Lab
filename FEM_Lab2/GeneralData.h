#pragma once

#include<vector>

using namespace std;

int elems_amount;
vector<vector<double>> list_of_elems;
vector<double> list_of_mu0;
vector<double> list_of_J;
vector<int> material_number;

vector<double> nodes_x;
int nodes_x_amount;
vector<double> step0_x;
vector<double> coef_x;
vector<int> direction_x;


vector<double> nodes_y;
int nodes_y_amount;
vector<double> step0_y;
vector<double> coef_y;
vector<int> direction_y;

pair<int, int> scale;