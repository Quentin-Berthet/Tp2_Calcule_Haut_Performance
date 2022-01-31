#include <assert.h>
#include <math.h>
#include "complex.h"

complex_t complex_t_init(double real, double imaginary) {
    return (complex_t) {real, imaginary};
}

complex_t complex_t_add(complex_t *self, complex_t *rhs) {
    assert(self != NULL && rhs != NULL);
    return (complex_t) {self->real + rhs->real, self->imaginary + rhs->imaginary};
}

complex_t complex_t_mul(complex_t *self, complex_t *rhs) {
    assert(self != NULL && rhs != NULL);
    return (complex_t) {self->real * rhs->real - self->imaginary * rhs->imaginary,
                        self->real * rhs->imaginary + self->imaginary * rhs->real};
}

double complex_t_modulus(complex_t *self) {
    double sum = pow(self->real, 2.0) + pow(self->imaginary, 2.0);
    return sqrt(sum);
}
