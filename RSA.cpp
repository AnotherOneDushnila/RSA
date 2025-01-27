#include "RSA.h"






RSA::RSA(num p, num q){
    
    if(!isPrime(p) || !isPrime(q)){
        throw std::invalid_argument("Numbers p and q must be prime!");
    }

    generateKeys(p, q);
}



bool RSA::isPrime(num number){

    if (number < 2){ 
        return false;
    }
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
    bool ContinueSearch = true;
    std::vector<unsigned int> FermatNumbers = {17, 257, 65537};

    num phi = (p-1)*(q-1); 

    n = p * q; 
    if (n < 88) {
        throw std::invalid_argument("n is too small, try to reset p and q");
    }

    e = 2;
    for(int f : FermatNumbers) {
        if (gcd(f, phi) == 1 && f < phi) {
            e = f;
            ContinueSearch = false;
        }
    }

    if(ContinueSearch){
        while(e < phi){
            if(gcd(e, phi) == 1){
                break;
            }
            else{
                e++;
            }
        } 
    }
    

    
    d = modInverse(e, phi);
    
}



num RSA::modInverse(num a, num b){// Function, based on extended Euclidean algorithm. Returns one of Bezout coeffs.
    long long r0 = a;
    long long r = b;
    long long q, r1, y1, x1;
    long long x0 = 1, x = 0;
    long long y0 = 0, y = 1;
    // a*x0 + b*y0 = 1  

    while(r != 0) {

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

    while(x0 < 0){
        x0 += b; //b = phi | ax = 1 mod b => ax + akb = 1 mod b
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



std::string RSA::getMessage(std::string& path){
    std::string line;
    std::string res;
    std::ifstream in(path);

    if(in.is_open()){
        while (std::getline(in, line)){
            res += line;
        }
    }
    
    in.close();

    return res;
}



void RSA::getCipher(std::vector<num>& encrypted){
    std::ofstream file("ciphertext.txt");

    for(num chpr : encrypted){
        file << chpr << " ";
    }

    file.close();
}



void RSA::getDecryptedMessage(std::string& decrypted){
    std::ofstream file("decrypted_m.txt");

    for(char ch : decrypted){
        file << ch;
    }

    file.close();

}