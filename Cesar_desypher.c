#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void caesar_decrypt(char *input, char *output, int key)
{
    int len = strlen(input);
    for (int i = 0; i < len; i++)
    {
        char c = input[i];
        if (isupper(c))
        {
            output[i] = (c - 'A' - key + 26) % 26 + 'A';
        }
        else if (islower(c))
        {
            output[i] = (c - 'a' - key + 26) % 26 + 'a';
        }
        else
        {
            output[i] = c; // Интервали и други символи остават в оригиналния си вид
        }
    }
    output[len] = '\0';
}

void bruteforce_attack(char *cipher)
{
    char buffer[256];
    printf("--- BRUTE FORCE REPORT ---\n");
    for (int k = 1; k < 26; k++)
    {
        caesar_decrypt(cipher, buffer, k);
        printf("[Key %02d]: %s\n", k, buffer);
    }
}

int main()
{
    char cipher[256];
    printf("Text: ");
    fgets(cipher, sizeof(cipher), stdin);
    bruteforce_attack(cipher);
    return 0;
}