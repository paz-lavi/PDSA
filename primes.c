//
// Created by Paz Lavi  on 22/01/2021.
//

#include "primes.h"
#include "8BitsPrimes.h"
#include "16BitsPrimes.h"
#include "32BitsPrimes.h"

long getRandomPrime(int bitSize)
{

    switch (bitSize)
    {
        case 8:
            return getRandom8BitsPrime();
        case 16:
            return getRandom16BitsPrime();
        case 32:
            return getRandom32BitsPrime();
        default:
            return -1;
    }
}