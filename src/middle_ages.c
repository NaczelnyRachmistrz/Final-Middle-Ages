#include <stdio.h>
#include <assert.h>
#include "parse.h"
#include "engine.h"

static enum ActionResult processCommand(Command * c) {
    switch (c->type) {
        case INIT: return init(c->args[0], c->args[1], c->args[2], c->args[3], c->args[4], c->args[5], c->args[6]);
        case MOVE: return move(c->args[0], c->args[1], c->args[2], c->args[3]);
        case PRODUCE_KNIGHT: return produceKnight(c->args[0], c->args[1], c->args[2], c->args[3]);
        case PRODUCE_PEASANT: return producePeasant(c->args[0], c->args[1], c->args[2], c->args[3]);
        case END_TURN: return endTurn();
        case INVALID_INPUT: return ACTION_ERROR;
        default: assert(0); return ACTION_ERROR;
    }
}

int main() {
    startGame();

    while (1) {
        Command * command = getCommandFromInput();
        enum ActionResult result = processCommand(command);
        removeCommand(command);

        if (result != ACTION_OK_NO_DISPLAY && result != ACTION_DRAW_NO_DISPLAY && result != ACTION_ERROR) {
            printTopLeft();
        }

        if (result == ACTION_OK || result == ACTION_OK_NO_DISPLAY) {
            continue;
        } else {
            endGame();
        }

        if (result == ACTION_DRAW_NO_DISPLAY || result == ACTION_DRAW || result == ACTION_PLAYER1_WIN || result == ACTION_PLAYER2_WIN) {
            switch (result) {
                case ACTION_PLAYER1_WIN: fprintf(stderr, "player 1 won\n"); break;
                case ACTION_PLAYER2_WIN: fprintf(stderr, "player 2 won\n"); break;
                default: fprintf(stderr, "draw\n"); break;
            }
            return 0;
        } else {
            fprintf(stderr, "input error\n");
            return 42;
        }
    }
}
