#pragma once
#include <vector>
#include "LocalMatrix.h"

class GlobalMatrix
{
private:

    std::vector<int> _ig;

    std::vector<int> _jg;

    std::vector<double> _diag;

    std::vector<double> _al;

    std::vector<double> _au;

public:

    double GetValue(int i, int j);

    inline int Size() { return _diag.size(); }

    void add(LocalMatrix lm)
    {
        /* Добавляем локальную матрицу */
    }

};