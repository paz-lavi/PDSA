//
// Created by Paz Lavi  on 22/01/2021.
//

#include <stdlib.h>
#include "8BitsPrimes.h"
#define PRIMES_SIZE_8_BITS 23
const long primesList8Bits[] = {131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251};

long getRandom8BitsPrime()
{
    int i = rand() % PRIMES_SIZE_8_BITS ;
    return primesList8Bits[i];
}