#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

class Ciphertext {
public:
    mpz_class Q;
    int Q_bits;
    mpz_class q0;
    vector<mpz_class> p;
    vector<mpz_class> c0;
    vector<mpz_class> c1;
    mpz_class P;
    pair<vector<mpz_class>, vector<mpz_class>> evaluation_key;

    Ciphertext(){};
    Ciphertext(const Ciphertext& rhs): Q(rhs.Q), q0(rhs.q0), p(rhs.p), c0(rhs.c0), c1(rhs.c1) {};
    Ciphertext operator+(const Ciphertext & rhs);
    Ciphertext operator*(const Ciphertext & rhs);
    Ciphertext operator*(const vector<long long> & rhs);
    void rescale();
};

#endif
