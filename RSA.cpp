#include "RSA.h"




RSA::RSA() : gen(rd()){};



number RSA::generatePrime(int min, int max){
    std::uniform_int_distribution<long long> dist(min, max);
    number num;

    do{
        num = dist(gen);
    } while(!isPrime(num));

    return num;
    
}



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

    while(b > 0){
        a %= b;
        std::swap(a, b); 
    }

    return a;
}



void RSA::generateKeys(){
    std::uniform_int_distribution<> dist(0,5);

    number p = generatePrime(500, 1000);
    number q = generatePrime(1000, 2000);
    number phi = (p-1)*(q-1);

    n = p * q;


    const std::vector<long long> common_e = {65537, 257, 17};

    e = common_e[dist(gen)];

    d = modInverse(e, phi);
}



number RSA::modInverse(number a, number b){} // there will be something like extended Euclidean algorithm



number RSA::modExp(number base, number exp, number mod){
    number result = 1;

    while (exp > 0) {
        if (exp % 2 == 1){                         
            result = (result * base) % mod;
            n--;                                
        }                                            
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;

}



std::vector<number> RSA::encrypt(const std::string& message){
    std::vector<number> encrypted;

    for(char M : message){
        number ind = alp.find(M);
        encrypted.push_back(modExp(M, e, n)); // M^e mod n
    }

    return encrypted;

}



std::string RSA::decrypt(const std::vector<number>& encrypted){
    std::string decrypted;

}



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