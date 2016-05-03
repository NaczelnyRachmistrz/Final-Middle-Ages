#include "parse.h"
#include "engine.h"
#include <stdio.h>

int main() {
    startGame();

    while (1) {
        Command * command = getCommandFromInput();
        enum ActionResult result = ACTION_INVALID_ARGUMENTS;

        switch (command->type) {
            case INIT:
                result = init(command->arguments[0],
                     command->arguments[1],
                     command->arguments[2],
                     command->arguments[3],
                     command->arguments[4],
                     command->arguments[5],
                     command->arguments[6]);
                printTopLeft();
                break;
            case MOVE: break;
            case PRODUCE_KNIGHT: break;
            case PRODUCE_PEASANT: break;
            case END_TURN: break;
            case INVALID_INPUT: result = ACTION_INVALID_ARGUMENTS; break;
        }

        if (result != ACTION_OK) {
            endGame();
            fprintf(stderr, "input error\n");
            return 42;
        }

        removeCommand(command);
    }

    endGame();
}
