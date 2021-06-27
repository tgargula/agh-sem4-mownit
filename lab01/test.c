#include <gsl/gsl_interp.h>
#include <stdio.h>

int main(void) {
    double d = 1.1;
    while (1) {
        gsl_ieee_printf_double(&d);
        printf("\n");
        d /= 2.0;
        if (d == 0) break;
    }
    return 0;
}