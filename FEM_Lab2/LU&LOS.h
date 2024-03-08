#pragma once
#include <vector>
#include "./MathObjects/GlobalMatrix.h"
#include "./MathObjects/GlobalVector.h"
#include "GeneralData.h"

using namespace std;

void LU(GlobalMatrix gm, GlobalVector gv)
{
    gm.d.resize(gm.size());
    gm.gl.resize(gm.get_elems_amount());
    gm.gu.resize(gm.get_elems_amount());
    int i0, i1, j, kk, ll, ll_1, lll, kkk;
    double sd, sl, su;
    for (int i = 0; i < nodes_x_y_amount; i++)
    {
        i0 = gm._ig[i] - 1;
        i1 = gm._ig[i + 1] - 1;
        sd = 0;
        for (int jj = i0; jj < i1; jj++)
        {
            j = gm._jg[jj] - 1;
            kk = i0;
            ll = gm._ig[j] - 1;
            ll_1 = gm._ig[j + 1] - 1;
            sl = 0;
            su = 0;
            while (ll < ll_1 && kk < jj)
            {
                lll = gm._jg[ll] - 1;
                kkk = gm._jg[kk] - 1;

                if (lll == kkk)
                {
                    su += gm.gl[ll] * gm.gu[kk];
                    sl += gm.gu[ll] * gm.gl[kk];
                    kk++;
                    ll++;
                }
                else
                {
                    if (kkk < lll)
                        kk++;
                    else
                        ll++;
                }
            }
            gm.gl[jj] = (gm._al[jj] - sl);
            gm.gu[jj] = (gm._au[jj] - su) / gm.d[j];
            sd += gm.gu[jj] * gm.gl[jj];
        }
        gm.d[i] = gm._diag[i] - sd;
    }

    for (int i = 0; i < nodes_x_y_amount; i++)
        gv.set_value(i, 0);
}

void mult_A(GlobalVector & vect, GlobalVector & res, GlobalMatrix gm)
{
    int i0, i1, j;
    for (int i = 0; i < nodes_x_y_amount; i++)
    {
        i0 = gm._ig[i] - 1;
        i1 = gm._ig[i + 1] - 1;
        res.set_value(i, gm._diag[i] * vect.get_value(i));
        for (int k = i0; k < i1; k++)
        {
            j = gm._jg[k];
            res.add_value(i, gm._al[k] * vect.get_value(j - 1));
            res.add_value(j - 1, gm._au[k] * vect.get_value(i));
        }
    }
}

void Direct(GlobalVector & vec, GlobalVector & res, GlobalMatrix gm)
{
    for (int i = 0; i < nodes_x_y_amount; i++)
    {
        res.set_value(i, vec.get_value(i));
        double s = 0;
        int j;
        for (int k = gm._ig[i] - 1; k < gm._ig[i + 1] - 1; k++)
        {
            j = gm._jg[k] - 1;
            s += res.get_value(j) * gm.gl[k];
        }
        res.down_value(i, s);
        res.reduce_value(i, gm.d[i]);
    }
}

void Reverse(GlobalVector & vec, GlobalVector & res, GlobalMatrix gm)
{
    for (int i = 0; i < nodes_x_y_amount; i++)
        res.set_value(i, vec.get_value(i));
    for (int i = nodes_x_y_amount - 1; i >= 0; i--)
    {
        for (int k = gm._ig[i + 1] - 2; k >= gm._ig[i] - 1; k--)
        {
            int j = gm._jg[k] - 1;
            res.down_value(j, res.get_value(i) * gm.gu[k]);
        }
    }
}

double norm_vector(int n, GlobalVector & vec)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += vec.get_value(i) * vec.get_value(i);
    return sqrt(sum);
}

double scal_prod(GlobalVector & a, GlobalVector & b, int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += a.get_value(i) * b.get_value(i);
    return sum;
}

void mult_coef(GlobalVector & vec, double k, GlobalVector & res, int n)
{
    for (int i = 0; i < n; i++)
        res.set_value(i, k * vec.get_value(i));
}

void sum_vector(GlobalVector & a, GlobalVector & b, GlobalVector & res, int n)
{
    for (int i = 0; i < n; i++)
        res.set_value(i, a.get_value(i) + b.get_value(i));
}


void LOS(GlobalMatrix gm, GlobalVector gv, GlobalVector gvr)
{
    double eps = 1e-15;
    int max_iter = 10000;
    vector<double> L;
    GlobalVector z (nodes_x_y_amount), r (nodes_x_y_amount), p (nodes_x_y_amount), res(nodes_x_y_amount), LAUr(nodes_x_y_amount);
    L.resize(nodes_x_y_amount);
    double a, b, norm;
    int k;
    mult_A(gv, res, gm);
    for (int i = 0; i < nodes_x_y_amount; i++)
        r.set_value(i, gvr.get_value(i) - res.get_value(i));
    Direct(r, r, gm);
    Reverse(r, z, gm);
    mult_A(z, res, gm);
    Direct(res, p, gm);
    double normV = norm_vector(nodes_x_y_amount, gvr);
    for (k = 0; (norm_vector(nodes_x_y_amount, r) / normV) > eps && k < max_iter; k++)
    {
        norm = scal_prod(p, p, nodes_x_y_amount);
        a = scal_prod(p, r, nodes_x_y_amount) / norm;
        mult_coef(z, a, res, nodes_x_y_amount);
        sum_vector(gv, res, gv, nodes_x_y_amount);
        mult_coef(p, -a, res, nodes_x_y_amount);
        sum_vector(r, res, r, nodes_x_y_amount);
        Reverse(r, res, gm);//res=U_-1*r
        mult_A(res, LAUr, gm);
        Direct(LAUr, LAUr, gm);
        b = -scal_prod(p, LAUr, nodes_x_y_amount) / norm;
        mult_coef(z, b, z, nodes_x_y_amount);
        sum_vector(res, z, z, nodes_x_y_amount);
        mult_coef(p, b, p, nodes_x_y_amount);
        sum_vector(p, LAUr, p, nodes_x_y_amount);
    }
}