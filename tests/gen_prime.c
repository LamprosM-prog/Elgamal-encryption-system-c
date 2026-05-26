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
    mpz_t seed_mpz;
    mpz_init(seed_mpz);
   
    FILE *f = fopen("/dev/urandom", "rb");
    unsigned char seed_buf[64]; 
    fread(seed_buf, 1, 64, f);
    fclose(f);
    mpz_import(seed_mpz, 64, 1, 1, 0, 0, seed_buf);

    gmp_randseed(state, seed_mpz);
    mpz_clear(seed_mpz);


    int attempts = 0;
    while (1) {
        mpz_urandomb(q, state, 4095);
        mpz_setbit(q, 4094);
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