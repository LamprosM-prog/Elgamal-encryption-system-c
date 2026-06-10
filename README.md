# ElGamal Encryption in C

A from-scratch ElGamal asymmetric encryption implementation in C using GMP for arbitrary precision arithmetic. Built as the encryption layer of a larger Reed-Solomon + ElGamal protocol over UDP.

## What's implemented

- **Parameter generation** — 512-bit safe prime `p`, generator `g = 2`, subgroup order `q = (p-1)/2`
- **Key generation** — private key `x` (random in `(1, q-1)`), public key `y = g^x mod p`
- **Encryption** — ephemeral key `k`, ciphertext `(c1, c2) = (g^k mod p, m * y^k mod p)`
- **Decryption** — shared secret `s = c1^x mod p`, message `m = c2 * s^(-1) mod p`

Uses `mpz_powm_sec` throughout for constant-time modular exponentiation, resistant to timing side-channel attacks.

## Example

```
Message:   Hello
c1:        5978cccd5432460f...
Decrypted: Hello
```

## Build

Requires GMP:
```bash
sudo apt install libgmp-dev
```

Then:
```bash
make
./elgamal_tests
```

## Design notes

- Message is imported to `mpz_t` via `mpz_import` before encryption, exported back to bytes via `mpz_export` after decryption
- Maximum message size is bounded by `p` (~64 bytes for 512-bit prime)
- 512-bit prime is sufficient for demonstration; production use requires 2048-bit minimum

## Part of

This is the encryption layer of a larger protocol combining ElGamal with Reed-Solomon error correction over UDP, targeting a real two-machine demonstration across separate networks.

## Security Disclaimer

This implementation is for educational purposes and protocol demonstration only. It is **not** production-secure for the following reasons:

- 512-bit prime is considered broken by modern standards (minimum 2048-bit for production)
- No message authentication — ciphertext is malleable
- Random seeding uses `time(NULL)` which is predictable; production requires a cryptographically secure RNG
- No padding scheme — textbook ElGamal is vulnerable to chosen-ciphertext attacks

Do not use this to protect real data.


## License

MIT
