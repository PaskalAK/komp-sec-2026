#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rc4_crypt(unsigned char *key, int keylen, unsigned char *data, int datalen, unsigned char *output) {
    unsigned char S[256];
    unsigned char temp;
    int i = 0, j = 0;


    for (i = 0; i < 256; i++) {
        S[i] = i;
    }

    for (i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % keylen]) % 256;

        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }

    i = 0;
    j = 0;

    for (int k = 0; k < datalen; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        unsigned char keystream = S[(S[i] + S[j]) % 256];

        output[k] = data[k] ^ keystream;
    }
}

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Usage: %s input output key\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "rb");
    FILE *out = fopen(argv[2], "wb");

    if (!in || !out) {
        printf("Error opening files\n");
        return 1;
    }
    fseek(in, 0, 2);
    long size = ftell(in);
    rewind(in);
    unsigned char *data = malloc(size);
    unsigned char *output = malloc(size);

    if (!data || !output) {
        printf("Memory allocation failed\n");
        return 1;
    }

    fread(data, 1, size, in);

    rc4_crypt((unsigned char*)argv[3], strlen(argv[3]), data, size, output);

    fwrite(output, 1, size, out);

    fclose(in);
    fclose(out);
    free(data);
    free(output);

    printf("Done!\n");
    return 0;
}