#include <stdio.h>
#include <string.h>
#include <crypt.h>

void dictionary_attack(const char *username, const char *hash, const char *dict_file) {
    FILE *file = fopen(dict_file, "r");
    if (!file) {
        printf("Error opening the dictionary!\n");
        return;
    }

    char word[256];

    while (fgets(word, sizeof(word), file)) {
        word[strcspn(word, "\n")] = 0;

        char *computed = crypt(word, hash);

        if (strcmp(computed, hash) == 0) {
            printf("User: %s | Password: %s\n", username, word);
            fclose(file);
            return;
        }
    }

    printf("User: %s | Password not found\n", username);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s shadow.txt dictionary.txt\n", argv[0]);
        return 1;
    }

    FILE *shadow = fopen(argv[1], "r");
    if (!shadow) {
        printf("Cannot open shadow file\n");
        return 1;
    }

    char line[512];

    while (fgets(line, sizeof(line), shadow)) {

        char *username = strtok(line, ":");
        char *hash = strtok(NULL, ":");

        if (username && hash) {
            printf("\nCracking user: %s\n", username);
            dictionary_attack(username, hash, argv[2]);
        }
    }

    fclose(shadow);
    return 0;
}