#include <bits/stdc++.h>
// #include <Eigen/Dense>
#include <gmp.h>
#include <gmpxx.h>
#include "utils.h"
using namespace std;
// using namespace Eigen;

const complex<double> _e = {M_E, 0.0};
const complex<double> _i = {0.0, 1.0};

vector<complex<double>> long_to_complex(vector<long long> v) {
    vector<complex<double>> ret;
    for (int i = 0; i < (int)v.size(); i++)
        ret.push_back(v[i]);
    return ret;
}

vector<long long> complex_to_long(vector<complex<double>> v) {
    vector<long long> ret;
    for (int i = 0; i < (int)v.size(); i++)
        ret.push_back(round(v[i].real()));
    return ret;
}

vector<complex<double>> random_rounding(vector<complex<double>> v) {
    int range = 100000;
    vector<complex<double>> ret;
    for (int i = 0; i < (int)v.size(); i++) {
        double cur = v[i].real();
        int bound = (cur - (int)cur) * range;
        int r = rand() % range;
        if (r > bound) ret.push_back((int)cur);
        else ret.push_back((int)cur + 1);
    }
    return ret;
}

complex<double> apply(const vector<complex<double>> & p, complex<double> root) {
    complex<double> ret = 0.0;
    for (int i = 0; i < (int)p.size(); i++) {
       ret += p[i] * pow(root, i);
    }
    return ret;
}

/*
// Ax = b
vector<complex<double>> linear_system_solve(const vector<vector<complex<double>>> & A, const vector<complex<double>> & b) {
    int n = A.size();

    // copy A
    MatrixXcd eA = MatrixXcd::Random(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            eA(i, j) = A[i][j];
        }
    }

    // copy b
    VectorXcd eb = VectorXcd::Random(n);
    for (int i = 0; i < n; i++)
        eb(i) = b[i];

    // solve
    VectorXcd ex = eA.inverse() * eb;

    // copy x back
    vector<complex<double>> x(n);
    for (int i = 0; i < n; i++)
        x[i] = ex(i);
    return x;
}
*/

/*
vector<complex<double>> FFT(vector<long long> c, int T) {
    vector<complex<double>> complex_c = long_to_complex(c);
    complex_c = FFT(complex_c, T);
    return complex_c;
}
*/

vector<Complex> FFT(vector<mpz_class> c, int T) {
    vector<Complex> _c(c.size());
    for (int i = 0; i < (int)c.size(); i++) {
        _c[i].x = c[i];
        _c[i].y = 0.0;
        // _c[i].set_prec((_c[i].x.get_prec() + 20) * c.size());
        _c[i].set_prec(500);
    }
    _c = FFT(_c, T);
    return _c;
}

vector<Complex> FFT(vector<Complex> c, int T) {
    int n = c.size();
    for (int i = 1, j = 0; i < n; i++) {
        for (int k = (n >> 1); k > (j ^= k); k >>= 1)
            ;
        if (i < j)
            swap(c[i], c[j]);
    }
    for (int m = 2; m <= n; m <<= 1) {
        // C wm(cos(2 * PI * T / m), sin(2 * PI * T / m));
        Complex wm(cos(2 * M_PI * T / m), sin(2 * M_PI * T / m));
        wm.set_prec(c[0].x.get_prec());
        for (int k = 0; k < n; k += m) {
            // C w(1.0, 0.0);
            Complex w(1.0, 0.0);
            w.set_prec(c[0].x.get_prec());
            for (int j = 0; j < (m >> 1); j++, w = w * wm) {
                Complex u = c[k + j], t = w * c[k + j + (m >> 1)];
                c[k + j] = u + t;
                c[k + j + (m >> 1)] = u - t;
            }
        }
    }
    if (!~T)
        for (int i = 0; i < n; i++)
            c[i].x /= n, c[i].y /= n;
    return c;
}

vector<complex<double>> FFT(vector<complex<double>> c, int T) {
    int n = c.size();
    for (int i = 1, j = 0; i < n; i++) {
        for (int k = (n >> 1); k > (j ^= k); k >>= 1)
            ;
        if (i < j)
            swap(c[i], c[j]);
    }
    for (int m = 2; m <= n; m <<= 1) {
        // C wm(cos(2 * PI * T / m), sin(2 * PI * T / m));
        complex<double> wm(cos(2 * M_PI * T / m), sin(2 * M_PI * T / m));
        for (int k = 0; k < n; k += m) {
            // C w(1.0, 0.0);
            complex<double> w(1.0, 0.0);
            for (int j = 0; j < (m >> 1); j++, w = w * wm) {
                complex<double> u = c[k + j], t = w * c[k + j + (m >> 1)];
                c[k + j] = u + t;
                c[k + j + (m >> 1)] = u - t;
            }
        }
    }
    if (!~T)
        for (int i = 0; i < n; i++)
            // c[i].x /= n, c[i].y /= n;
            c[i].real(c[i].real() / n), c[i].imag(c[i].imag() / n);
    return c;
}

/*
int main() {
    vector<vector<complex<double>>> A;
    int n = 2;
    A.resize(n);
    for (int i = 0; i < n; i++) {
        A[i].resize(n);
    }

    A[0][0] = 1.0;
    A[0][1] = 2.0;
    A[1][0] = 3.0;
    A[1][1] = 4.0;

    vector<complex<double>> b = {1.0, 1.0};

    vector<complex<double>> x = linear_system_solve(A, b);

    for (int i = 0; i < n; i++) {
        cout << x[i];
    }
    cout << endl;


    return 0;
}
*/

/*
// LatexEnd
typedef long long LL;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    while (cin >> n) {
        int len = 1;
        while (len < 2 * n)
            len <<= 1;
        vector<complex<double>> A(len), B(len);
        double tmp;
        for (int i = 0; i < n; i++)
            cin >> tmp, A[i].real(tmp);
        for (int i = 0; i < n; i++)
            cin >> tmp, B[i].real(tmp);
        FFT(A, 1);
        FFT(B, 1);
        vector<complex<double>> C(len);
        for (int i = 0; i < len; i++)
            C[i] = A[i] * B[i];
        FFT(C, -1);
        for (int i = 0; i < 2 * n - 1; i++)
            cout << LL(C[i].real() + 0.5) << " \n"[i + 1 == 2 * n - 1];
    }
}
*/
