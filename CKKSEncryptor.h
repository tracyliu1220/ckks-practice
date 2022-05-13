#ifndef CKKSENCRYPTOR_H
#define CKKSENCRYPTOR_H

#include <bits/stdc++.h>
#include "ciphertext.h"

class CKKSEncryptor {
public:
    int N;
    int L;
    long long Q;
    long long P;
    long long q0;
    vector<long long> p;

    vector<long long> secret_key;
    pair<vector<long long>, vector<long long>> public_key;

    CKKSEncryptor() = delete;
    CKKSEncryptor(int);

    /* modulus generation */
    void generate_modulus();

    /* key generation */
    vector<long long> generate_secret_key();
    pair<vector<long long>, vector<long long>> generate_public_key();

    Ciphertext encrypt(vector<long long> mu);
    vector<long long> decrypt(Ciphertext c);
};

#endif
