#include <iostream>
#include "./Meshing/Reader.h"
#include "./Meshing/MeshGenerator.h"

#include "./MathObjects/LocalMatrix.h"
#include "./MathObjects/GlobalMatrix.h"
#include "./MathObjects/GlobalVector.h"
#include "./MathObjects/LocalVector.h"
#include "LU&LOS.h"

#include <algorithm>

const string mesh_data = "InputMeshData.txt";
const string subtotals_points = "Subtotals/Points.txt";
const string subtotals_elems = "Subtotals/Elems.txt";

void local_matrix_creation_test()
{
	LocalMatrix lm(1.0, 2.0, 1.0, 2.0, 1.0);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << lm.get_value(i, j) << " ";
		cout << endl;
	}
}

void global_matrix_portrait_creation_test()
{
	vector<vector<int>> elems = {{0, 1, 5, 6}, 
								 {1, 2, 6, 7},
								 {2, 3, 7, 8},
								 {3, 4, 8, 9},
								 
								 {5, 6, 10, 11},
								 {6, 7, 11, 12},
								 {7, 8, 12, 13},
								 {8, 9, 13, 14},
								 
								 {10, 11, 15, 16},
								 {11, 12, 16, 17},
								 {12, 13, 17, 18},
								 {13, 14, 18, 19},
								 
								 {15, 16, 20, 21},
								 {16, 17, 21, 22},
								 {17, 18, 22, 23},
								 {18, 19, 23, 24},};	
	
	GlobalMatrix gm;
	gm.generate_portrait(elems);
}

void local_vector_generation_test()
{
	LocalVector lv(1.0, 2.0, 1.0, 3.0);
	for (int i = 0; i < 4; i++)
		cout << lv[i] << endl;

}

void global_vector_generation_test()
{
	vector<vector<int>> elems = {{0, 1, 5, 6}, 
								 {1, 2, 6, 7},
								 {2, 3, 7, 8},
								 {3, 4, 8, 9},
							 	
								 {5, 6, 10, 11},
								 {6, 7, 11, 12},
								 {7, 8, 12, 13},
								 {8, 9, 13, 14},
								
								 {10, 11, 15, 16},
								 {11, 12, 16, 17},
								 {12, 13, 17, 18},
								 {13, 14, 18, 19},
								
	 							 {15, 16, 20, 21},
	 							 {16, 17, 21, 22},
	 							 {17, 18, 22, 23},
	 							 {18, 19, 23, 24},};	
	
	vector<double> _my_nodes_x {0.0, 1.0, 2.0, 3.0, 4.0};
	vector<double> _my_nodes_y {0.0, 1.0, 2.0, 3.0, 4.0};


	vector<pair<double, double>> points;
	for (auto y : _my_nodes_y)
		for (auto x : _my_nodes_x)
			points.push_back(pair<double, double> (x, y));


	GlobalVector gv(elems.back()[3] + 1);

	for (auto elem : elems)
	{
		LocalVector lv(points[elem[0]].first, points[elem[1]].first,
					points[elem[0]].second, points[elem[2]].second);
		gv.add(lv, elem);
	}
}

void global_matrix_generation_test()
{
	vector<vector<int>> elems = {{0, 1, 5, 6}, 
								 {1, 2, 6, 7},
								 {2, 3, 7, 8},
								 {3, 4, 8, 9},
								 
								 {5, 6, 10, 11},
								 {6, 7, 11, 12},
								 {7, 8, 12, 13},
								 {8, 9, 13, 14},
								 
								 {10, 11, 15, 16},
								 {11, 12, 16, 17},
								 {12, 13, 17, 18},
								 {13, 14, 18, 19},
								 
								 {15, 16, 20, 21},
								 {16, 17, 21, 22},
								 {17, 18, 22, 23},
								 {18, 19, 23, 24},};	
	
	vector<double> _my_nodes_x {0.0, 1.0, 2.0, 3.0, 4.0};
	vector<double> _my_nodes_y {0.0, 1.0, 2.0, 3.0, 4.0};


	vector<pair<double, double>> points;
	for (auto y : _my_nodes_y)
		for (auto x : _my_nodes_x)
			points.push_back(pair<double, double> (x, y));

	GlobalMatrix gm;
	gm.generate_portrait(elems);

	for (auto elem : elems)
	{
		LocalMatrix lm(points[elem[0]].first, points[elem[1]].first,
					   points[elem[0]].second, points[elem[2]].second, 1.0);
		gm.add(lm, elem);		
	}

	ofstream fout("matrix.txt");
	for (int i(0); i < points.size(); i++)
	{
		//setprecision(4);
		for (int j(0); j < points.size(); j++)
		{
			fout << scientific << gm.get_value(i, j) << " ";
		}
		fout << endl;
	}

}

