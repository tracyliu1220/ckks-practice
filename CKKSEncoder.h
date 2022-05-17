#ifndef CKKSENCODER_H
#define CKKSENCODER_H

#include <bits/stdc++.h>
using namespace std;

class CKKSEncoder {
public:
    /* variables */
    int M;
    int N;
    complex<double> xi;
    double scale_factor;
    vector<vector<complex<double>>> sigma_R_basis;
    vector<complex<double>> sigma_R_basis_L2;

    /* init */
    CKKSEncoder() = delete;
    CKKSEncoder(int, double);


    /* vandermonde */
    // vector<vector<complex<double>>> vandermonde();
    // vector<vector<complex<double>>> create_sigma_R_basis();
    // vector<complex<double>> calculate_sigma_R_L2();

    /* sigma */
    vector<complex<double>> sigma_inverse(const vector<complex<double>> &b);
    vector<complex<double>> sigma(vector<complex<double>> p);

    /* pi */
    vector<complex<double>> pi(vector<complex<double>> z);
    vector<complex<double>> pi_inverse(vector<complex<double>> z);

    /* project on sigma R */
    vector<complex<double>> project_on_beta(vector<complex<double>> z);
    vector<complex<double>> project_sigma_R(vector<complex<double>> z);

    vector<long long> encode(vector<complex<double>> z);
    vector<complex<double>> decode(vector<long long> p);
};

#endif
