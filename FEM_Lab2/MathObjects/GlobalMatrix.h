#pragma once
#include <vector>
#include "../Meshing/Mesh.h"
#include "LocalMatrix.h"
#include <list>

using namespace std;

class GlobalMatrix
{
private:

    vector<int> _ig;

    vector<int> _jg;

    vector<double> _diag;

    vector<double> _al;

    vector<double> _au;

public:

    double GetValue(int i, int j);

    inline int Size() { return _diag.size(); }

    void Portrait(vector <Elem> elems)
    {
        //_jg = new();
        _ig.resize(elems.back().y1 + 1);
        _diag.resize(elems.back().y1);

        // Рабочий массив.
        vector<vector<int>> arr;

        // ! Дерьмодристный момент - слабо очень слабо (.
        for (int i = 0; i < elems.back().y1; i++)
            arr.push_back(vector<int>());

        for (auto elem : elems)
        {
            for (auto pnt : elems)
            {

            }
        }



        



        foreach(var _elem in _arrOfElms)
            foreach(var point in _elem)
            foreach(var pnt in _elem)
            if (pnt < point && Array.IndexOf(arr[point].ToArray(), pnt) == -1)
            {
                arr[point].Add(pnt);
                arr[point].Sort();
            }

        _ig[0] = 0;
        for (int i = 0; i < _arrOfPnt.Length; i++)
        {
            _ig[i + 1] = _ig[i] + arr[i].Count;
            _jg.AddRange(arr[i]);
        }
    }

    void add(LocalMatrix lm)
    {
        /* Добавляем локальную матрицу */
    }

};