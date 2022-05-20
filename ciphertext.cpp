#include "ciphertext.h"
#include "vector_ops.h"
#include "utils.h"

Ciphertext Ciphertext::operator+(const Ciphertext & rhs) {
    Ciphertext ret;
    if (Q < rhs.Q) ret = *this;
    else ret = rhs;
    mpz_class cur_Q = ret.Q;
    ret.c0 = polynomial_add(c0, rhs.c0, cur_Q);
    ret.c1 = polynomial_add(c1, rhs.c1, cur_Q);
    return ret;
}

Ciphertext Ciphertext::operator*(const vector<long long> & rhs) {
    vector<mpz_class> _rhs(rhs.size());
    for (int i = 0; i < (int)rhs.size(); i++) {
        _rhs[i] = (long int)rhs[i];
    }
    Ciphertext ret = *this;
    ret.c0 = polynomial_times(c0, _rhs, Q);
    ret.c1 = polynomial_times(c1, _rhs, Q);
    return ret;
}

Ciphertext Ciphertext::operator*(const Ciphertext & rhs) {
    Ciphertext ret;
    if (Q < rhs.Q) ret = *this;
    else ret = rhs;
    mpz_class cur_Q = ret.Q;

    vector<mpz_class> d0 = polynomial_times(c0, rhs.c0, Q);
    vector<mpz_class> d1_0 = polynomial_times(c0, rhs.c1, Q);
    vector<mpz_class> d1_1 = polynomial_times(c1, rhs.c0, Q);
    vector<mpz_class> d1 = polynomial_add(d1_0, d1_1, Q);
    vector<mpz_class> d2 = polynomial_times(c1, rhs.c1, Q);

    for (int i = 0; i < (int)d2.size(); i++) {
        mpf_class d2_f(d2[i], Q_bits + 64);
        d2[i] = (mpz_class)(((d2_f / P) * 10 + 5) / 10) % Q;
    }

    vector<mpz_class> P0 = polynomial_times(d2, evaluation_key.first, P * Q);
    vector<mpz_class> P1 = polynomial_times(d2, evaluation_key.second, P * Q);

    // for (int i = 0; i < (int)P0.size(); i++) {
    //     mpf_class P0_f(P0[i], Q_bits + 64);
    //     mpf_class P1_f(P1[i], Q_bits + 64);
    //     P0[i] = (mpz_class)(((P0_f / P) * 10 + 5) / 10) % Q;
    //     P1[i] = (mpz_class)(((P1_f / P) * 10 + 5) / 10) % Q;
    // }

    ret.c0 = polynomial_add(d0, P0, Q);
    ret.c1 = polynomial_add(d1, P1, Q);

    return ret;
}

void Ciphertext::rescale() {
    mpz_class pl = p.back();
    cout << "pl: " << pl << endl;
    p.pop_back();

    // calculate new Q
    Q = q0;
    for (int i = 0; i < (int)p.size(); i++) {
        Q *= p[i];
    }

    // calculate new Q_bits
    Q_bits = 0;
    mpz_class test_Q = 1;
    while (test_Q < Q) {
        test_Q *= 2;
        Q_bits++;
    }

    for (int i = 0; i < (int)c0.size(); i++) {
        // c0[i] = (c0[i] / pl) % Q;
        // c1[i] = (c1[i] / pl) % Q;
        mpf_class c0_f(c0[i], Q_bits + 64);
        mpf_class c1_f(c1[i], Q_bits + 64);
        c0[i] = (mpz_class)(((c0_f / pl) * 10 + 5) / 10) % Q;
        c1[i] = (mpz_class)(((c1_f / pl) * 10 + 5) / 10) % Q;
    }
}
