#ifndef COMPLEX_H
#define COMPLEX_H

#include <math.h>
#include <stdlib.h>

typedef struct complex_t {
    double real;
    double imaginary;
} complex_t;

complex_t complex_t_init(double real, double imaginary);

complex_t complex_t_add(complex_t *self, complex_t *rhs);

complex_t complex_t_mul(complex_t *self, complex_t *rhs);

double complex_t_modulus(complex_t *self);

void *complex_t_destroy(complex_t *self);

#endif //COMPLEX_H
