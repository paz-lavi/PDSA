//
// Created by Paz Lavi  on 23/01/2021.
//

#include "converters.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

const char zero[] = "\u200C";
const char one[] = "\u200D";

/* represent string array (chars) as bits array (binary , 0/1 array) */
void stringToBin(char *str, char **bin)
{
    //printf("\nstringToBin");
   // printf("\nstr = %s",str);
    int tempLen = strlen(str);
    int i, j, k = 0;

    *bin = calloc(8 * (tempLen + 1), sizeof(char));
    if (bin == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }


    for (j = 0; j < tempLen; j++)
    {
        for (i = 7; i >= 0; --i)
        {
            (*bin)[k++] = str[j] & (1 << i) ? '1' : '0';

        }
    }

}

/* convert bits array (binary 0/1 chars) to string array*/
void binToString(char **str, char *bin)
{
   // printf("\nstringToBin");
    long tempLen = strlen(bin);
    int i, j = 0;


    *str = calloc((tempLen) / 8 + 1, sizeof(char));
    if (*str == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    char charInBin[8], c;
    for (i = 0; i < tempLen / 8; i++)
    {
        strncpy(&charInBin[0], bin + (i * 8), 8);
        // printf("%s", charInBin);
        c = strtol(charInBin, 0, 2);
        (*str)[j++] = c;
    }
   // printf("\nstr = %s",*str);

}

/* convert bits array (binary) to zero width chars array (invisible chars)*/
void binToZeroWidth(char *bin, char **zeroWidth)
{
    int binLen = strlen(bin), i;
    *zeroWidth = calloc((binLen + 1) * 3, sizeof(char));
    if (*zeroWidth == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < binLen; i++)
    {
        strncat(&((*zeroWidth)[i * 3]), bin[i] == '1' ? one : zero, 3);
    }

}

/* convert zero width chars array (invisible chars) to bits array (binary 0/1 chars)*/
void zeroWidthToBin(char **bin, char *zeroWidth)
{
    int zeroWidthLen = strlen(zeroWidth), i;
    char c[4];
    *bin = calloc(((zeroWidthLen) / 3) + 1, sizeof(char));
    if (*bin == NULL)
    {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < zeroWidthLen / 3; i++)
    {
        strncpy(&c[0], &zeroWidth[i * 3], 3);
        (*bin)[i] = strcmp(c, zero) == 0 ? '0' : '1';
    }

}