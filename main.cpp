#include <iostream>

#include "Crossword.h"

// Gets 1, 2, or 3 from user.
int32_t GetUserCommand ();
void ExecuteCommand (Crossword* crossword, int32_t command);

int main() {
    printf ("Input file name: ");
    char* fileName = GetUserString();
    Crossword* crossword = ReadFromFile(fileName);
    free(fileName);

    if (crossword == NULL) return 0;

    ExecuteCommand(crossword, GetUserCommand());

    DestroyCrossword(crossword);
    return 0;
}

int32_t GetUserCommand () {
    int32_t cmd;
    char* cmdStr;

    while (1) {
        printf("\nOptions:\n");
        printf("(1) Print longest vertical words.\n");
        printf("(2) Print locations of given word.\n");
        printf("(3) Test for symmetry.\n");

        printf("\n");

        cmdStr = GetUserString();
        cmd = *cmdStr - '0';
        free(cmdStr);

        if (1 <= cmd && cmd <= 3) {
            break;
        } else {
            printf("Invalid input!");
        }
    }

    return cmd;
}

void ExecuteCommand (Crossword* crossword, int32_t command) {
    char* userStr;
    int32_t temp; // Just a temp int.

    switch (command) {
        case 1:
            temp = VertMaxWordLength(crossword);
            printf("Max word length: %d\n", temp);
            PrintVertWordsOfLength(crossword, temp);
            break;
        case 2:
            printf("Input word to find: ");
            userStr = GetUserString();
            PrintWordPositions(crossword, userStr);
            free (userStr);
            break;
        case 3:
            FindAsymmetry(crossword);
            break;
        default:
            printf("Error! Invalid command!\n");
            return;
    }
}