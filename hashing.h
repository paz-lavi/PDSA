//
// Created by Paz Lavi  on 16/01/2021.
//

#ifndef DIGITALSIGNATURE_HASHING_H
#define DIGITALSIGNATURE_HASHING_H

#include <stdio.h>
#include <string.h>


int hashFile(FILE *input);

int foldFile(FILE *pFile, char *numberString);
int sfold(char* s, int M);
int foldFileV2(FILE *pFile);
#endif //DIGITALSIGNATURE_HASHING_H
