#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);

    
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, time(NULL));

    while(1){
        //random 512-bit prime candidate for q
        mpz_urandomb(q, state, 511);
        mpz_nextprime(q, q);
        
        // p = 2q + 1
        mpz_mul_ui(p, q, 2);
        mpz_add_ui(p, p, 1);
        
        // check if p is also prime
        if(mpz_probab_prime_p(p, 25)){ //25 rounds , error probability is at like 4^-25, 1 in 1.1 quadrillion that it isnt prime
            printf("p = ");
            mpz_out_str(stdout, 16, p);
            printf("\n");
            break;
        }
    }

    mpz_clear(p);
    mpz_clear(q);
    gmp_randclear(state);
    return 0;

}