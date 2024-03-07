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

    double _x0;

    double _x1;

    double _y0;

    double _y1;

    double _hx;

    double _hy;

    double _elems[4];

    double _M[2][2] {{2.0, 1.0}, 
                     {1.0, 2.0}};

public:

    LocalVector(double x0, double x1, double y0, double y1)
    {
        _x0 = x0;
        _x1 = x1;
        _y0 = y0;
        _y1 = y1;
        _hx = _x1 - _x0;
        _hy = _y1 - _y0;
    }

    double operator[](int i)
    {
        if (i > 3)
        {
            cerr << "Out of local vector range";
            exit(-1);
        }

        switch (i)
        {
        case 0:
            return _hx * _hy / 36.0 * (_M[0][0] * _M[0][0] * F(_x0, _y0) + 
                                       _M[0][1] * _M[0][0] * F(_x1, _y0) +
                                       _M[0][0] * _M[0][1] * F(_x0, _y1) +
                                       _M[0][1] * _M[0][1] * F(_x1, _y1));
        case 1:
            return _hx * _hy / 36.0 * (_M[1][0] * _M[0][0] * F(_x0, _y0) + 
                                       _M[1][1] * _M[0][0] * F(_x1, _y0) +
                                       _M[1][0] * _M[0][1] * F(_x0, _y1) +
                                       _M[1][1] * _M[0][1] * F(_x1, _y1));
        case 2:
            return _hx * _hy / 36.0 * (_M[0][0] * _M[1][0] * F(_x0, _y0) + 
                                       _M[0][1] * _M[1][0] * F(_x1, _y0) +
                                       _M[0][0] * _M[1][1] * F(_x0, _y1) +
                                       _M[0][1] * _M[1][1] * F(_x1, _y1));
        case 3:
            return _hx * _hy / 36.0 * (_M[1][0] * _M[1][0] * F(_x0, _y0) + 
                                       _M[1][1] * _M[1][0] * F(_x1, _y0) +
                                       _M[1][0] * _M[1][1] * F(_x0, _y1) +
                                       _M[1][1] * _M[1][1] * F(_x1, _y1));
        }
        return 0.0;
    }
};