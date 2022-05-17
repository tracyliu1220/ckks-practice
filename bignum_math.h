#ifndef BIGNUM_MATH_H
#define BIGNUM_MATH_H

#include <gmp.h>
#include <gmpxx.h>

extern mpf_class bignum_PI;

mpf_class bignum_sin(mpf_class x);
mpf_class bignum_cos(mpf_class x);

#endif
