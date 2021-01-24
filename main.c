#include <stdio.h>
#include <stdlib.h>
#include "mainFunctions.h"

#define OPTION_ARGV_POS 1
#define FIRST_FILE_NAME_ARGV_POS 2
#define SECOND_FILE_NAME_ARGV_POS 3
#define THIRD_FILE_NAME_ARGV_POS 4

//  0 /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/temp.txt /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/signature.enc /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.private
//  -f /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/temp.txt -s /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/signature.enc -e /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.private
//  1 /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/temp.txt /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/signature.enc /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.public
//  2 /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.private /Users/pazlavi/Paz/dev/Afeka/Linux/DigitalSignature/rsa.public

int main2(int argc, char *argv[])
{

    int option;
    char *fileName1, *fileName2, *fileName3,*fileName4;
    if (argc == 4 || argc == 5)
    {
        option = atoi(argv[OPTION_ARGV_POS]);
        fileName1 = argv[FIRST_FILE_NAME_ARGV_POS];
        fileName2 = argv[SECOND_FILE_NAME_ARGV_POS];
        fileName4 = argv[SECOND_FILE_NAME_ARGV_POS];
        switch (option)
        {
            case 0:
                fileName3 = argv[THIRD_FILE_NAME_ARGV_POS];
                signFile(fileName1, fileName2, fileName3,fileName4);
                break;
            case 1:
                fileName3 = argv[THIRD_FILE_NAME_ARGV_POS];
                validateSignature(fileName1, fileName2, fileName3);
                break;
            case 2:
                generateKeyPair(fileName1, fileName2,32);
                break;
            default:
                printf("No option selected, bye :)");
                return 0;
        }
    } else if (argc > 3)
    {
        printf("Too many arguments supplied.\n");
        return 1;
    } else
    {
        printf("3 or 4 argument expected.\n");
        return 1;
    }
    return 0;
}
