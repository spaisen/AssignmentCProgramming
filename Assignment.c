#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <sys/stat.h>

#define MIN_LENGTH 16
#define MAX_LENGTH 24
#define ALPHABET_COUNT 26
#define NUMBER_COUNT 10
#define SYMBOL_COUNT 32

char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
char uppercase_alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char numbers[] = "0123456789";
char symbols[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

void generate_password(int length, bool include_uppercase, bool include_numbers, bool include_symbols, char *password) {
    int alphabet_count = ALPHABET_COUNT;
    int number_count = include_numbers ? NUMBER_COUNT : 0;
    int symbol_count = include_symbols ? SYMBOL_COUNT : 0;

    if (include_uppercase) {
        alphabet_count += ALPHABET_COUNT;
    }

    for (int i = 0; i < length; i++) {
        int character_set = rand() % (alphabet_count + number_count + symbol_count);

        if (character_set < alphabet_count) {
            int index = rand() % ALPHABET_COUNT;
            if (include_uppercase && index < ALPHABET_COUNT / 2) {
                password[i] = uppercase_alphabet[index];
            } else {
                password[i] = alphabet[index];
            }
        } else if (character_set < alphabet_count + number_count) {
            int index = rand() % NUMBER_COUNT;
            password[i] = numbers[index];
        } else if (character_set < alphabet_count + number_count + symbol_count) {
            int index = rand() % SYMBOL_COUNT;
            password[i] = symbols[index];
        }
    }

    password[length] = '\0';
}

int main() {
    srand(time(NULL));

    char website[100];
    char username[100];
    int length;
    bool include_uppercase = false;
    bool include_numbers = false;
    bool include_symbols = false;
    char password[MAX_LENGTH + 1];

    printf("Enter website: ");
    scanf("%s", website);

    printf("Enter username: ");
    scanf("%s", username);

    // Create the password folder if it doesn't exist
    struct stat st = {0};
    if (stat("passwords", &st) == -1) {
        mkdir("passwords");
    }

    printf("Enter password length (%d-%d): ", MIN_LENGTH, MAX_LENGTH);
    scanf("%d", &length);
    while (length < MIN_LENGTH || length > MAX_LENGTH) {
        printf("Invalid length, enter password length (%d-%d): ", MIN_LENGTH, MAX_LENGTH);
        scanf("%d", &length);
    }

    char include_uppercase_input[4];
    printf("Include uppercase letters (y/n): ");
    scanf("%s", include_uppercase_input);
    if (include_uppercase_input[0] == 'y' || include_uppercase_input[0] == 'Y') {
        include_uppercase = true;
    }

    char include_numbers_input[4];
    printf("Include numbers (y/n): ");
    scanf("%s", include_numbers_input);
    if (include_numbers_input[0] == 'y' || include_numbers_input[0] == 'Y') {
        include_numbers = true;
    }

    char include_symbols_input[4];
    printf("Include symbols (y/n): ");
    scanf("%s", include_symbols_input);
    if (include_symbols_input[0] == 'y' || include_symbols_input[0] == 'Y') {
        include_symbols = true;
    }

    generate_password(length, include_uppercase, include_numbers, include_symbols, password);

    char file_path[150];
    sprintf(file_path, "passwords/%s.txt", website);
    FILE *file = fopen(file_path, "a");
    fprintf(file, "%s:%s\n", username, password);
    fclose(file);
    printf("Your password is saved in the 'passwords' folder in a file called %s.txt.",website);
    return 0;
}
