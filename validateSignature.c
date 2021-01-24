
//
// Created by Paz Lavi  on 22/01/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include "mainFunctions.h"
#include <unistd.h>
#include <string.h>

static void usage(const char *argv0)
{
    fprintf(stderr, "Usage: %s [-d public key][-f file name] [-s signature file] \n", argv0);
    exit(EXIT_FAILURE);
}

// -f /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/temp.txt  -s /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/signature.enc -d /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.public
int main(int argc, char **argv)
{

    int opt;
    char *publicKey = "rsa.public";
    char *signatureOutput = "signature.enc";
    char *fileName = "";


    while ((opt = getopt(argc, argv, "f:d:s:")) != -1)
    {

        switch (opt)
        {
            case 'f':
                fileName = optarg;
                break;
            case 'd':
                publicKey = optarg;
                break;
            case 's':
                signatureOutput = optarg;
                break;
            default:
                usage(argv[0]);
        }
    }

    if (strcmp(fileName, "") == true)
    {
        fprintf(stderr, "File path missing - %s\n", fileName);
        usage(argv[0]);

    }

    validateSignature(fileName, signatureOutput, publicKey);

    return 0;
}