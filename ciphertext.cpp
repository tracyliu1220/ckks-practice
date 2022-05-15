#include "ciphertext.h"
#include "vector_ops.h"

/*
Ciphertext Ciphertext::operator+(const Ciphertext & rhs) {
    Ciphertext ret = rhs;
    ret.c0 = polynomial_add(c0, rhs.c0, Q);
    ret.c1 = polynomial_add(c1, rhs.c1, Q);
    return ret;
}

Ciphertext Ciphertext::operator*(const vector<mpz_class> & rhs) {
    Ciphertext ret = *this;
    ret.c0 = polynomial_times(rhs, c0, Q);
    ret.c1 = polynomial_times(rhs, c1, Q);
    return ret;
}
*/
