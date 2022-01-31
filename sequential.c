#include <stdio.h>
#include "complex.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define MANDELBROT_MIN (-2)
#define MANDELBROT_MAX (2)

#define INDEX_2D_TO_1D(x, y, nb_columns) ((y) * nb_columns + (x))

double *linspace(double start, double end, int number) {
    double step = (fabs(start) + fabs(end)) / (number - 1.0);
    double *array = malloc((size_t) number * sizeof(double));
    array[0] = start;
    for (int i = 1; i < (number - 1); ++i) {
        array[i] = array[i - 1] + step;
    }
    array[number - 1] = end;
    return array;
}

bool *compute_mandelbrot(int max_iter, int d, int nx, int ny) {
    double *xs = linspace(MANDELBROT_MIN, MANDELBROT_MAX, nx);
    double *ys = linspace(MANDELBROT_MIN, MANDELBROT_MAX, ny);

    complex_t *cs = malloc((size_t) (nx * ny) * sizeof(complex_t));
    complex_t *zs = malloc((size_t) (nx * ny) * sizeof(complex_t));
    bool *bs = malloc((size_t) (nx * ny) * sizeof(bool));

    for (int y = 0; y < ny; ++y) {
        for (int x = 0; x < nx; ++x) {
            int idx = INDEX_2D_TO_1D(x, y, nx);
            cs[idx] = complex_t_init(xs[y], ys[x]);
            zs[idx] = complex_t_init(xs[y], ys[x]);
        }
    }

    for (int i = 0; i < max_iter; ++i) {
        for (int y = 0; y < ny; ++y) {
            for (int x = 0; x < nx; ++x) {
                int idx = INDEX_2D_TO_1D(x, y, nx);
                complex_t power2 = complex_t_mul(&zs[idx], &zs[idx]);
                complex_t add_c = complex_t_add(&power2, &cs[idx]);
                zs[idx] = add_c;
                bs[idx] = complex_t_modulus(&zs[idx]) < d;
            }
        }
    }

    free(xs);
    free(ys);
    free(cs);
    free(zs);
    return bs;
}

int main() {
    int nx = 5;
    int ny = 5;

    bool *res = compute_mandelbrot(100, 15, nx, ny);

    FILE *fp;
    fp = fopen("test.txt", "w");

    for (int y = 0; y < ny; ++y) {
        for (int x = 0; x < nx; ++x) {
            int idx = INDEX_2D_TO_1D(x, y, nx);
            fprintf(fp, "%d ", res[idx]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    free(res);
    return 0;
}
