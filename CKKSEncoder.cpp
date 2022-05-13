#include "CKKSEncoder.h"
#include "utils.h"
#include "vector_ops.h"
#include <bits/stdc++.h>
using namespace std;

const complex<double> _e = {M_E, 0.0};
const complex<double> _i = {0.0, 1.0};

/* init */
CKKSEncoder::CKKSEncoder(int M, double scale) : M(M), scale_factor(scale) {
    N = M / 2;
    xi = pow(_e, 2.0 * _i * M_PI / (double)M);
    sigma_R_basis = create_sigma_R_basis();
    sigma_R_basis_L2 = calculate_sigma_R_L2();
}

/* vandermonde */
vector<vector<complex<double>>> CKKSEncoder::vandermonde() {
    vector<vector<complex<double>>> matrix;

    for (int i = 0; i < N; i++) {
        complex<double> root = pow(xi, 2.0 * i + 1.0);
        vector<complex<double>> matrix_row;

        for (int j = 0; j < N; j++) {
            matrix_row.push_back(pow(root, j));
        }

        matrix.push_back(matrix_row);
    }

    return matrix;
}

vector<vector<complex<double>>> CKKSEncoder::create_sigma_R_basis() {
    vector<vector<complex<double>>> matrix = vandermonde();
    // get matrix.T
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
    return matrix;
}

vector<complex<double>> CKKSEncoder::calculate_sigma_R_L2() {
    vector<complex<double>> ret;
    for (int i = 0; i < N; i++) {
        ret.push_back(hermitian_product(sigma_R_basis[i], sigma_R_basis[i]));
    }
    return ret;
}

/* sigma */
vector<complex<double>>
CKKSEncoder::sigma_inverse(const vector<complex<double>> &b) {

    vector<complex<double>> nb(M);
    for (int i = 0; i < N; i++) {
        nb[2 * i + 1] = b[i];
    }
    vector<complex<double>> coeffs = FFT(nb, -1);
    coeffs = vector_times(coeffs, 2);
    coeffs.resize(N);

    /*
    vector<vector<complex<double>>> A = vandermonde();
    // A * coeffs = b
    // known: A and b
    // use linear algebra to get coeffs
    vector<complex<double>> coeffs = linear_system_solve(A, b);
    */

    return coeffs;
}

vector<complex<double>> CKKSEncoder::sigma(vector<complex<double>> p) {
    /*
    vector<complex<double>> ret;
    for (int i = 0; i < N; i++) {
            complex<double> root = pow(xi, 2.0 * i + 1.0);
            complex<double> output = apply(p, root);
            ret.push_back(output);
    }
    */

    p.resize(M);
    fill(p.begin() + N, p.end(), 0);
    p = FFT(p, 1);
    for (int i = 0; i < N; i++) {
        p[i] = p[i * 2 + 1];
    }
    p.resize(N);

    return p;
}

/* pi */
vector<complex<double>> CKKSEncoder::pi(vector<complex<double>> z) {
    // size: N -> N / 2
    z.resize(N / 2);
    return z;
}

vector<complex<double>> CKKSEncoder::pi_inverse(vector<complex<double>> z) {
    // size: N / 2 -> N
    for (int i = N / 2 - 1; i >= 0; i--) {
        z.push_back(conj(z[i]));
    }
    return z;
}

/* project on sigma R */
vector<complex<double>>
CKKSEncoder::project_on_beta(vector<complex<double>> z) {
    // TODO: complexity O(n^2)
    vector<complex<double>> ret(N);
    for (int i = 0; i < N; i++) {
        complex<double> zi = hermitian_product(z, sigma_R_basis[i]);
        zi /= sigma_R_basis_L2[i];
        ret[i] = zi;
    }
    return ret;
}

vector<complex<double>>
CKKSEncoder::project_sigma_R(vector<complex<double>> z) {
    vector<complex<double>> coor = random_rounding(project_on_beta(z));
    coor.resize(M);
    fill(coor.begin() + N, coor.end(), 0);

    vector<complex<double>> projected = FFT(coor, 1);
    for (int i = 0; i < M; i++) {
        projected[i] = projected[2 * i + 1];
    }
    projected.resize(N);
    return projected;
}

vector<long long> CKKSEncoder::encode(vector<complex<double>> z) {
    z = pi_inverse(z);
    z = vector_times(z, scale_factor);
    vector<complex<double>> projected = project_sigma_R(z);
    vector<complex<double>> cp = sigma_inverse(projected);

    vector<long long> p;
    for (int i = 0; i < (int)cp.size(); i++) {
        p.push_back(round(cp[i].real()));
    }
    // project
    // sigma_inverse
    return p;
}

vector<complex<double>> CKKSEncoder::decode(vector<long long> p) {
    vector<complex<double>> cp = long_to_complex(p);
    cp = vector_times(cp, 1 / scale_factor);
    vector<complex<double>> z = sigma(cp);
    z = pi(z);
    return z;
}
