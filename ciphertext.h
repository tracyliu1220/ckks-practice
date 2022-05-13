#ifndef CIPHERTEXT_H
#define CIPHERTEXT_H

#include <bits/stdc++.h>
using namespace std;

class Ciphertext {
public:
    long long Q;
    long long q0;
    vector<long long> p;
    vector<long long> c0;
    vector<long long> c1;

    Ciphertext operator+(const Ciphertext & rhs);
    Ciphertext operator*(const vector<long long> & rhs);
};

#endif
