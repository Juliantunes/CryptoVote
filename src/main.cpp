//main file that runs voting system

#include <iostream>
#include "encryption/paillier.h"

using namespace std;

int main() {
    // Generate keys
    PaillierKeys keys = generateKeys(1024);
    cout << "Keys generated" << endl;

    // Print the keys for verification
    cout << "Public Key (n): " << keys.n << endl;
    cout << "Public Key (g): " << keys.g << endl;
    cout << "Private Key (lambda): " << keys.lambda << endl;
    cout << "Private Key (mu): " << keys.mu << endl;

    return 0;
}


