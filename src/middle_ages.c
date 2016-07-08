 /** @file
    Modified version of game engine. An AI programme, able to win with some simple strategies. Knights move to the closest 
    * enemy, peasant initially produces a second peasant and then, if it is possible, new knights.cd 
    * @return 0 if the game is won
    * @return 1 if the game is drawn
    * @return 2 if the game is lost
    * @return 42 if the input is incorrect
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse.h"
#include "engine.h"
#include "utils.h"
/**
 * Prints (into stderr) error message, terminates the game and frees memory if the input data is incorrect.
 **/
static void putError() {
	clearAll();
	fprintf(stderr, "input error\n");
	return;
}

/**
 * Main function of the game.
 **/
int main() {

    startGame();

    Command newCommand;
    char newLine[100];
    bool initCorrect;
    
    readCommand(newLine);
	newCommand = parseCommand(newLine);
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
	} else {
		putError();
		return 42;			
	}
	
    while (1) {
		for (int i = 0; i < 100; i++) {
			newLine[i] = '\0';
		}
		if (checkWinner())  {
			break;
		}
		
		if (checkCurrentPlayer() == checkMyID()) {
			makeMoves();
			if (checkWinner()) {
				break;
			}
			printf("END_TURN\n");
			fflush(stdout);
			if (endTurn()) {
				break;
			}
			continue;
		}
		readCommand(newLine);
		newCommand = parseCommand(newLine);
        if (strcmp(newCommand.name, "MOVE") == 0) {
			if (move(newCommand.data[0],
				newCommand.data[1],
				newCommand.data[2],
				newCommand.data[3]) == 0) {
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
    }

    return endGame();
}
