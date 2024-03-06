#pragma once
#include "../Functions.h"
#include <iostream>

using std::cerr;

/*
 * LocalMatrix.h потом немного переделаем под нашу задачу, а пока пусть будет в качестве тестовой фигни.
*/

class LocalVector
{
private:

    double _hx;

    double _hy;

    double _elems[4];

    double _M[2][2] {{2.0, 1.0}, 
                     {1.0, 2.0}};

public:

    LocalVector(double x0, double x1, double y0, double y1)
    {
        _hx = x1 - x0;
        _hy = y1 - y0;
    }

    LocalVector(double hx, double hy)
    {
        _hx = hx;
        _hy = hy;
    }
    double get_value(int i)
    {
        if (i > 3)
        {
            cerr << "Out of local vector range";
            exit(-1);
        }
        return 1.0;
    }
};