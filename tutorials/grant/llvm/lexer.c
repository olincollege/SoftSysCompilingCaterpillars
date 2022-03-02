#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Token {
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,
    
    tok_identifier = -4,
    tok_number = -5
};

static char *IdentifierStr;
static double NumVal;

static int get_tok() {
    static int lastChar = ' ';

    while (isspace(lastChar)) {
        lastChar = getChar();
    }

    if (isalpha(lastChar)) {
        IdentifierStr = lastChar;
        while (isalnum((lastChar = getChar()))) {
            IdentifierStr += lastChar;
        }
        if (strcmp(IdentifierStr, "def")==0) {
            return tok_def;
        }
        if (strstr(IdentifierStr, "extern") ==0) {
            return tok_extern;
        }
        return tok_identifier;
    }

    if (isdigit(lastChar) || lastChar == '.') {
        char *NumStr;
        do {
            NumStr += lastChar;
            lastChar = getChar();
        } while (isdigit(lastChar) || lastChar == '.');

        NumVal = strtod(NumStr, NULL);
        return tok_number;
    }

    if (lastChar == '#') {
        do {
            lastChar = getChar();
        } while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');

        if (lastChar != EOF) {
            return get_tok();
        }
    }

    if (lastChar == EOF) {
        return tok_eof;
    }

    int thisChar = lastChar;
    lastChar = getChar();
    return thisChar;
}