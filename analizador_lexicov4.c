#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NUM_STATES 46      // Estados del Automata
#define NUM_INPUT_TYPES 22 // Columnas de tabla de transiciones
#define MAX_FILE_SIZE 1024  // Tamaño maximo de archivo

// Transiciones del Automata
typedef struct Transition {
    char input;               
    int nextState;            
    struct Transition* next;  
} Transition;

// Nodos del Automata
typedef struct State {
    int stateId;             
    Transition* transitions;  
} State;

typedef struct DFA {
    State* states[NUM_STATES]; 
} DFA;

Transition* createTransition(char input, int nextState) {
    Transition* newTransition = (Transition*)malloc(sizeof(Transition));
    newTransition->input = input;
    newTransition->nextState = nextState;
    newTransition->next = NULL;
    return newTransition;
}

void addTransition(State* state, char input, int nextState) {
    Transition* newTransition = createTransition(input, nextState);
    
    if (state->transitions == NULL) {
        state->transitions = newTransition;
    } else {
        Transition* temp = state->transitions;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTransition;
    }
}

DFA* createDFA() {
    DFA* dfa = (DFA*)malloc(sizeof(DFA));

    for (int i = 0; i < NUM_STATES; i++) {
        dfa->states[i] = (State*)malloc(sizeof(State));
        dfa->states[i]->stateId = i;
        dfa->states[i]->transitions = NULL;
    }

     // Rutas del Automata  
    addTransition(dfa->states[0], 'a', 1);  // amp: (keyword)
    addTransition(dfa->states[1], 'm', 12);  
    addTransition(dfa->states[12], 'p', 23);
    addTransition(dfa->states[23], 'p', 32);  

    addTransition(dfa->states[0], 'd', 2);  // do (keyword)
    addTransition(dfa->states[2], 'o', 13);  

    addTransition(dfa->states[0], 'e', 3);  // end (keyword)
    addTransition(dfa->states[3], 'n', 14);
    addTransition(dfa->states[14], 'd', 24);

    addTransition(dfa->states[0], 'l', 4);  // loop /live_loop (keywords)
    addTransition(dfa->states[4], 'o', 16);
    addTransition(dfa->states[16], 'o', 26);
    addTransition(dfa->states[26], 'p', 34); 
    
    addTransition(dfa->states[4], 'i', 15);
    addTransition(dfa->states[15], 'v', 25);
    addTransition(dfa->states[25], 'e', 33);
    addTransition(dfa->states[33], '_', 39);
    addTransition(dfa->states[39], 'l', 41);
    addTransition(dfa->states[41], 'o', 43);
    addTransition(dfa->states[43], 'o', 44);
    addTransition(dfa->states[44], 'p', 45);
    
    addTransition(dfa->states[0], 'p', 5); // pan: (keyword)
    addTransition(dfa->states[5], 'a', 17);
    addTransition(dfa->states[17], 'n', 27);
    addTransition(dfa->states[27], ':', 35);

    addTransition(dfa->states[5], 'l', 18);
    addTransition(dfa->states[18], 'a', 28);
    addTransition(dfa->states[28], 'y', 36);
  
    addTransition(dfa->states[0], 'r', 6);  // rate: (keyword)
    addTransition(dfa->states[6], 'a', 19);
    addTransition(dfa->states[19], 't', 29);
    addTransition(dfa->states[29], 'e', 37);
    addTransition(dfa->states[37], ':', 40);
    
    addTransition(dfa->states[0], 's', 7);  // sleep
    addTransition(dfa->states[7], 'l', 20);
    addTransition(dfa->states[20], 'e', 30);
    addTransition(dfa->states[30], 'e', 38);
    addTransition(dfa->states[38], 'e', 42);

    addTransition(dfa->states[0], '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9', 8);
    addTransition(dfa->states[8], '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9', 8);
    addTransition(dfa->states[9], '.', 21);
    addTransition(dfa->states[9], '0'||'1'||'2'||'3'||'4'||'5'||'6'||'7'||'8'||'9', 21);
    
    addTransition(dfa->states[0], ':', 9);  //Notes (identificador)
    addTransition(dfa->states[9], 'A'||'B'||'C'||'D'||'E'||'F'||'G', 22);
    addTransition(dfa->states[22], '0'||'1'||'2'||'3'||'4'||'5', 31);
    
    addTransition(dfa->states[0], ';', 10);  // ; (end of line)
    
    addTransition(dfa->states[0], ',', 11);  // , (punctuation)


    return dfa;
}

int getNextState(DFA* dfa, int currentState, char input) {
    Transition* transitions = dfa->states[currentState]->transitions;

    while (transitions != NULL) {
        if (transitions->input == input) {
            return transitions->nextState; 
        }
        transitions = transitions->next;
    }

    return -1;  
}


void processToken(DFA* dfa, char* token, int lineNumber) {
    int currentState = 0;  // Start at D0

    for (int i = 0; token[i] != '\0'; i++) {
        char currentChar = token[i];

        int nextState = getNextState(dfa, currentState, currentChar);

        if (currentChar == ' ') {
            continue;
        } else if(nextState == -1) {
            printf("Error: No valid transition for '%c' from state D%d in line %d\n", currentChar, currentState, lineNumber);
            return;
        }

        currentState = nextState; 
    }

    // Regresa tipo de token y linea donde lo encuentra
    if (currentState == 8) {
        printf("Token: %s, Type: CONSTANT, Line: %d\n", token, lineNumber);
    } else if (currentState == 10) {
        printf("Token: %s, Type: END_OF_LINE, Line: %d\n", token, lineNumber);
    } else if (currentState == 11) {
        printf("Token: %s, Type: PUNCTUATION, Line: %d\n", token, lineNumber);
    } else if (currentState == 13 || currentState == 24 || currentState == 32 || currentState == 34 || currentState == 35 || currentState == 36 || currentState == 40 || currentState == 42 || currentState == 45) {
        printf("Token: %s, Type: KEYWORD, Line: %d\n", token, lineNumber);
    } else if (currentState == 31) {
        printf("Token: %s, Type: IDENTIFIER, Line: %d\n", token, lineNumber);
    } else {
        printf("Error: Invalid token %s on line %d\n", token, lineNumber);
    }
}

// Divide input en varios tokens
void lexicalAnalysis(DFA* dfa, char* input) {
    char* token;
    int lineNumber = 1;

    token = strtok(input, " ;\n");

    while (token != NULL) {
        processToken(dfa, token, lineNumber);

        token = strtok(NULL, " ;\n");

        if (strchr(input, ';') != NULL) {
            printf("End of Line %d\n", lineNumber);
            lineNumber++;  // Proxima linea
        }
    }
}

int main() {
    DFA* dfa = createDFA(); 

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char input[MAX_FILE_SIZE];
    size_t bytesRead = fread(input, 1, MAX_FILE_SIZE - 1, file);
    input[bytesRead] = '\0';  // Null-terminate the string

    fclose(file);

    lexicalAnalysis(dfa, input);

    return 0;
}
