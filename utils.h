#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
using namespace std;

vector<complex<double>> long_to_complex(vector<long long> v);
vector<long long> complex_to_long(vector<complex<double>> v);
vector<complex<double>> random_rounding(vector<complex<double>> v);
vector<complex<double>> FFT(vector<long long> c, int T);
vector<complex<double>> FFT(vector<complex<double>>, int);
// vector<complex<double>> linear_system_solve(const vector<vector<complex<double>>> & A, const vector<complex<double>> & b);
complex<double> apply(const vector<complex<double>> & p, complex<double> root);

#endif
