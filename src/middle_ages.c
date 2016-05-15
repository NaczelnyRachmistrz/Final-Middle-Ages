#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "parse.h"
#include "engine.h"

static void putError() {
	clearAll();
	fprintf(stderr, "input error\n");
	return;
}

int main() {

    startGame();

    Command newCommand;
    
    int begin = 2;
    bool initCorrect;
    while (begin-- > 0) {
		newCommand = parseCommand();
		if (strcmp(newCommand.name, "INIT") == 0) {
            initCorrect = init(newCommand.data[0],
                newCommand.data[1],
                newCommand.data[2],
                newCommand.data[3],
                newCommand.data[4],
                newCommand.data[5],
                newCommand.data[6]);
                if (!initCorrect) {
					putError();
					return 42;
				}
				printTopleft();
		} else {
			putError();
			return 42;			
		}
	}
	
    while (1) {
		
		if (checkWinner())  {
			break;
		}
		newCommand = parseCommand();
		
        if (strcmp(newCommand.name, "MOVE") == 0) {
			if (!move(newCommand.data[0],
				newCommand.data[1],
				newCommand.data[2],
				newCommand.data[3])) {
					putError();
					return 42;
				}
		} else if (strcmp(newCommand.name, "PRODUCE_KNIGHT") == 0) {
			if (!produceKnight(newCommand.data[0],
				newCommand.data[1],
				newCommand.data[2],
				newCommand.data[3])) {
					putError();
					return 42;
				}
		} else if (strcmp(newCommand.name, "PRODUCE_PEASANT") == 0) {
			if (!producePeasant(newCommand.data[0],
				newCommand.data[1],
				newCommand.data[2],
				newCommand.data[3])) {
					putError();
					return 42;
				}			
		} else if (strcmp(newCommand.name, "END_TURN") == 0) {
			if (endTurn()) {
				break;
			}
			continue;
		} else {
			putError();
			return 42;
		}

        printTopleft();
    }

    endGame();

    return 0;
}
