#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
#include "utils.h"

using namespace std;

vector<mpz_class> polynomial_neg(vector<mpz_class> a, mpz_class mod) {
    for (int i = 0; i < (int)a.size(); i++) {
        a[i] = (mod - a[i]) % mod;
    }
    return a;
}

vector<mpz_class> polynomial_add(vector<mpz_class> a, vector<mpz_class> b, mpz_class mod) {
    for (int i = 0; i < (int)a.size(); i++) {
        a[i] = (a[i] + b[i]) % mod;
    }
    return a;
}

vector<mpz_class> polynomial_times(vector<mpz_class> a, vector<mpz_class> b, mpz_class mod) {
    int n = a.size();
    a.resize(2 * n);
    b.resize(2 * n);
    fill(a.begin() + n, a.end(), 0);
    fill(b.begin() + n, b.end(), 0);

    vector<Complex> _a = FFT(a, 1);
    vector<Complex> _b = FFT(b, 1);
    for (int i = 0; i < (int)_a.size(); i++) {
        _a[i] = _a[i] * _b[i];
    }
    _a = FFT(_a, -1);

    // complex mpf to mpz (round)
    for (int i = 0; i < (int)_a.size(); i++) {
        a[i] = floor((_a[i].x * 10 + 5) / 10);
    }

    for (int i = n; i < 2 * n; i++) {
        mpz_class x = a[i % n] - a[i];
        if (x < 0)
            x += mod * ((-x) / mod + 1);
        a[i % n] = x % mod;
    }
    a.resize(n);

    return a;
}

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
