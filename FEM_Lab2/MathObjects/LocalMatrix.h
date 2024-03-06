#pragma once
#include <iostream>

using std::cerr;

class LocalMatrix
{
private:

    double _hx;

    double _hy;

    double _mu;

    double _G[2][2] = {{1.0, -1.0},
                       {-1.0, 1.0}};

    double _M[2][2] = {{2.0, 1.0},
                       {1.0, 2.0}};

public:
    LocalMatrix(double hx, double hy, double mu)
    {
        _hx = hx;
        _hy = hy;
        _mu = mu;
    }

    LocalMatrix(double x0, double x1, double y0, double y1, double mu)
    {
        _hx = x1 - x0;
        _hy = y1 - y0;    
        _mu = mu;
    }

    double get_value(int i, int j)
    {
        if (i > 3 || j > 3)
        {
            cerr << "Out of local matrix range";
            exit(-1);
        }
        return 1.0 / _mu * ((1.0 / _hx) * _G[i % 2][j % 2] * (_hy / 6.0) * _M[i / 2][j / 2] + (_hx / 6.0) * _M[i % 2][j % 2] * (1.0 / _hy) * _G[i / 2][j / 2]);    
    }
};