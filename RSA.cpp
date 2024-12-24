#include "RSA.h"




// RSA::RSA() : gen(rd()){};

RSA::RSA(num p, num q){
    generateKeys(p, q);
}



bool RSA::isPrime(num number){

    if (number < 2) 
        return false;
    for (num i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) 
            return false;
    }
    return true;

}



num RSA::gcd(num a, num b){

    while(b > 0){
        a %= b;
        std::swap(a, b); 
    }

    return a;
}



void RSA::generateKeys(num p, num q){
    std::vector<num> res;
    num phi = (p-1)*(q-1); 

    n = p * q; 
    if (n < 88) {
        throw std::invalid_argument("n is too small, try to reset p and q");
    }

    e = 2;

    while(e < phi){
        if(gcd(e, phi) == 1){
            break;
        }
        else{
            e++;
        }
    } 

    

    d = modInverse(e, phi);
    
}



num RSA::modInverse(num a, num b){     // Function, based on extended Euclidean algorithm. Returns one of Bezout coeffs.
    num r0 = a;
    num r = b;
    num q, r1, y1, x1;
    num x0 = 1, x = 0;
    num y0 = 0, y = 1;
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



num RSA::modExp(num base, num exp, num mod){
    num result = 1;

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



std::vector<num> RSA::encrypt(const std::string& message){
    std::vector<num> encrypted;

    for(char M : message){
        num m = alp.find(M);
        encrypted.push_back(modExp(m, e, n)); // m^e mod n
    }

    return encrypted;

}



std::string RSA::decrypt(const std::vector<num>& encrypted){
    std::string decrypted;
    num res;

    for(num m : encrypted){
        
        res = modExp(m, d, n);

        decrypted += alp[res];
    }
    return decrypted;
}



// std::vector<number> RSA::attack(const std::vector<number> pubKey){

// }


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