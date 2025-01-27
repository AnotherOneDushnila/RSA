#include "RSA.cpp"
#include "RSA.h"




int main() {
    int mode;
    num p, q;
    std::string message;

    std::cout << "Enter prime number p: ";
    std::cin >> p;
    std::cout << "Enter prime number q: ";
    std::cin >> q;
    std::cout << std::endl;
    
    RSA rsa(p, q); // 877, 991 | 852889 703673

    std::cout << "Choose the way you'll hand over the message:" << std::endl <<
    "0. Write it down in terminal " << std::endl << "1. In file (you should enter the path)" << std::endl;
    std::cout << "Mode: ";
    std::cin >> mode;

    // Original message
    if(mode) {
        std::string path;
        std::cout << "Enter the path to the file:" << std::endl;
        std::cin >> path;
        std::cout << std::endl;
        message = rsa.getMessage(path);
    } else {
        std::cout << "Enter the message: \n";
        std::cin >> message;
    }
    
 
    std::cout << "Original message: " << message << "\n\n";
    
    // Encrypt the message
    std::vector<num> encrypted = rsa.encrypt(message);
    rsa.getPublicKey();
    rsa.getPrivateKey();
    rsa.getCipher(encrypted);

    std::cout << "Encrypted message: ";
    for (const auto& num : encrypted) {
        std::cout << num << " ";
    }
    std::cout << "\n\n";
    
    // Decrypt the message
    std::string decrypted = rsa.decrypt(encrypted);
    rsa.getDecryptedMessage(decrypted);
    std::cout << "Decrypted message: " << decrypted << std::endl;

    
    return 0;
}