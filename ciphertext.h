#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

class Ciphertext {
public:
    long long Q;
    // long long q0;
    // vector<long long> p;
    vector<mpz_class> c0;
    vector<mpz_class> c1;

    // Ciphertext operator+(const Ciphertext & rhs);
    // Ciphertext operator*(const vector<mpz_class> & rhs);
};

#endif
