//
// Created by Paz Lavi  on 16/01/2021.
//
#include <stdio.h>
#include <math.h>
#include "rsa.h"
#include "primes.h"



/* check if a provided number is a prime*/
bool checkIfPrime(int num)
{

    if (num == 0 || num == 1)
    {
        return false;
    } else if (num == 2 || num == 3)
    {
        return true;
    } else
    {
        return isPrimeChecker(num);
    }
}

/* check if prime*/
bool isPrimeChecker(int num)
{
    int i, n = floor(sqrt(num));
    bool prime = true;
    for (i = 2; i <= n; i++)
    {
        if (num % i == 0)
        {
            prime = false;
            break;
        }
    }


    return prime;
}

/* calculate GCD of 2 numbers  GCD for both positive and negative numbers in recursion */
long calculateGCD(long a, long b)
{
    long n1 = (a > 0) ? a : -a;
    long n2 = (b > 0) ? b : -b;
    long reminder;
    if (n1 > n2)
    {
        reminder = n1;
        n1 = n2;
        n2 = reminder;
    }
    while (true)
    {
        reminder = n1 % n2;
        if (reminder == 0)
        {
            return n2;
        }
        n1 = n2;
        n2 = reminder;
    }
}


long decrypt(long cipher, long publicKey, long keyLength)
{
    return powMod(cipher, publicKey, keyLength);

}

long encrypt(long plain, long privateKey, long keyLength)
{

    return powMod(plain, privateKey, keyLength);

}

long isValidSignature(long hash, long publicKey, long keyLength, long expectedCipher)
{
    printf("publicKey = %ld , keyLength = %ld , expectedCipher = %ld ," ,publicKey,keyLength,expectedCipher);
    long d = decrypt(expectedCipher, publicKey, keyLength);
    printf("hash = %ld , d = %ld",hash,d);
    return hash == decrypt(expectedCipher, publicKey, keyLength);
}


long multiplicativeInverse(long a, long b)
{
    long b0 = b, t, q;
    long x0 = 0, x1 = 1;
    if (b == 1) return 1;
    while (a > 1)
    {
        q = a / b;
        t = b, b = a % b, a = t;
        t = x0, x0 = x1 - q * x0, x1 = t;
    }
    if (x1 < 0) x1 += b0;
    return x1;
}

long powMod(long A, long B, long C)
{

    // Base cases
    if (A == 0)
        return 0;
    if (B == 0)
        return 1;

    // If B is even
    long y;
    if (B % 2 == 0)
    {
        y = powMod(A, B / 2, C);
        y = (y * y) % C;
    }

        // If B is odd
    else
    {
        y = A % C;
        y = (y * powMod(A, B - 1, C) % C) % C;
    }

    return ((y + C) % C);
}

/*keyS generation algorithm: https://www.di-mgt.com.au/rsa_alg.html */
void keysGenerator(long *D, long *N, long *E, int bitSize)
{
    printf("\nkeysGenerator");
    long e = getRandomPrime(8);
    long p, q;

    do
    {
        p = getRandomPrime(bitSize / 2);
    } while (p % e == 1);

    do
    {
        q = getRandomPrime(bitSize / 2);
    } while (q % e == 1);

    long n = p * q;
    long phi_n = (p - 1) * (q - 1);
    long d = multiplicativeInverse(e, phi_n);


    *E = e;
    *D = d;
    *N = n;
}