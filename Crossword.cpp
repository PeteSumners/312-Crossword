//
// Created by peter on 2/16/18.
//

#include "Crossword.h"
#include <stdio.h>
#include <stdlib.h> // For malloc.
#include <ctype.h> // For isalpha.

#define FILENAME_SIZE_STEP 10

Crossword* CreateCrossword (int32_t rows, int32_t cols) {
    if (rows < 0 || cols < 0) {
        printf ("Null crosswords not allowed.");
        return NULL;
    }

    Crossword* crossword = (Crossword*) malloc(sizeof(Crossword));
    crossword->rows = rows;
    crossword->cols = cols;
    crossword->matrix = (char*) malloc(sizeof(char) * rows * cols);
}

void DestroyCrossword (Crossword* crossword) {
    if (crossword == NULL) {
        printf("Don't free a null crossword!");
        return;
    }

    free (crossword->matrix);
    crossword->matrix = NULL;

    free (crossword);
    crossword = NULL;
}

Crossword* ReadFromFile (const char fileName[]) {
    // Basic algorithm:
    // Get dimensions.
    // Get matrix.
    // Return crossword.

    Crossword* crossword;
    FILE *filePtr = fopen(fileName, "r");

    int32_t rowCount;
    int32_t colCount;

    if (filePtr != NULL) {

        if (fscanf(filePtr, "%d %d\n", &rowCount, &colCount) != NULL) { // != NULL just to be clear
                                                                        // even though it's not necessary.
            if (rowCount >= 0 && colCount >= 0) { // Don't mess with neg. dimensions.
                crossword = CreateCrossword (rowCount, colCount);

                char currentRow[colCount + 1]; // + 1 for null character.
                for (uint32_t i = 0; i < rowCount; i++) { // Get matrix data now.
                    if (fgets(currentRow, colCount + 1, filePtr) != NULL) {

                        puts(currentRow);
                        for (uint32_t j = 0; j < colCount; j++) { // No need to store null chars.
                            crossword->matrix[i * colCount + j] = currentRow[j];
                        }

                        if (*fgets (currentRow, colCount + 1, filePtr) != '\n') { // I know I'm calling fgets twice: I want to.
                            printf ("Error (1) in formatting at crossword row %d! Destroying crossword.\n", i);
                            DestroyCrossword(crossword);
                            break;
                        }
                        //printf("%d: %s", i, currentRow);
                    } else {
                        printf ("Error (2) in formatting at crossword row %d! Destroying crossword.\n", i);
                        DestroyCrossword(crossword);
                        break; // Don't try to put anything else in a destroyed crossword.
                    }
                }
            } else {
                printf ("Error! Negative dimensions!\n");
            }
        } else {
            printf("Error! Unrecognized dimensions!\n");
        }
        fclose(filePtr);
    } else {
        printf("Error! Null file pointer!\n");
    }

    return crossword;
}

uint32_t VertMaxWordLength (Crossword* crossword){
    int32_t tempCounter = 0, maxLength = 0;

    // Loop through cols.
    for (int32_t i = 0; i < crossword->cols; i++) {
        for (int32_t j = 0; j < crossword->rows; j++) {
            if (isalpha(crossword->matrix[j * crossword->cols + i])) { // Start temp counter when letter is seen.
                tempCounter++;
            } else { // Stop temp counter when letters stop being seen.
                maxLength = Max (maxLength, tempCounter); // Update max length, reset temp counter.
                tempCounter = 0;
            }
        }

        // In case word ends at end of column.
        maxLength = Max (maxLength, tempCounter);
        tempCounter = 0;
    }

    return maxLength;
}

void PrintVertWordsOfLength(Crossword* crossword, uint32_t length) {
    // Print ALL vert words of length, one line for ea. word.
    int32_t tempCounter = 0, wordStartIndex = 0; // wordStartIndex is starting index of possible word of length length.

    // Loop through all rows for ea. col, start counter when letter is first encountered. (Loop vertically.)
    for (int32_t i = 0; i < crossword->cols; i++) {
        for (int32_t j = 0; j < crossword->rows; j++) {
            if (isalpha(crossword->matrix[j * crossword->cols + i])) { // Start temp counter when letter is seen.
                tempCounter++;
                printf("%d,", tempCounter);
            } else { // Stop temp counter when letters stop being seen.
                putchar('\n');
                if (tempCounter == length) {
                    // Print word b/c it's of length length.
                    for (int32_t k = 0; k < length; k++) {
                        putchar(crossword->matrix[crossword->cols * (j - (length - 1) + k) + i]);
                    }
                    putchar('\n');
                }
                tempCounter = 0;
            }

            if (j == crossword->rows - 1) { // In case word ends at end of column.
                putchar('\n');
                if (tempCounter == length) {
                    // Print word b/c it's of length length.
                    for (int32_t k = 0; k < length; k++) {
                        putchar(crossword->matrix[crossword->cols * (j - (length - 1) + k) + i]);
                    }
                    putchar('\n');
                }
                tempCounter = 0;
            }
        }
    }

    // Stop counter when letters stop being encountered.
    // Check counter w/ length, print word if counter == length.
}

int FindAsymmetry (Crossword* crossword) {
    // Inefficient, simple way:
    // Loop through matrix, looking for '*'.
    // If '*' is encountered, check for '*' at inverse coords.
    // - If there's something else, print current coords on their own line.
}

void PrintWordPositions (char word[]) {
    // Loop through crossword
}

char* GetUserString () {
    char* userString;
    uint32_t stringSize = 0, stringLength = 0;
    userString = (char*) malloc (FILENAME_SIZE_STEP * sizeof(char));

    char currentChar;
    printf ("Input file name: ");
    while (1) {
        currentChar = getchar();

        if (currentChar == EOF || currentChar == '\n') break; // I didn't use brackets because it's only one line!

        if (stringLength >= stringSize) { // Increase capacity if required.
            stringSize += FILENAME_SIZE_STEP;
            userString = (char*) realloc(userString, stringSize * sizeof(char));

            if (userString == NULL) {
                printf ("File name got too big! Stopping program now.");
                return 0;
            }
        }

        userString[stringLength++] = currentChar;
    }
    return userString;
}

int32_t Max (int32_t a, int32_t b) {
    if (a > b) return a;
    else return b;
}