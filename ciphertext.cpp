#include "ciphertext.h"
#include "vector_ops.h"

Ciphertext Ciphertext::operator+(const Ciphertext & rhs) {
    Ciphertext ret = rhs;
    ret.c0 = polynomial_add(c0, rhs.c0, Q);
    ret.c1 = polynomial_add(c1, rhs.c1, Q);
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
