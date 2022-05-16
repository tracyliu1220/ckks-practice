#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H

#include <bits/stdc++.h>
using namespace std;

vector<long long> polynomial_neg(vector<long long> a, long long mod);
vector<long long> polynomial_add(vector<long long> a, vector<long long> b, long long mod);
vector<mpz_class> polynomial_times(vector<mpz_class> a, vector<mpz_class> b, mpz_class mod);


vector<complex<double>> vector_times(vector<complex<double>> a, double b);
vector<complex<double>> vector_times(vector<complex<double>> a, complex<double> b);
complex<double> hermitian_product(vector<complex<double>> a, vector<complex<double>> b);
complex<double> vector_product(vector<complex<double>> a, vector<complex<double>> b);

#endif
