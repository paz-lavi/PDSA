//
// Created by Paz Lavi  on 22/01/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include "mainFunctions.h"
#include <unistd.h>

static void usage(const char *argv0)
{
    fprintf(stderr, "Usage: %s [-e private key][-d public key] [-b bits size]\n", argv0);
    exit(EXIT_FAILURE);
}

void isValidBits(int bitSize)
{
    if (!(bitSize == 16 || bitSize == 32 || bitSize == 64))
    {
        fprintf(stderr, "Not valid bits size!\n Optional sizes: 16, 32, 64");
        exit(EXIT_FAILURE);
    }

}

// -e /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.private -d /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.public -b 32
int main(int argc, char **argv)
{

    int opt;
    char *privateKey = "rsa.private";
    char *publicKey = "rsa.public";
    int bitSize = 32;


    while ((opt = getopt(argc, argv, "e:d:b:")) != -1)
    {

        switch (opt)
        {
            case 'e':
                privateKey = optarg;
                break;
            case 'd':
                publicKey = optarg;
                break;
            case 'b':
                bitSize = atoi(optarg);
                break;
            default:
                usage(argv[0]);
        }
    }

    isValidBits(bitSize);
    generateKeyPair(privateKey, publicKey, bitSize);

    return 0;
}