#include <iostream>

#include "Crossword.h"

int main() {
    char* fileName = GetUserString();
    Crossword* crossword = ReadFromFile(fileName);
    free(fileName);

    PrintVertWordsOfLength(crossword, VertMaxWordLength(crossword));
    DestroyCrossword(crossword);
    return 0;
}
