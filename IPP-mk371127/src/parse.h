 /** @file
    Interface of parser.

 */

#ifndef PARSE_H
#define PARSE_H

typedef struct defCommand {
    char name[16];
    int data[7];
} Command;


/** Reads a command.
  Returns command with data points using 'Command' structure.
  */
Command parseCommand();

#endif /* PARSE_H */
