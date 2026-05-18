#include "../src/elgamal.h"
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(){
    ElGamalParam params;
    mpz_init(params.p);
    mpz_init(params.q);
    mpz_init(params.g);


    generate_param(&params);

    //generate keys
    mpz_t x; //secret
    mpz_init(x);
    generate_skey(x,params.q);

    mpz_t y; // public
    mpz_init(y); 
    generate_pkey(y,params.g,x,params.p);

    //message
    char* msg = "Hello";
    mpz_t msg_mpz;
    mpz_init(msg_mpz);
    mpz_import(msg_mpz, strlen(msg), 1, 1, 0, 0, msg);
    printf("%s\n", msg);


    //encrypt
    ElgamalCiphertext ciphers;
    mpz_init(ciphers.c1);
    mpz_init(ciphers.c2);
    
    encrypt(&ciphers, msg_mpz, y, &params);

    // print first 16 chars of c1
    char* c1_str = mpz_get_str(NULL, 16, ciphers.c1);
    printf("c1: %.16s...\n", c1_str);   
    free(c1_str);


    //decrypt
    mpz_t msg_dec_mpz;
    mpz_init(msg_dec_mpz);

    decrypt(msg_dec_mpz, &ciphers, x, params.p);

    //export
    char buf[64] = {0};
    size_t count;
    mpz_export(buf, &count, 1, 1, 0, 0, msg_dec_mpz);
    printf("%s\n", buf);

    mpz_clear(params.q);
    mpz_clear(params.g);
    mpz_clear(params.p);
    mpz_clear(ciphers.c1);
    mpz_clear(ciphers.c2);
    mpz_clear(msg_mpz);
    mpz_clear(msg_dec_mpz);
    mpz_clear(x);
    mpz_clear(y);

    return 0;
}