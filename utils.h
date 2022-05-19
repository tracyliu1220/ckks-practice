#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

class Complex {
public:
    mpf_class x, y;
    Complex() {
    }
    Complex(mpf_class _x, mpf_class _y) : x(_x), y(_y) {};
    void set_prec(int n) {
        x.set_prec(n);
        y.set_prec(n);
    }
    Complex operator+(const Complex& c) const { return Complex(x + c.x, y + c.y); }
    Complex operator-(const Complex& c) const { return Complex(x - c.x, y - c.y); }
    Complex operator*(const Complex& c) const { return Complex(x*c.x - y*c.y, x*c.y + y*c.x); }
    Complex operator/(const mpf_class d) const {
        mpf_class _d(d, x.get_prec());
        return Complex((x / d), (y / d));
    }
};

vector<complex<double>> long_to_complex(vector<long long> v);
vector<long long> complex_to_long(vector<complex<double>> v);
vector<complex<double>> random_rounding(vector<complex<double>> v);
vector<Complex> FFT(vector<mpz_class> c, int T, int precision);
vector<Complex> FFT(vector<Complex> c, int T);
vector<complex<double>> FFT(vector<long long> c, int T);
vector<complex<double>> FFT(vector<complex<double>>, int);
// vector<complex<double>> linear_system_solve(const vector<vector<complex<double>>> & A, const vector<complex<double>> & b);
complex<double> apply(const vector<complex<double>> & p, complex<double> root);

mpz_class extgcd(mpz_class a, mpz_class b, mpz_class &x, mpz_class &y);
mpz_class mod_inverse(mpz_class a, mpz_class m);

#endif
