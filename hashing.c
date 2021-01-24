//
// Created by Paz Lavi  on 16/01/2021.
//

#include <stdbool.h>
#include <stdlib.h>
#include "hashing.h"
#include <stdlib.h>
#include "mainFunctions.h"

#define FOLDING_DIGITS_COUNT 5
#define FOLDING_MOD 100000

int hashFile(FILE *input)
{
    FILE *ascii = tmpfile();
    if (ascii == NULL)
    {
        printf("Unable to create temp file");
        return EXIT_FAILURE;
    } else
    {

        char *lineNumberString = (char *) malloc(sizeof(char) * FOLDING_DIGITS_COUNT);

        fseek(input, 0, SEEK_SET);
        copyFile(input, ascii);
        fseek(ascii, 0, SEEK_SET);

        //int res = foldFile(ascii, lineNumberString);
        free(lineNumberString);
        int res = foldFileV2(ascii);
        return res;
    }
}


int foldFile(FILE *pFile, char *numberString)
{
    bool hasNext = true;
    char number;
    int hashResult = 0;
    int numberIndex = 0;
int i;

    while (hasNext)
    {

        for(i = 0 ; i < FOLDING_DIGITS_COUNT ; i++){
            number = fgetc(pFile);
            if (number == EOF)
            {
                hasNext = false;
                break;
            }
            numberString[numberIndex] = number;

        }
        hashResult = (hashResult + atoi(numberString)) ;


        number = fgetc(pFile);
        if (number == EOF)
        {
            hashResult = (hashResult + atoi(numberString)) ;
            hasNext = false;
        }
        numberString[numberIndex] = number;
        if (numberIndex == FOLDING_DIGITS_COUNT - 1)
        {
            hashResult = (hashResult + atoi(numberString)) ;
            numberIndex = 0;
        } else
        {
            numberIndex += 1;
        }
    }
    return hashResult % FOLDING_MOD;
}
int sfold(char* s, int M) {
//    long sum = 0, mul = 1;
//    for (int i = 0; i < strlen(s); i++) {
//        mul = (i % 4 == 0) ? 1 : mul * 256;
//        //sum += (*s)[i] * mul;
//    }
//    return (int)(abs(sum) % FOLDING_MOD);
    return 1;
}

int foldFileV2(FILE *pFile) {
    bool hasNext = true;
    long sum = 0, mul = 1;
    int i=0;
    char number;
    while (hasNext){
        number = fgetc(pFile);
        if (number == EOF)
        {
            hasNext = false;
        }
        mul = (i++ % 4 == 0) ? 1 : mul * 256;
        sum += number * mul;

    }
//    for (int i = 0; i < strlen(s); i++) {
//        mul = (i % 4 == 0) ? 1 : mul * 256;
//        sum += (*s)[i] * mul;
//    }
    return (int)(labs(sum) % FOLDING_MOD);
}