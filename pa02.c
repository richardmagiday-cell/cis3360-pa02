/*============================================================================
| Assignment: pa02 - Encrypting a plaintext file using the Hill cipher
|
| Author: Richard Magiday
| Language: C
| ================= COMPILATION & EXECUTION =================
|
| ---- Linux / Eustis ----
|   gcc -o pa02 pa02.c
|   ./pa02 k1.txt p1.txt > stu1Output.txt
|   diff --ignore-blank-lines stu1Output.txt base1.txt
|
| ---- Windows PowerShell (MinGW gcc installed) ----
|   gcc -o pa02.exe pa02.c
|   .\pa02.exe k1.txt p1.txt
|   cmd /c fc stu1Output.txt base1.txt
|
| ===========================================================
|
| where kX.txt is the keytext file
| and pX.txt is plaintext file
|
| Class: CIS3360 - Security in Computing - Summer 2025
| Instructor: McAlpin
| Due Date: 03/25/26
+===========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_N 9
#define MAX_TEXT 10000 // max plaintext size

void print_80_cols(char *s);
int read_key_file(char *filename, int key[MAX_N][MAX_N], int *n_out);
int read_plaintext_file(char *filename, char plaintext[MAX_TEXT], int n);
void hill_encrypt(int key[MAX_N][MAX_N], int n, char *plaintext, char *ciphertext);

int main(int argc, char *argv[])
{
    // ensure exactly two command line arguments
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <keyfile> <plaintextfile>\n", argv[0]);
        return 1;
    }

    char *keyfile = argv[1];
    char *ptfile = argv[2];

    int key[MAX_N][MAX_N];
    int n = 0;

    // read key matrix from file
    if (!read_key_file(keyfile, key, &n))
    {
        fprintf(stderr, "Error: could not read key file.\n");
        return 1;
    }

    // echo key matrix to stdout
    printf("\nKey matrix:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%4d", key[i][j]);
        }
        printf("\n");
    }

    char plaintext[MAX_TEXT];

    // read and process plaintext
    int pt_len = read_plaintext_file(ptfile, plaintext, n);

    if (pt_len < 0)
    {
        fprintf(stderr, "Error: could not read plaintext file.\n");
        return 1;
    }

    // echo processed plaintext
    printf("\nPlaintext:\n");
    print_80_cols(plaintext);

    char ciphertext[MAX_TEXT];

    // encrypt plaintext using hill cipher
    hill_encrypt(key, n, plaintext, ciphertext);

    // output ciphertext in 80-column format
    printf("\nCiphertext:\n");
    print_80_cols(ciphertext);

    return 0;
}

// reads key matrix file into 2D array
int read_key_file(char *filename, int key[MAX_N][MAX_N], int *n_out)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return 0;

    int n;

    // first value is matrix size
    if (fscanf(fp, "%d", &n) != 1)
    {
        fclose(fp);
        return 0;
    }

    // valid key size is 2 through 9
    if (n <= 1 || n >= 10)
    {
        fclose(fp);
        return 0;
    }

    // read n x n integers
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (fscanf(fp, "%d", &key[i][j]) != 1)
            {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    *n_out = n;
    return 1;
}

// reads plaintext, keeps letters only, converts to lowercase, pads with 'x'
int read_plaintext_file(char *filename, char plaintext[MAX_TEXT], int n)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return -1;

    int len = 0;
    int ch;

    // read file character by character
    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalpha((unsigned char)ch)) // keep letters only
        {
            if (len >= MAX_TEXT - 1)
            {
                fclose(fp);
                return -1;
            }

            plaintext[len++] = (char)tolower((unsigned char)ch); // convert to lowercase
        }
    }

    fclose(fp);

    // pad with 'x' until length is multiple of n
    while (len % n != 0)
    {
        if (len >= MAX_TEXT - 1)
            return -1;

        plaintext[len++] = 'x';
    }

    plaintext[len] = '\0';
    return len;
}

// performs Hill cipher matrix multiplication
void hill_encrypt(int key[MAX_N][MAX_N], int n, char *plaintext, char *ciphertext)
{
    int len = 0;

    // determine plaintext length
    while (plaintext[len] != '\0')
        len++;

    // process in blocks of size n
    for (int block = 0; block < len; block += n)
    {
        for (int i = 0; i < n; i++)
        {
            long sum = 0;

            // matrix multiplication: row * column
            for (int j = 0; j < n; j++)
            {
                sum += key[i][j] * (plaintext[block + j] - 'a');
            }

            int c = sum % 26; // mod 26 for alphabet
            if (c < 0)
                c += 26;

            ciphertext[block + i] = 'a' + c;
        }
    }

    ciphertext[len] = '\0';
}

// prints string in rows of exactly 80 characters
void print_80_cols(char *s)
{
    int i = 0;

    while (s[i] != '\0')
    {
        putchar(s[i]);
        i++;

        if (i % 80 == 0)
            putchar('\n');
    }

    // ensure newline at end
    if (i % 80 != 0 || i == 0)
        putchar('\n');
}

/*=============================================================================
| I Richard Magiday (ri610670) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/