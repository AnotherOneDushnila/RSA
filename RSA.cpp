#include "RSA.h"





RSA::RSA() : gen(rd()){};



number RSA::generatePrime(int min, int max){}



bool RSA::isPrime(number num){

    if (num < 2) 
        return false;
    for (number i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) 
            return false;
    }
    return true;

}



number RSA::gcd(number a, number b){

    if(b == 0) 
        return a;

    while(b){
        a %= b;
        std::swap(a, b);
    }

    return a;
}



void RSA::generateKeys(){}



number RSA::modInverse(number a, number b){};



number RSA::modExp(number base, number exp, number mod){};



std::vector<number> RSA::encrypt(const std::string& message){}



std::string RSA::decrypt(const std::vector<number>& encrypted){}



void RSA::getPublicKey(){

    std::ofstream file("PublicKey.txt");

    file << e << std::endl << n;

    file.close();

}



void RSA::getPrivateKey(){

    std::ofstream file("PrivateKey.txt");

    file << d << std::endl << n;

    file.close();

}