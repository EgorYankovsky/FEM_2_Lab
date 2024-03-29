#pragma once
#include <vector>
#include "../Meshing/Mesh.h"
#include "LocalMatrix.h"
//#include <bits/stdc++.h> 
#include <list>
#include <cassert>
#include <algorithm>


using namespace std;

class GlobalMatrix
{
private:

    bool is_unique(std::vector<int> elem, int pnt)
    {
        for (auto value : elem)
            if (value == pnt)
                return false;
        return true;
    }

    double get_value_al(int i, int j)
    {
        for (int ii = 0; ii < _ig[i + 1] - _ig[i]; ii++)
            if (_jg[_ig[i] + ii] == j)
                return _al[_ig[i] + ii];
        return 0.0;
    }

    double get_value_au(int i, int j)
    {
        for (int ii = 0; ii < _ig[i + 1] - _ig[i]; ii++)
            if (_jg[_ig[i] + ii] == j)
                return _au[_ig[i] + ii];
        return 0.0;
    }

public:

    vector <double> d;

    vector <double> gl;

    vector <double> gu;

    vector<int> _ig;

    vector<int> _jg;

    vector<double> _diag;

    vector<double> _al;

    vector<double> _au;

    GlobalMatrix()
    {
        std::cout << "empty matrix created" << std::endl;
    }

    GlobalMatrix(vector<int>_ig, vector<int>_jg, vector<double> _diag, vector<double> _al, vector<double> _au) 
    {
        this->_ig = _ig;
        this->_jg = _jg;
        this->_diag = _diag;
        this->_al = _al;
        this->_au = _au;
    }

    void consider_boundary_condition_at(int index)
    {
        _diag[index] = 1.0;
        for (int j = _ig[index]; j < _ig[index + 1]; j++)
            _al[j] = 0;
        for (int j = 0; j < _jg.size(); j++)
            if (_jg[j] == index)
                _au[j] = 0;
    }

    double get_value(int i, int j)
    {
        if (i > size() || j > size())
        {
            std::cerr << "Index out of matrix" << std::endl;
            exit(-1);
        }
        if (i - j == 0)
            return _diag[i];
        else if (i - j < 0)
            return get_value_au(j, i);
        else if (i - j > 0)
            return get_value_al(i, j);
    }

    inline int size() { return _diag.size(); }

    void generate_portrait(vector<vector<int>> elems)
    {
        int points_amount = elems.back()[3] + 1;
        _ig.resize(points_amount + 1);
        _diag.resize(points_amount);

        // Рабочий массив.
        vector<vector<int>> arr;

        // ! Дерьмодристный момент - слабо очень слабо (.
        for (int i = 0; i < points_amount; i++)
            arr.push_back(vector<int>());

        for (auto elem : elems)
        {
            for (auto point : elem)
            {
                for (auto pnt : elem)
                {
                    if (pnt < point && is_unique(arr[point], pnt))
                    {
                        arr[point].push_back(pnt);
                        if (arr[point].size() != 1)
                            sort(arr[point].begin(), arr[point].end());
                    }
                }
            }
        }

        _ig[0] = 0;
        for (int i(0); i < points_amount; i++)
        {
            _ig[i + 1] = _ig[i] + arr[i].size();
            for (int j(0); j < arr[i].size(); j++)
                _jg.push_back(arr[i][j]);
        }
        _al.resize(_jg.size());
        _au.resize(_jg.size());
    }

    void add(LocalMatrix lm, vector<int> elem)
    {
        int ii = 0;
        for (auto i : elem)
        {
            int jj = 0;
            for (auto j : elem)
            {
                int ind = 0;
                double val = 0.0;
                if (i == j)
                {
                    val = lm.get_value(ii, jj);
                    _diag[i] += lm.get_value(ii, jj);
                }
                else if (i < j)
                {
                    ind = _ig[j];
                    for (; ind <= _ig[j + 1] - 1; ind++)
                        if (_jg[ind] == i) break;
                    val = lm.get_value(ii, jj);
                    _au[ind] += lm.get_value(ii, jj);
                }
                else if (i > j)
                {
                    ind = _ig[i];
                    for (; ind <= _ig[i + 1] - 1; ind++)
                        if (_jg[ind] == j) break;
                    val = lm.get_value(ii, jj);
                    _al[ind] += lm.get_value(ii, jj);
                }
                jj++;
            }
            ii++;
        }
    }

    inline int get_elems_amount() { return _al.size(); }

};