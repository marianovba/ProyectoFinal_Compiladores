#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Token types
enum TokenType {
    KEYWORD, 
    CONSTANT,
    PUNCTUATION, 
    IDENTIFIER, 
    END_OF_LINE, 
    ERROR};

// DFA matrix (transitions between states)
size_t estados[46][22] = {
    // matrix data remains the same
    {1,2,3,-1,4,-1,-1,-1,5,6,7,-1,-1,-1,8,-1,-1,9,11,-1,10,-1},
    {-1,-1,-1,-1,-1,12,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,13,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,15,-1,-1,-1,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {17,-1,-1,-1,18,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,20,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,-1,-1,-1,-1,21,-1,-1},  //d8 Numeros (constant)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,22,-1,-1,-1,-1,-1}, //d9 : (punctuation)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d10 ; (end of line)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d11 , (punctuation)
    {-1,-1,-1,-1,-1,-1,-1,-1,23,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d13 do (keyword)
    {-1,24,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,25,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,26,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,27,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {28,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,29,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,30,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,31,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,32,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d24 end (keyword)
    {-1,-1,33,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,34,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,35,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,36,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,37,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,38,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d31 Notas (identificador)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d32 amp: (keyword)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,39},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d34 loop
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d35 pan: (keyword)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d36 play (keyword)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,40,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,41,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,42,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d40 rate: (keyword)
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,43,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //d42 sleep (keyword)
    {-1,-1,-1,-1,-1,-1,-1,44,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,45,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}  //d45 live_loop (keyword)
};

enum TokenType getTokenType(char *token) {
    int state = 0; 
    int i;

    for (i = 0; token[i] != '\0'; i++) {
        char c = token[i];
        int inputType = -1;

        if (c == 'a') {
            inputType = estados[c][0];  
        } else if (c == 'd') {
            inputType = estados[c][1];
        } else if (c == 'e') {
            inputType = estados[c][2];
        } else if (c == 'i') {
            inputType = estados[c][3];
        } else if (c == 'l') {
            inputType = estados[c][4];
        } else if (c == 'm') {
            inputType = estados[c][5];
        } else if (c == 'n') {
            inputType = estados[c][6];
        } else if (c == 'o') {
            inputType = estados[c][7];
        } else if (c == 'p') {
            inputType = estados[c][8];
        } else if (c == 'r') {
            inputType = estados[c][9];
        } else if (c == 's') {
            inputType = estados[c][10];
        } else if (c == 't') {
            inputType = estados[c][11];
        } else if (c == 'v') {
            inputType = estados[c][12];
        } else if (c == 'y') {
            inputType = estados[c][13];
        } else if (c>='0' && c<='9') {
            inputType = estados[c][14];
        } else if (c>='0' && c<='5') {
            inputType = estados[c][15];
        } else if (c == 'A') {
            inputType = estados[c][16];
        } else if (c == 'B') {
            inputType = estados[c][16];
        } else if (c == 'C') {
            inputType = estados[c][16];
        } else if (c == 'D') {
            inputType = estados[c][16];
        } else if (c == 'E') {
            inputType = estados[c][16];
        } else if (c == 'F') {
            inputType = estados[c][16];
        } else if (c == 'G') {
            inputType = estados[c][16];
        } else if (c == ':') {
            inputType = estados[c][17];
        } else if (c == ',') {
            inputType = estados[c][18];
        } else if (c == '.') {
            inputType = estados[c][19];
        } else if (c == ';') {
            inputType = estados[c][20];
        } else if (c == '_') {
            inputType = estados[c][21];
        } else if (c == ' ') {
            continue;
        } else {
            return ERROR;
        }


        state = estados[state][inputType];

        // Marca Error para cualquier estado no definido
        if (state == -1) {
            return ERROR;
        }
    }

    // Decide el tipo de token en base al estado final
    switch (state) {
        case 8:
            return CONSTANT; // Constant state
        case 10:
            return END_OF_LINE; // End of line
        case 11:
            return PUNCTUATION; // Operator
        case 13:
            return KEYWORD; // Keyword
        case 24: 
            return KEYWORD; // Keyword
        case 31:
            return IDENTIFIER; // Identifier (Notes)
        case 32:
            return KEYWORD; // Keyword
        case 34:
            return KEYWORD; // Keyword
        case 35:
            return KEYWORD; // Keyword
        case 36:
            return KEYWORD;
        case 40:
            return KEYWORD;
        case 42:
            return KEYWORD;
        case 45:
            return KEYWORD; 
        default:
            return ERROR; // Default to identifier
    }
}

const char* getTokenTypeName(enum TokenType type) {
    switch (type) {
        case KEYWORD:
            return "KEYWORD";
        case CONSTANT:
            return "CONSTANT";
        case PUNCTUATION:
            return "PUNCTUATION";
        case IDENTIFIER:
            return "IDENTIFIER";
        case END_OF_LINE:
            return "END OF LINE";
        case ERROR:
            return "ERROR";
    }
}

// Function to perform lexical analysis
void lexicalAnalysis(char *line, int lineNumber) {
    char token[100];
    int tokenIndex = 0;

    for (int i = 0; i < strlen(line); i++) {
        char current = line[i];

        if (current == ' ' || current == ';' || current == '\n') {
            // Process the current token
            if (tokenIndex > 0) {
                token[tokenIndex] = '\0';
                enum TokenType type = getTokenType(token);
                printf("Token: %s, Type: %s, Line: %d\n", token, getTokenTypeName(type), lineNumber);
                tokenIndex = 0;
            }

            // If end of line token (e.g., ';')
            if (current == ';') {
                printf("Token: ;, Type: %s, Line: %d\n", getTokenTypeName(END_OF_LINE), lineNumber);
            }
        } else {
            token[tokenIndex++] = current;
        }
    }
}

int main() {
    // Test input
    char *lines[] = {
        "pan: 123;",
        "end 456;",
        "play A2;"
    };

    // Analyze each line
    for (int i = 0; i < 3; i++) {
        lexicalAnalysis(lines[i], i + 1);
    }

    return 0;
}