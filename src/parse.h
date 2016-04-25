#ifndef PARSE_H
#define PARSE_H

#define MAX_ARGUMENTS_COUNT 7

enum command_type {
    INIT,
    MOVE,
    PRODUCE_KNIGHT,
    PRODUCE_PEASANT,
    END_TURN
};

typedef struct def_command {
    enum command_type type;
    int arguments[MAX_ARGUMENTS_COUNT];
} command;


/** Reads a command.
  Returns command with data points using 'command' structure.
  */
command* parse_command();

#endif /* PARSE_H */
