#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);

    gmp_randstate_t state;
    gmp_randinit_mt(state);

    // /dev/urandom seed
    uint64_t seed;
    FILE *f = fopen("/dev/urandom", "rb");
    fread(&seed, sizeof(seed), 1, f);
    fclose(f);
    gmp_randseed_ui(state, seed);

    int attempts = 0;
    while (1) {
        mpz_urandomb(q, state, 4095);
        mpz_nextprime(q, q);

        mpz_mul_ui(p, q, 2);
        mpz_add_ui(p, p, 1);

        if (mpz_probab_prime_p(p, 25)) {
            printf("\nFound after %d attempts\n", attempts);
            printf("p = ");
            mpz_out_str(stdout, 16, p);
            printf("\n");
            break;
        }

        if (++attempts % 100 == 0) {
            printf(".");
            fflush(stdout);
        }
    }

    mpz_clear(p);
    mpz_clear(q);
    gmp_randclear(state);
    return 0;
}