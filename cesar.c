#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // за isupper()
#define MAXN 1000

char caesar_encrypt_char(char p, int k) {
    if (isupper(p)) {
        return ( (p - 'A' + k) % 26 ) + 'A';
    }
    else if(islower(p))
    {
    return ( (p - 'a' + k) % 26 ) + 'a';
    } 
    return p;
}

char caesar_decrypt_char(char c, int k) {
    if (isupper(c)) {
        return  (c - 'A' - k + 26 ) % 26  + 'A';
    }
    else if(islower(c))
    {
        return  (c - 'a' - k + 26) % 26  + 'a'; 
    }
    return c;
}
char* caesar_encrypt(char* plaintext, int key)
{
    int len= strlen(plaintext);
    char* cipher = malloc(len+ 1);
    if(!cipher) return NULL;

    for (int i= 0; i< len; i++){
        cipher[i]= caesar_encrypt_char(plaintext[i], key);
    }
    cipher[len]='\0';
    return cipher;
}
int main()
{
    char plaintext[MAXN];
    int key;
    printf("Enter text: ");
    scanf("%s", plaintext);
    printf("Enter key: ");
    scanf("%d", &key);
    char* cipher= caesar_encrypt(plaintext, key);
    printf("%s", cipher);
    return EXIT_SUCCESS;

}