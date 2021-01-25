//
// Created by Paz Lavi  on 16/01/2021.
//
#include "mainFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "rsa.h"
#include "hashing.h"
#include <libgen.h>
#include "converters.h"

/* generate key pair, public and private and saved them the the specified files*/
bool generateKeyPair(char *privateFile, char *publicFile, int bitSize)
{
    time_t t;
    srand((unsigned) time(&t));

    long public, private, keyLen;

    keysGenerator(&public, &keyLen, &private, bitSize);

    saveKeyToFile(private, keyLen, privateFile);
    saveKeyToFile(public, keyLen, publicFile);

    char chr;

    printf("Print keys to screen? [Y/N] ");
    scanf("%c", &chr);
    if (chr == 'Y' || chr == 'y')
    {
        printf("\npublic key: %ld\n", public);
        printf("\nprivate key: %ld\n", private);
        printf("\nkey length: %ld\n", keyLen);
    }


    return true;
}

/*save a key to file*/
void saveKeyToFile(long key, long keyLength, char *filename)
{
    FILE *keyFile = fopen(filename, "w+");
    assert(keyFile);
    fprintf(keyFile, "%ld %ld", keyLength, key);
    fclose(keyFile);
}

/*read a key from file*/
void readKeyFromFile(long *key, long *keyLength, char *filename)
{


    FILE *keyFile = fopen(filename, "r");
    assert(keyFile);
    fscanf(keyFile, "%ld %ld", keyLength, key);
    fclose(keyFile);
}

/* write a signature to file*/
void writeSignatureToFile(long signature, char *fileName)
{

    FILE *input;
    if ((input = fopen(fileName, "w+")) == NULL)
    {
        printf("Error - Couldn't open the file");
        return;
    }
    fprintf(input, "%ld\n", signature);
    fclose(input);

}

/* read Signature From File*/
long readSignatureFromFile(char *fileName)
{
    FILE *input;
    long signature;
    if ((input = fopen(fileName, "r")) == NULL)
    {
        printf("Error - Couldn't open the file");
        return 1;
    }
    fscanf(input, "%ld", &signature);
    fclose(input);
    return signature;
}

/* create a signed file. write the signature to file with invisible characters */
void createFileWithSignature(char *fileToSign, char **encryptedString)
{
    char *ts1 = strdup(fileToSign);
    char *ts2 = strdup(fileToSign);

    char *dir = dirname(ts1);

    char *filename = basename(ts2);

    char outputFilePath[200];
    int i;
    for (i = 0; i < 200; i++)
    {
        outputFilePath[i] = '\0';
    }


    strcat(outputFilePath, dir);
    strcat(outputFilePath, "/sign_");
    strcat(outputFilePath, filename);

    FILE *output;
    if ((output = fopen(outputFilePath, "w+")) == NULL)
    {
        printf("Error - Couldn't open the file: %s", outputFilePath);
        return;
    }

    FILE *input;
    if ((input = fopen(fileToSign, "r")) == NULL)
    {
        printf("Error - Couldn't open the file: %s", fileToSign);
        return;
    }

    fprintf(output, "Singed with P-DSA!%s! Use our CLI command to validate the signature\n", *encryptedString);

    copyFile(input, output);

    fclose(input);
    fclose(output);


}

/* sing on file. calculate the signature, encrypt it to non visible characters and write it to a new file*/
bool signFile(char *fileToSign, char *signatureFileName, char *privateKeyFileName, char *publicKeyFileName)
{
    char *str = NULL;
    FILE *input;
    long hash, privateK, keyLength, publicKey;
    if ((input = fopen(fileToSign, "r")) == NULL)
    {
        printf("Error - Couldn't open the file111\n");
        return false;
    }
    hash = hashFile(input);
    fclose(input);
    readKeyFromFile(&privateK, &keyLength, privateKeyFileName);
    long e = encrypt(hash, privateK, keyLength);
    readKeyFromFile(&publicKey, &keyLength, publicKeyFileName);
    writeSignatureToFile(e, signatureFileName);

    encodeZeroWidth(e, keyLength, publicKey, &str);
    createFileWithSignature(fileToSign, &str);

    free(str);
    return true;
}

