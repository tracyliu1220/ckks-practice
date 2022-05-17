#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

class Ciphertext {
public:
    mpz_class Q;
    // long long q0;
    // vector<long long> p;
    vector<mpz_class> c0;
    vector<mpz_class> c1;

    Ciphertext operator+(const Ciphertext & rhs);
    Ciphertext operator*(const vector<long long> & rhs);
};

#endif
