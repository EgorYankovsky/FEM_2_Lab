#pragma once

#include <vector>
#include "./MathObjects/GlobalMatrix.h"
#include "./MathObjects/GlobalVector.h"
#include "./Meshing/Mesh.h"

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

int nodes_x_y_amount = nodes_x_amount * nodes_y_amount;

pair<int, int> scale;

void consider_boundary_conditions(GlobalMatrix & gm, GlobalVector & gv, int points_amount)
{
    int divider_x = nodes_x.size();
    int step_x = nodes_x.size();
    // По оси X.
    for (int i = 0; i < points_amount; i += step_x)
    {
        gv.set_value(i, 0.0);
        gv.set_value(i + step_x - 1, 0.0);
        gm.consider_boundary_condition_at(i);
        gm.consider_boundary_condition_at(i + step_x - 1);
    }

    // По оси Y.
    for (int i = nodes_x.size() * (nodes_y.size() - 1) + 1; i < points_amount; i++)
    {
        gv.set_value(i, 0.0);
        gm.consider_boundary_condition_at(i);
    }
}