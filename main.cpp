#include "RSA.cpp"
#include "RSA.h"
#include <iostream>


int main() {
    RSA rsa(17, 151); // (277, 71)
    
    // Original message
    std::string message = "RSA";
    std::cout << "Original message: " << message << std::endl;
    
    // Encrypt the message
    std::vector<num> encrypted = rsa.encrypt(message);
    rsa.getPublicKey();
    rsa.getPrivateKey();
    std::cout << "Encrypted message: ";
    for (const auto& num : encrypted) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Decrypt the message
    std::string decrypted = rsa.decrypt(encrypted);
    std::cout << "Decrypted message: " << decrypted << std::endl;

    std::cout << "runtime = " << clock()/CLOCKS_PER_SEC << "sec."; 
    
    return 0;
}