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

void Ciphertext::rescale() {
    mpz_class pl = p.back();
    cout << "pl: " << pl << endl;
    p.pop_back();

    // calculate new Q
    Q = q0;
    for (int i = 0; i < (int)p.size(); i++) {
        Q *= p[i];
    }

    int prec = 500;

    for (int i = 0; i < (int)c0.size(); i++) {
        c0[i] = (c0[i] / pl) % Q;
        c1[i] = (c1[i] / pl) % Q;
        // mpf_class c0_f(c0[i], prec);
        // mpf_class c1_f(c1[i], prec);
        // c0[i] = (mpz_class)(((c0_f / pl) * 10 + 5) / 10) % Q;
        // c1[i] = (mpz_class)(((c1_f / pl) * 10 + 5) / 10) % Q;
    }
}
