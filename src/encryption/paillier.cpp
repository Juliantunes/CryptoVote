//implementation of encryption,decryption, homomorphic addition


#include <iostream>
#include <gmpxx.h>

// Struct for holding Paillier keys
struct PaillierKeys {
    mpz_class n, nSquared, g, lambda, mu;
};

// 🔹 Helper Functions
mpz_class L_function(const mpz_class& x, const mpz_class& n); // Computes L(x) = (x - 1) / n
mpz_class mod_inverse(const mpz_class& a, const mpz_class& n); // Computes modular inverse
mpz_class generate_random_r(const mpz_class& n); // Generates a random r in ℤₙ*

// 🔹 Core Paillier Functions
PaillierKeys generateKeys(int bitSize); // Generates keys (public + private)
mpz_class encryptVote(const mpz_class& vote, const PaillierKeys& keys); // Encrypts a vote
mpz_class decryptVote(const mpz_class& ciphertext, const PaillierKeys& keys); // Decrypts a vote
mpz_class addEncryptedTallies(const mpz_class& c1, const mpz_class& c2, const PaillierKeys& keys); // Adds encrypted votes
void simulateVoting(); // Runs a demo

// 🔹 Main Function
int main() {
    simulateVoting();
    return 0;
}