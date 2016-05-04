#ifndef MIDDLE_AGES_PARSE_H
#define MIDDLE_AGES_PARSE_H

#define COMMANDS_COUNT 5
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS_COUNT 7

enum CommandType {
    INIT,
    MOVE,
    PRODUCE_KNIGHT,
    PRODUCE_PEASANT,
    END_TURN,
    INVALID_INPUT
};

typedef struct {
    enum CommandType type;
    long arguments[MAX_ARGUMENTS_COUNT];
} Command;

Command * getCommandFromInput();
void removeCommand(Command * command);

#endif
