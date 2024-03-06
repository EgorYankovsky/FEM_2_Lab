#include <iostream>
#include "./Meshing/Reader.h"
#include "./Meshing/MeshGenerator.h"
#include "./MathObjects/LocalMatrix.h"

const string mesh_data = "InputMeshData.txt";
const string subtotals_points = "Subtotals/Points.txt";
const string subtotals_elems = "Subtotals/Elems.txt";

int main()
{
	ReadData(mesh_data);
	Mesh mesh;
	GenerateMesh(mesh);
	generateArrayOfPoints(mesh);
	generateArrayOfElems(mesh);
	mesh.logout_data(subtotals_points, subtotals_elems);

	// For test. Delete after.

	LocalMatrix lm(1.0, 2.0, 1.0, 2.0, 1.0);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << lm.get_value(i, j) << " ";
		cout << endl;
	}
	return 0;
}
