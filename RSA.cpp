#include "RSA.h"




RSA::RSA() : gen(rd()){};



number RSA::generatePrime(int min, int max){
    std::uniform_int_distribution<number> dist(min, max);
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
    do{
    number p = generatePrime(2, 10000);
    number q = generatePrime(32, 20000);
    number phi = (p-1)*(q-1); 

    n = p * q; 

    number i = 2;

    while(gcd(i, phi) != 1){
        if(i >= phi){
            break;
        }
        i++;
    }

    e = i;

    d = modInverse(e, phi);
    
    } while(d > 10000000000000000); // to avoid 20-25 nums
}



number RSA::modInverse(number a, number b){     // Function, based on extended Euclidean algorithm. Returns one of Bezout coeffs.
    number r0 = a;
    number r = b;
    number q, r1, y1, x1;
    number x0 = 1, x = 0;
    number y0 = 0, y = 1;
    // a*x0 + b*y0 = 1
    
    while(r != 0){

        q = r0/r;

        r1 = r; //previous value of r
        r = r0 - q * r1; // new r
        r0 = r1; // new r0

        x1 = x;  //same alg, but diffrent vars
        x = x0 - q * x1;
        x0 = x1;

        // y1 = y;
        // y = y0 - q * y1;
        // y0 = y1;
        
    }
    

    return x0;
}



number RSA::modExp(number base, number exp, number mod){
    number result = 1;

    while (exp > 0) {
        if (exp % 2 == 1){                         
            result = (result * base) % mod;
            exp--;                                
        }                                            
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;

}



std::vector<number> RSA::encrypt(const std::string& message){
    std::vector<number> encrypted;

    for(char M : message){
        number m = alp.find(M);
        encrypted.push_back(modExp(m, e, n)); // m^e mod n
    }

    return encrypted;

}



std::string RSA::decrypt(const std::vector<number>& encrypted){
    std::string decrypted;
    number res;

    for(number m : encrypted){
        res = modExp(m, d, n);  // m^d mod n
        decrypted += alp[res];
    }
    return decrypted;
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