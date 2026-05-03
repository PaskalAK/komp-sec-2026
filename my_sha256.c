#include <stdio.h>
#include <openssl/evp.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("Cannot open file!\n");
        return 1;
    }

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);

    unsigned char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) != 0) {
        EVP_DigestUpdate(ctx, buffer, bytes);
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int len;

    EVP_DigestFinal_ex(ctx, hash, &len);

    for (int i = 0; i < len; i++)
        printf("%02x", hash[i]);
    printf("\n");

    EVP_MD_CTX_free(ctx);
    fclose(file);
    return 0;
}