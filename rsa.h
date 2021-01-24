//
// Created by Paz Lavi  on 16/01/2021.
//

#ifndef DIGITALSIGNATURE_RSA_H
#define DIGITALSIGNATURE_RSA_H

#include <stdbool.h>

#define BITS_SIZE 16

bool isPrimeChecker(int num);

bool checkIfPrime(int num);

long calculateGCD(long a, long b);

bool keyPairGenerator(int p, int q, int *resN, int *publicKeyRes, int *privateKKeyRes);

int find_d(int phi_n, int e);

int exponentMod(int base, unsigned int exponent, int modulo);

bool find_e(int phi_n, int *res_E);

long isValidSignature(long hash, long publicKey, long keyLength, long expectedCipher);

long encrypt(long plain, long privateKey, long keyLength);

long decrypt(long cipher, long publicKey, long keyLength);

long powMod(long A, long B, long C);

long multiplicativeInverse(long a, long b);

void keysGenerator(long *D, long *N, long *E, int bitSize);

#endif //DIGITALSIGNATURE_RSA_H
