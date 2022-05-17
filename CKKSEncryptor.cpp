#include <bits/stdc++.h>
#include "utils.h"
#include "vector_ops.h"
#include "CKKSEncryptor.h"
#include "ciphertext.h"

CKKSEncryptor::CKKSEncryptor(int N) : N(N) {
    generate_modulus();
    secret_key = generate_secret_key();
    public_key = generate_public_key();
}

void CKKSEncryptor::generate_modulus() {
    // L = 2;
    // q0 = 65521; // close to 1 << 16
    // p = {16381, 16369}; // close to 1 << 14
    // P = 65521;
    // Q = q0;
    // for (int i = 0; i < (int)p.size(); i++) {
    //     Q *= p[i];
    // }
    Q = 1;
    for (int i = 0; i < 50; i++) {
        Q *= 2;
    }
    Q_bits = 0;
    mpz_class test_Q = 1;
    while (test_Q < Q) {
        test_Q *= 2;
        Q_bits++;
    }
}

vector<mpz_class> CKKSEncryptor::generate_secret_key() {
    gmp_randclass r(gmp_randinit_default);

    vector<mpz_class> ret;
    for (int i = 0; i < N; i++) {
        ret.push_back(r.get_z_bits(Q_bits) % Q);
    }
    return ret;
}

pair<vector<mpz_class>, vector<mpz_class>> CKKSEncryptor::generate_public_key() {
    gmp_randclass r(gmp_randinit_default);

    vector<mpz_class> a;
    for (int i = 0; i < N; i++) {
        a.push_back(r.get_z_bits(Q_bits) % Q);
    }

    // TODO: add e

    vector<mpz_class> ret1 = polynomial_times(a, secret_key, Q);
    ret1 = polynomial_neg(ret1, Q);

    return {ret1, a};
}

Ciphertext CKKSEncryptor::encrypt(vector<long long> mu) {
    vector<mpz_class> _mu(mu.size());

    for (int i = 0; i < (int)mu.size(); i++) {
        _mu[i] = (long int)mu[i];
        if (_mu[i] < 0) _mu[i] += Q * ((-_mu[i]) / Q + 1);
        _mu[i] %= Q;
    }
    Ciphertext ret;
    ret.Q = Q;
    // ret.q0 = q0;
    // ret.p = p;
    ret.c0 = polynomial_add(_mu, public_key.first, Q);
    ret.c1 = public_key.second;
    return ret;
}

vector<long long> CKKSEncryptor::decrypt(Ciphertext c) {
    vector<mpz_class> mu = polynomial_add(c.c0, polynomial_times(c.c1, secret_key, Q), Q);

    for (int i = 0; i < (int)mu.size(); i++) {
      if (mu[i] > Q / 2) mu[i] = mu[i] - Q;
    }
    vector<long long> ret;
    for (int i = 0; i < (int)mu.size(); i++) {
        ret.push_back(mu[i].get_si());
    }
    return ret;
}
