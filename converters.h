//
// Created by Paz Lavi  on 23/01/2021.
//

#ifndef DIGITALSIGNATURE_CONVERTERS_H
#define DIGITALSIGNATURE_CONVERTERS_H

void stringToBin(char* str , char** bin);
void binToString(char** str , char* bin);
void zeroWidthToBin(char **bin, char *zeroWidth);
void binToZeroWidth(char *bin, char **zeroWidth);
#endif //DIGITALSIGNATURE_CONVERTERS_H
