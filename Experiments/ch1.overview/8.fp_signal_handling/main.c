#include <stdio.h>
#include <fenv.h>
#include <float.h>
#include <signal.h>
#include <setjmp.h>

sigjmp_buf buffer;

void fp_handler(int sig) {
    fprintf(stderr, "SIGFP is catched!\n");
    if (sig == SIGFPE) {
        siglongjmp(buffer, 1);
    }
    else {
        signal(SIGFPE, fp_handler);
    }
}

int main(void) {
	feenableexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW);
    signal(SIGFPE, fp_handler);

	double x = DBL_MIN;
    printf("min normal = %g\n", x);
	x = DBL_MIN / 13.0;
    printf("min normal / 13.0 = %g\n", x);
	x = DBL_MAX;
    printf("max normal = %g\n", x);

    if (sigsetjmp(buffer, 1) == 0) {
        x = DBL_MAX * DBL_MAX;
    }
    else {
        fedisableexcept(FE_OVERFLOW);
        x = DBL_MAX * DBL_MAX;
        printf("max normal * max normal = %g\n", x);
        feenableexcept(FE_OVERFLOW);
    }
	return 0;
}
