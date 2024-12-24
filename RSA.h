#pragma once

#include <iostream>
#include <cmath>
#include <random>
#include <string>
#include <vector>
#include <fstream>




typedef unsigned long long num;

std::string alp = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm .,:;''!?@#$%^&*()[]{}-+=1234567890";



class RSA {


    private:

        num n, e, d;
        void generateKeys(num p, num q);
    


    public:

        RSA(num p, num q);
        ~RSA(){};
        bool isPrime(num num);
        num gcd(num a, num b);
        num modInverse(num a, num b);
        num modExp(num base, num exp, num mod);   
        std::vector<num> encrypt(const std::string& message);
        std::string decrypt(const std::vector<num>& encrypted);
        void getPublicKey();
        void getPrivateKey();

};