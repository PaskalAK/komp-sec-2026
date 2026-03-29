#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char caesar_encrypt_char(char c, int k) {
    if (isupper(c)) {
        return ((c - 'A' + k) % 26) + 'A';
    }
       else if(islower(c))
    {
    return ( (c - 'a' + k) % 26 ) + 'a';
    } 
    return c;
}

char caesar_decrypt_char(char c, int k) {
    if (isupper(c)) {
        return ((c - 'A' - k + 26) % 26) + 'A';
    }
       else if(islower(c))
    {
    return ( (c - 'a' - k + 26) % 26 ) + 'a';
    } 
    return c;
}

int main() {
    FILE *input = fopen("plaintext.txt", "r");
    FILE *keyFile = fopen("key.txt", "r");
    FILE *output = fopen("encrypted.txt", "w");
    FILE *output_decrypted=fopen("decrypted.txt","w");

    if (!input || !keyFile || !output || !output_decrypted) {
        printf("Error opening files\n");
        return 1;
    }

    int key;
    fscanf(keyFile, "%d", &key);

    int ch;

    while ((ch = fgetc(input)) != EOF) {
        char encrypted = caesar_encrypt_char(ch, key);
        fputc(encrypted, output);
    }

    fclose(output);
    
FILE *input_encrypted = fopen("encrypted.txt", "r");
    if (!input_encrypted) {
        printf("Error opening encrypted file\n");
        return 1;
    }

    while ((ch = fgetc(input_encrypted)) != EOF) {
        char decrypted = caesar_decrypt_char(ch, key);
        fputc(decrypted, output_decrypted);
    }

    fclose(input_encrypted);
    fclose(output_decrypted);
    fclose(input);
    fclose(keyFile);
    fclose(output);

    printf("completed\n");
    return 0;
}