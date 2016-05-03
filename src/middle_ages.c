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
                result = init(command->arguments[0], command->arguments[1], command->arguments[2],
                     command->arguments[3], command->arguments[4], command->arguments[5], command->arguments[6]);
                break;
            case MOVE:
                result = move(command->arguments[0], command->arguments[1], command->arguments[2], command->arguments[3]);
                break;
            case PRODUCE_KNIGHT:
                result = produceKnight(command->arguments[0], command->arguments[1], command->arguments[2], command->arguments[3]);
                break;
            case PRODUCE_PEASANT:
                result = producePeasant(command->arguments[0], command->arguments[1], command->arguments[2], command->arguments[3]);
                break;
            case END_TURN:
                result = endTurn();
                break;
            case INVALID_INPUT:
                result = ACTION_INVALID_ARGUMENTS;
                break;
        }

        removeCommand(command);

        if (result == ACTION_OK) {
            printTopLeft();
        } else if (result == ACTION_OK_NO_DISPLAY) {
            continue;
        } else {
            endGame();
            fprintf(stderr, "input error\n");
            return 42;
        }
    }
}
