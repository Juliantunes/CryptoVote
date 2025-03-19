#include <iostream>
#include <gmpxx.h>

// Struct for holding Paillier keys
struct PaillierKeys {
    mpz_class n, nSquared, g, lambda, mu;
};

// L function: L(x) = (x - 1) / n
mpz_class L_function(const mpz_class& x, const mpz_class& n) {
    return (x - 1) / n;
}

// Compute modular inverse
mpz_class mod_inverse(const mpz_class& a, const mpz_class& n) {
    mpz_class result;
    mpz_invert(result.get_mpz_t(), a.get_mpz_t(), n.get_mpz_t());
    return result;
}

// Key Generation
PaillierKeys generateKeys(int bitSize) {
    gmp_randclass randGen(gmp_randinit_mt);
    randGen.seed(time(NULL));

    mpz_class p = randGen.get_z_bits(bitSize / 2);
    mpz_class q = randGen.get_z_bits(bitSize / 2);

    // Ensure p and q are prime
    mpz_nextprime(p.get_mpz_t(), p.get_mpz_t());
    mpz_nextprime(q.get_mpz_t(), q.get_mpz_t());

    PaillierKeys keys;
    keys.n = p * q;
    keys.nSquared = keys.n * keys.n;
    keys.g = keys.n + 1; // Common choice for g

    // Compute lambda = lcm(p-1, q-1)
    mpz_class p1 = p - 1, q1 = q - 1;
    keys.lambda = (p1 * q1) / gcd(p1, q1);

    // Compute μ = (L(g^λ mod n^2))^{-1} mod n
    mpz_class g_lambda;
    mpz_powm(g_lambda.get_mpz_t(), keys.g.get_mpz_t(), keys.lambda.get_mpz_t(), keys.nSquared.get_mpz_t());

    mpz_class Lg_lambda = L_function(g_lambda, keys.n);
    keys.mu = mod_inverse(Lg_lambda, keys.n);

    return keys;
}

// 🔹 Main Function
int main() {
    std::cout << "🔹 Generating Paillier Keys...\n";
    PaillierKeys keys = generateKeys(512);

    std::cout << "🔹 Public Key (n): " << keys.n << "\n";
    std::cout << "🔹 Private Key (lambda): " << keys.lambda << "\n";
    std::cout << "🔹 μ: " << keys.mu << "\n";

    return 0;
}