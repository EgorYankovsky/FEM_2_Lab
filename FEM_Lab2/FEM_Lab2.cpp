#include <iostream>
#include "Reader.h"
#include "MeshGenerator.h"

const string mesh_data = "InputMeshData.txt";

int main()
{
	ReadData(mesh_data);
	Mesh mesh;
	GenerateMesh(mesh);
	generateArrayOfPoints(mesh);
	generateArrayOfElems(mesh);
	return 0;
}
