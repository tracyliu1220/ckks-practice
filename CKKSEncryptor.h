#ifndef CKKSENCRYPTOR_H
#define CKKSENCRYPTOR_H

#include <bits/stdc++.h>
#include "ciphertext.h"

class CKKSEncryptor {
public:
    int N;
    // int L;
    mpz_class Q;
    int Q_bits;
    mpz_class P;
    mpz_class q0;
    vector<mpz_class> p;

    vector<mpz_class> secret_key;
    pair<vector<mpz_class>, vector<mpz_class>> public_key;

    CKKSEncryptor() = delete;
    CKKSEncryptor(int N, mpz_class q0, vector<mpz_class> p);

    /* modulus generation */
    // void generate_modulus();

    /* key generation */
    vector<mpz_class> generate_secret_key();
    pair<vector<mpz_class>, vector<mpz_class>> generate_public_key();

    Ciphertext encrypt(vector<long long> mu);
    vector<long long> decrypt(Ciphertext c);
};

#endif
