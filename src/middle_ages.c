#include "parse.h"
#include "engine.h"
#include <stdbool.h>
#include <stdio.h>

int main() {
    bool gameInProgress = true;
    start_game();

    while (gameInProgress) {
        Command * command = getCommandFromInput();

        printf("%d", command->type);

        switch (command->type) {
            case INIT: break;
            case MOVE: break;
            case PRODUCE_KNIGHT: break;
            case PRODUCE_PEASANT: break;
            case END_TURN: break;
            case INVALID: gameInProgress = false; break;
        }

        removeCommand(command);
    }

    end_game();
    return 0;
}
