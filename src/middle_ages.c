#include "parse.h"
#include "engine.h"
#include <stdio.h>

#define GAME_FINISHED 0
#define GAME_PLAYING 1
#define GAME_INPUT_ERROR 42

int main() {
    int gameState = GAME_PLAYING;
    
    startGame();
    
    while (gameState == GAME_PLAYING) {
        Command * command = getCommandFromInput();

        switch (command->type) {
            case INIT: break;
            case MOVE: break;
            case PRODUCE_KNIGHT: break;
            case PRODUCE_PEASANT: break;
            case END_TURN: break;
            case INVALID: gameState = GAME_INPUT_ERROR; break;
        }

        removeCommand(command);
    }

    endGame();

    switch (gameState) {
        case GAME_INPUT_ERROR: fprintf(stderr, "input error\n");
    }

    return gameState;
}
