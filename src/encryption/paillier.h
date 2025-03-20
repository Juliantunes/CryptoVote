//Header file for Pallier functions
//this file declares the functions but does not implement them

#ifndef PAILLIER_H
#define PAILLIER_H

#include <gmpxx.h>

// Struct for holding Paillier keys
struct PaillierKeys {
    mpz_class n, nSquared, g, lambda, mu;
};

// Function declarations
PaillierKeys generateKeys(int bitSize);

#endif // PAILLIER_H