/*check if signature is valid for a plain text file (original file! not signed file)*/
bool validateSignature(char *fileToValidate, char *signatureFileName, char *publicKeyFileName)
{
    FILE *input;
    long hash, publicK, keyLength, signature;
    if ((input = fopen(fileToValidate, "r")) == NULL)
    {
        printf("Error - Couldn't open the file\n");
        return false;
    }
    hash = hashFile(input);
    readKeyFromFile(&publicK, &keyLength, publicKeyFileName);
    signature = readSignatureFromFile(signatureFileName);

    if (isValidSignature(hash, publicK, keyLength, signature))
    {
        printf("Valid signature :)\n");
    } else
    {
        printf("Not a valid signature :(\n");
    }
    return true;
}

/*encode the signature to a non visible characters*/
void encodeZeroWidth(long signature, long keyLength, long publicKey, char **str)
{
    char temp[1000], *bin, *fromBin = NULL,  *fromZero;
    sprintf(temp, "signature:%ld$keyLength:%ld$publicKey:%ld$", signature, keyLength, publicKey);
    stringToBin(&temp[0], &bin);
    binToZeroWidth(bin, str);

    zeroWidthToBin(&fromZero, *str);

    free(bin);
    free(fromZero);
    free(fromBin);
}

/* validate signed file. read encrypted signature, decode it and validate file*/
void validateSignedFile(char *filePath)
{
    char *encodedSignature = NULL;
    long signature, keyLength, publicKey, hash;

    size_t len = 0;
    FILE *signedFile = fopen(filePath, "r");
    assert(signedFile);
    if (getline(&encodedSignature, &len, signedFile) == -1)  // read encrypted signature from the file
    {
        printf("Error - Couldn't read signature from the file: %s ", filePath);
        exit(EXIT_FAILURE);
    }

    decodeSignature(encodedSignature, &signature, &keyLength, &publicKey);  // decode encrypted signature

    FILE *tempOriginalFile = tmpfile();
    if (tempOriginalFile == NULL)
    {
        printf("Unable to create temp file");
        exit(EXIT_FAILURE);
    }
    copyFile(signedFile, tempOriginalFile);
    hash = hashFile(tempOriginalFile);

    if (isValidSignature(hash, publicKey, keyLength, signature))
    {
        printf("Valid signature :)\n");
    } else
    {
        printf("Not a valid signature :(\n");
    }

    fclose(signedFile);
}

/* decode encoded signature */
void decodeSignature(char *encoded, long *signature, long *keyLength, long *publicKey)
{
    char *bin, *plain;
    //printf("\encoded = %s",&encoded[0]);

    zeroWidthToBin(&bin, strtok(&encoded[strlen("Singed with P-DSA!")], "!"));
    //zeroWidthToBin(&bin, &encoded[strlen("Singed with P-DSA!")]);
    //printf("\nbin = %s",&bin[0]);
    binToString(&plain, &bin[0]);
   // printf("\nplain = %s",&plain[0]);

    parseSignature(plain, signature, keyLength, publicKey);
    free(bin);
    free(plain);


}

/* parse signature content*/
void parseSignature(char *decoded, long *signature, long *keyLength, long *publicKey)
{
    char *token, *ptr;
    char *rest = decoded;
    int i = 0;

    while ((token = strtok_r(rest, "$", &rest)))
    {
        //printf("\nrest = %s, decode = %s",rest,decoded);

        switch (i++)
        {
            case 0:
                *signature = strtol(&token[strlen("signature:")], &ptr, 10);
                //printf("\nsignature: %ld",*signature);
                break;
            case 1:
                *keyLength = strtol(&token[strlen("keyLength:")], &ptr, 10);
               // printf("\nkeyLength: %ld",*keyLength);

                break;
            case 2:
                *publicKey = strtol(&token[strlen("publicKey:")], &ptr, 10);
                //printf("\npublicKey: %ld",*publicKey);

                break;

        }
    }
}


/* copy file content to another file. provide 2 open files. the files will not closed!*/
void copyFile(FILE *src, FILE *dest)
{
    // Read contents from file
    char c;
    c = fgetc(src);

    while (c != EOF)
    {
        fputc(c, dest);
        c = fgetc(src);
    }

}
