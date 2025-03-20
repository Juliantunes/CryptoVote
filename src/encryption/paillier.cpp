//implementation of encryption,decryption, homomorphic addition


#include "paillier.h"
#include <iostream>
#include <gmpxx.h>
#include <random>
#include <ctime>

using namespace std;

// Function to generate Paillier keys
PaillierKeys generateKeys(int bitSize) {
    PaillierKeys keys;
    gmp_randstate_t randState;  // Define GMP random state
    gmp_randinit_default(randState);  // Initialize random state
    gmp_randseed_ui(randState, time(NULL));  // Seed with current time

    // Generate large prime numbers p and q
    mpz_class p, q;
    mpz_urandomb(p.get_mpz_t(), randState, bitSize / 2);
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());

    mpz_urandomb(q.get_mpz_t(), randState, bitSize / 2);
    mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());

    // Compute n = p * q and n^2
    keys.n = p * q;
    keys.nSquared = keys.n * keys.n;

    // Set g = n + 1 (simplified)
    keys.g = keys.n + 1;

    // Compute lambda = lcm(p-1, q-1)
    mpz_class p1 = p - 1, q1 = q - 1;
    mpz_class gcd;
    mpz_gcd(gcd.get_mpz_t(), p1.get_mpz_t(), q1.get_mpz_t());
    keys.lambda = (p1 * q1) / gcd;

    // Compute mu = (L(g^lambda mod n^2))^(-1) mod n
    mpz_class gLambda;
    mpz_powm(gLambda.get_mpz_t(), keys.g.get_mpz_t(), keys.lambda.get_mpz_t(), keys.nSquared.get_mpz_t());

    mpz_class L;
    L = (gLambda - 1) / keys.n;
    mpz_invert(keys.mu.get_mpz_t(), L.get_mpz_t(), keys.n.get_mpz_t());

    // GMP random state
    gmp_randclear(randState);

    return keys; 
}