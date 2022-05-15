#include <bits/stdc++.h>

#include "utils.h"

using namespace std;

/*
vector<long long> polynomial_neg(vector<long long> a, long long mod) {
    for (int i = 0; i < (int)a.size(); i++) {
        a[i] = (mod - a[i]) % mod;
    }
    return a;
}

vector<long long> polynomial_add(vector<long long> a, vector<long long> b, long long mod) {
    for (int i = 0; i < (int)a.size(); i++) {
        a[i] = (a[i] + b[i]) % mod;
    }
    return a;
}

vector<long long> polynomial_times(vector<long long> a, vector<long long> b, long long mod) {
    int n = a.size();
    a.resize(2 * n);
    b.resize(2 * n);
    fill(a.begin() + n, a.end(), 0);
    fill(b.begin() + n, b.end(), 0);

    vector<complex<double>> _a = FFT(a, 1);
    vector<complex<double>> _b = FFT(b, 1);

    for (int i = 0; i < (int)_a.size(); i++) {
        _a[i] = _a[i] * _b[i];
    }
    _a = FFT(_a, -1);

    a = complex_to_long(_a);

    for (int i = n; i < 2 * n; i++) {
        long long x = a[i % n] - a[i];
        if (x < 0)
            x += mod * ((-x - mod + 1) / mod);
        a[i % n] = x % mod;
    }
    a.resize(n);

    return a;
}
*/

vector<complex<double>> vector_times(vector<complex<double>> a, double b) {
    for (int i = 0; i < (int)a.size(); i++) {
        a[i] *= b;
    }
    return a;
}

vector<complex<double>> vector_times(vector<complex<double>> a, complex<double> b) {
    for (int i = 0; i < (int)a.size(); i++) {
        a[i] *= b;
    }
    return a;
}

complex<double> hermitian_product(vector<complex<double>> a, vector<complex<double>> b) {
    complex<double> ret(0, 0);
    for (int i = 0; i < (int)a.size(); i++) {
        ret += a[i] * conj(b[i]);
    }
    return ret;
}

complex<double> vector_product(vector<complex<double>> a, vector<complex<double>> b) {
    complex<double> ret(0, 0);
    for (int i = 0; i < (int)a.size(); i++) {
        ret += a[i] * b[i];
    }
    return ret;
}
