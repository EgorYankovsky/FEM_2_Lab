#pragma once
#include <vector>
#include <iostream>
#include "LocalVector.h"

class  GlobalVector
{
private:

    std::vector<double> _values;

public:

    inline int size() { return _values.size(); }

    GlobalVector(/* args */);

    GlobalVector(int size)
    {
        _values.resize(size);
    }

    void add(LocalVector lv, std::vector<int> pointers)
    {
        for (int i(0); i < 4; i++)
            _values[pointers[i]] += lv[i];
    }

    ~GlobalVector()
    {
        std::cout << "Vector deleted" << std::endl;
    }
};