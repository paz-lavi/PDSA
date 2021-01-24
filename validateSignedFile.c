//
// Created by Paz Lavi  on 24/01/2021.
//
// this program get a signed file path and will return if the file signature is valid
//

#include <stdio.h>
#include <stdlib.h>
#include "mainFunctions.h"
#include <unistd.h>
#include <string.h>

static void usage(const char *argv0)
{
    fprintf(stderr, "Usage: %s [-f file name]  \n", argv0);
    exit(EXIT_FAILURE);
}

// -f /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/sign_temp.txt
int main(int argc, char **argv)
{

    int opt;

    char *fileName = "";


    while ((opt = getopt(argc, argv, "f:")) != -1)
    {

        if (opt == 'f')
        {
            fileName = optarg;

        } else
        {
            usage(argv[0]);

        }
    }

    if (strcmp(fileName, "") == true)
    {
        fprintf(stderr, "File path missing - %s\n", fileName);
        usage(argv[0]);

    }

    validateSignedFile(fileName);

    return 0;
}