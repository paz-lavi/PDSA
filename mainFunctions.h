//
// Created by Paz Lavi  on 16/01/2021.
//

#ifndef DIGITALSIGNATURE_MAINFUNCTIONS_H
#define DIGITALSIGNATURE_MAINFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>

bool generateKeyPair(char *privateFile, char *publicFile, int bitSize);

void saveKeyToFile(long key, long keyLength, char *filename);

void readKeyFromFile(long *key, long *keyLength, char *filename);

void writeSignatureToFile(long signature, char *fileName);

long readSignatureFromFile(char *fileName);

void createFileWithSignature(char *fileToSign, char **encryptedString);

bool validateSignature(char *fileToValidate, char *sigantureFileName, char *publicKeyFileName);

bool signFile(char *fileToSign, char *signatureFileName, char *privateKeyFileName, char *publicKeyFileName);

void encodeZeroWidth(long signature, long keyLength, long publicKey, char **str);

void decodeSignature(char *encoded, long *signature, long *keyLength, long *publicKey);

void validateSignedFile(char *filePath);

void parseSignature(char *decoded, long *signature, long *keyLength, long *publicKey);

void copyFile(FILE* src, FILE* dest);
#endif //DIGITALSIGNATURE_MAINFUNCTIONS_H
