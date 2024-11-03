#pragma once

#include <iostream>
#include <cmath>
#include <random>
#include <string>
#include <vector>
#include <fstream>




typedef unsigned long long number;

std::string alp = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm .,:;''!?@#$%^&*()[]{}-+=1234567890";



class RSA {


    private:
        number n, e, d;
        std::random_device rd;
        std::mt19937 gen;
        number generatePrime(int min, int max);


    public:
        RSA();
        void generateKeys();
        bool isPrime(number num);
        number gcd(number a, number b);
        number modInverse(number a, number b);
        number modExp(number base, number exp, number mod);
        std::vector<number> encrypt(const std::string& message);
        std::string decrypt(const std::vector<number>& encrypted);
        void getPublicKey();
        void getPrivateKey();

};