void consider_boundary_conditions_test()
{
	vector<vector<int>> elems = {{0, 1, 5, 6}, 
								 {1, 2, 6, 7},
								 {2, 3, 7, 8},
								 {3, 4, 8, 9},
								 
								 {5, 6, 10, 11},
								 {6, 7, 11, 12},
								 {7, 8, 12, 13},
								 {8, 9, 13, 14},
								 
								 {10, 11, 15, 16},
								 {11, 12, 16, 17},
								 {12, 13, 17, 18},
								 {13, 14, 18, 19},
								 
								 {15, 16, 20, 21},
								 {16, 17, 21, 22},
								 {17, 18, 22, 23},
								 {18, 19, 23, 24},};	
	
	vector<double> _my_nodes_x {0.0, 1.0, 2.0, 3.0, 4.0};
	vector<double> _my_nodes_y {0.0, 1.0, 2.0, 3.0, 4.0};

	nodes_x = _my_nodes_x;
	nodes_y = _my_nodes_y;

	vector<pair<double, double>> points;
	for (auto y : _my_nodes_y)
		for (auto x : _my_nodes_x)
			points.push_back(pair<double, double> (x, y));

	GlobalMatrix gm;
	gm.generate_portrait(elems);

	for (auto elem : elems)
	{
		LocalMatrix lm(points[elem[0]].first, points[elem[1]].first,
					   points[elem[0]].second, points[elem[2]].second, 1.0);
		gm.add(lm, elem);		
	}

	GlobalVector gv(elems.back()[3] + 1);
	for (auto elem : elems)
	{
		LocalVector lv(points[elem[0]].first, points[elem[1]].first,
					points[elem[0]].second, points[elem[2]].second);
		gv.add(lv, elem);
	}

	consider_boundary_conditions(gm, gv, elems.back()[3] + 1);

	ofstream fout("matrix.txt");
	for (int i(0); i < points.size(); i++)
	{
		fout.precision(1);
		for (int j(0); j < points.size(); j++)
		{
			if (gm.get_value(i, j) != 0.0)
				fout << 1 << " ";
			else 
				fout << 0 << " ";
			//fout << scientific << gm.get_value(i, j) << " ";
		}
		fout << endl;
	}
	fout.close();

	fout.open("vector.txt");
	for (int i(0); i < gv.size(); i++)
		fout << gv.get_value(i) << endl;
}

void LU_test()
{
	vector<int> _ig = { 0, 0, 0, 1, 3, 5, 8, 11, 14, 18, 26 };

	vector<int> _jg = { 1, 1, 2, 1, 3, 1, 3, 4, 2, 3, 5, 2, 3, 6, 2, 3, 5, 7, 0, 1, 2, 3, 4, 5, 6, 7};

	vector<double> _diag = { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };

	vector<double> _al = { 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 1, 3, 3, 3, 3, 3, 3, 3 };

	vector<double> _au = { 3, 4, 4, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 1, 3, 3, 3, 3, 3, 3, 3 };
	
	GlobalMatrix glk(_ig, _jg, _diag, _al, _au);

	GlobalVector glv(10);
	glv._values = vector<double> {10, 94, 98, 155, 104, 136, 123, 109, 127, 70};

	GlobalVector glresult(10);
	nodes_x_y_amount = 10;

	LU(glk);
	//LOS(glk, glresult, glv);
	//for (auto value : glresult._values)
	//	cout << value << endl;
}

int main()
{
	LU_test();
	read_data(mesh_data);
	Mesh mesh;
	generate_mesh(mesh);
	generate_array_of_points(mesh);
	generate_array_of_elems(mesh);
	mesh.logout_data(subtotals_points, subtotals_elems);
	return 0;
}
