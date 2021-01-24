//
// Created by Paz Lavi  on 22/01/2021.
//

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
    fprintf(stderr, "Usage: %s [-d public key] [-e private key][-f file name] [-s signature output file] \n", argv0);
    exit(EXIT_FAILURE);
}

// -f /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/temp.txt -s /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/signature.enc -e /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.private -d /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.public
int main(int argc, char **argv)
{

    int opt;
    char *privateKey = "rsa.private";
    char *publicKey = "rsa.public";
    char *signatureOutput = "signature.enc";
    char *fileName = "";


    while ((opt = getopt(argc, argv, "f:e:s:d:")) != -1)
    {

        switch (opt)
        {
            case 'f':
                fileName = optarg;
                break;
            case 'e':
                privateKey = optarg;
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


    signFile(fileName, signatureOutput, privateKey,publicKey);

    return 0;
}