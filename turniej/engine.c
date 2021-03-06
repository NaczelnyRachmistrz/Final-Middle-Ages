 /** @file
    Game engine.

 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "engine.h"
/* DATA STRUCTURE */

/**
 * Enum with all kinds of pawns.
 **/
enum PieceType {KING, KNIGHT, PEASANT};

/**
 * Data structure with the positon, owner and turn of last move of a pawn.
 **/
typedef struct piece {
	enum PieceType type; /**< Type of the piece. */
	int owner; /**< ID of a player. */
	int x; /**< Column of a pawn. */
	int y; /**< Row of a pawn. */
	int lastMove; /**< Number of turns left when the last move was done. */
} Piece;

/**
 * List-type data structure of pieces.
 **/
typedef struct pieceList {
	Piece firstPiece; /**< First piece on the list */
	struct pieceList* next; /**< Pointer to the list tail. */
} PieceList;

/**
 * Simple structure representing a point;
 **/
typedef struct pair {
	int x; /**< Column coordinate. */
	int y; /**< Row coordinate. */
} Pair;

/* REQUIRED DATA */

/**
 * List of first player's pieces.
 **/
	PieceList* firstPlayer;

/**
 * List of second player's pieces.
 **/
	PieceList* secondPlayer;

/**
 * Size of the board.
 **/
	int boardSize;
/**
 * Number of turns left.
 **/
	int turnsLeft;

/**
 * ID given by the script.
 **/
	int MyID;

/**
 * Coordinates of the rival's king.
 **/
	Pair foeKing;
	
/**
 * Coordinates of the AI's king.
 **/
	Pair myKing;

/* Prefered moves */

static Pair upLeft[6] = {{-1, -1}, {-1, 0}, {0, -1}, {-1, 1}, {1, -1}, {0, 0}};

static Pair upRight[6] = {{1, -1}, {1, 0}, {0, -1}, {1, 1}, {-1, -1}, {0, 0}};

static Pair downLeft[6] = {{-1, 1}, {-1, 0}, {0, 1}, {-1, -1}, {1, 1}, {0, 0}};

static Pair downRight[6] = {{1, 1}, {1, 0}, {0, 1}, {-1, 1}, {1, -1}, {0, 0}};

static Pair up[6] = {{0, -1}, {-1, -1}, {1, -1}, {1, 0}, {-1, 0}, {0, 0}};

static Pair down[6] = {{0, 1}, {-1, 1}, {1, 1}, {1, 0}, {-1, 0}, {0, 0}};

static Pair left[6] = {{-1, 0}, {-1, -1}, {-1, 1}, {0, 1}, {0, -1}, {0, 0}};

static Pair right[6] = {{1, 0}, {1, -1}, {1, 1}, {0, -1}, {0, 1}, {0, 0}};	
	
/* Prefered new Peasants */

static Pair tab1[5] = {{-1, -1}, {1, 1}, {-1, 1}, {1, -1}, {0, 0}};

static Pair tab2[5] = {{1, -1}, {-1, 1}, {-1, -1}, {1, 1}, {0, 0}};

static Pair tab3[5] = {{-1, 1}, {1, -1}, {1, 1}, {-1, -1}, {0, 0}};

static Pair tab4[5] = {{1, 1}, {-1, -1}, {1, -1}, {-1, 1}, {0, 0}};

int howOften = 2;

int producedPieces = 0;
/* AUXILIARY FUNCTIONS */

/**
 * Deletes given pieceList and frees memory.
 * @param[in] list Pointer to the list.
 **/
static void clearPieceList(PieceList* list) {
	if (list == NULL) {
		return;
	}
	if (list->next != NULL) {
		clearPieceList(list->next);
	}
	free(list);
	return;
}

/**
 * Clears the piece lists of both players.
 **/
void clearAll() {
	clearPieceList(firstPlayer);
	clearPieceList(secondPlayer);
	return;
}

/**
 * Returns |a-b|.
 **/
static int dist(int a, int b) {
	if (a > b) {
		return a - b;
	}
	return b - a;
}

/**
 *  Return max(a, b);
 **/
static int max(int a, int b) {
	if (a > b) {
		return a;
	}
	return b;
}

/**
 * ID of current player.
 **/
static int currentPlayer;

/**
 * Variable, winner = 0 when game is not over yet, winner = 3 when game is drawn,
 * ID of the winner otherwise.
 **/
static int winner = 0;

/**
 * Variable, counts the number of turns.
 **/
static int endTurnCounter = 0;

/**
 * Checks the number of INIT commands.
 **/
static int initCounter = 0;

int checkCurrentPlayer() {
	return currentPlayer;
}

int checkMyID() {
	return MyID;
}

/**
 * Checks if there are two peasants produced, in order to determinate
 * the move of a peasant.
 **/
static bool secondPeasantProduced = false;

bool checkWinner() {
	return (winner != 0);
}

/** 
 * Checks which piece wins the battle. Additionally, sets the winner if the king is beaten.
 * @param[in] p1 First piece.
 * @param[in] p2 Second piece.
 * @return 1 if the first piece wins,
 * @return 2 if the second piece wins,
 * @return 3 if both pieces die.
 **/
static int fight(Piece p1, Piece p2) {
	if (p1.type == KING && p2.type == KING) {
		winner = 3;
	}
	if (p1.type == KING && p2.type == KNIGHT) {
		winner = p2.owner;
	}
	if (p1.type == KNIGHT && p2.type == KING) {
		winner = p1.owner;
	}
	if (p1.type == p2.type) {
		return 3;
	}
	if (p1.type == KNIGHT) {
		return 1;
	}
	if (p2.type == KNIGHT) {
		return 2;
	}
	if (p1.type == KING) {
		return 1;
	}
	return 2;
}

/**
 * Checks if the INIT coordinates are valid.
 **/
static bool checkPositions(int x1, int x2, int y1, int y2) {
	bool ret = true;
	ret &= (x1 > 0 && x1 < boardSize - 2);
	ret &= (x2 > 0 && x2 < boardSize - 2);
	ret &= (y1 > 0 && y1 <= boardSize);
	ret &= (y2 > 0 && y2 <= boardSize);
	return ret;
}

/** 
 * Returns true, if the given coordinates do not fit the board.
 **/
static bool wrongPosition(int x1, int y1, int x2, int y2) {
	bool ret = true;
	ret &= (x1 > 0 && x1 <= boardSize);
	ret &= (x2 > 0 && x2 <= boardSize);
	ret &= (y1 > 0 && y1 <= boardSize);
	ret &= (y2 > 0 && y2 <= boardSize);
	return !ret;
}

/**
 * Checks if the move is correct.
 **/
static bool incorrectMove(int x1, int y1, int x2, int y2) {
	int x, y;
	if (wrongPosition(x1, y1, x2, y2)) {
		return true;
	}
	x = dist(x1, x2);
	y = dist(y1, y2);
	if (x + y == 0) {
		return true;
	}
	if (x > 1 || y > 1) {
		return true;
	}
	return false;
}

/**
 * Returns pointer to the piece list of the current player.
 **/
static PieceList** setPlayer1() {
	if (currentPlayer == 1) {
		return &firstPlayer;
	} else {
		return &secondPlayer;
	}
}

/**
 * Returns pointer to the piece list of the player who is waiting for his move.
 **/
static PieceList** setPlayer2() {
	if (currentPlayer == 1) {
		return &secondPlayer;
	} else {
		return &firstPlayer;
	}	
}	

/**
 * Returns a pointer to the pieceList pointer, where the first piece is on the given position.
 * @param[in] x Column of the pawn.
 * @param[in] y Row of the pawn.
 * @param[in] tempList Pointer to the pieceList pointer in which we are looking for a piece.
 **/
static PieceList** pointerToPosition(int x, int y, PieceList** tempList) {
	PieceList** ret = NULL;
	while (*tempList != NULL) {
		if ((*tempList)->firstPiece.x == x && (*tempList)->firstPiece.y == y) {
			ret = tempList;
			break;
		}
		tempList = &(*tempList)->next;
	}
	return ret;
}

/**
 * Adds piece in the end of the given list.
 * @param[in] x Column of the piece.
 * @param[in] y Row of the piece.
 * @param[in] p Type of the piece.
 * @param[in] tempList Pointer to the pieceList pointer on which we are going to add a piece.
 * @return false if there already is a piece with given coordinates on the list,
 * @return true otherwise.
 **/
static bool addPiece(int x, int y, PieceList** tempList, enum PieceType p) {
	while (*tempList != NULL) {
		if ((*tempList)->firstPiece.x == x && (*tempList)->firstPiece.y == y) {
			return false;
		}
		tempList = &(*tempList)->next;
	}
	
	*tempList = (PieceList*) malloc(sizeof(PieceList));
	(*tempList)->firstPiece.owner = currentPlayer;
	(*tempList)->firstPiece.lastMove = turnsLeft + 1;
	(*tempList)->firstPiece.x = x;
	(*tempList)->firstPiece.y = y;
	(*tempList)->firstPiece.type = p;
	(*tempList)->next = NULL;
	
	return true;
}

/**
 * Checks correctness of the data and produces a new piece on the given position.
 * @return false if the given input is not valid,
 * @return true otherwise.
 **/
static bool produce(int x1, int y1, int x2, int y2, enum PieceType p) {
	if (incorrectMove(x1, y1, x2, y2)) {
		return false;
	}
	
	PieceList** player1 = setPlayer1();
	PieceList** player2 = setPlayer2();
	PieceList** pieceFrom = pointerToPosition(x1, y1, player1);
	if (pieceFrom == NULL) {
		return false;
	}
	if (pointerToPosition(x2, y2, player2) != NULL) {
		return false;
	}
	if ((*pieceFrom)->firstPiece.type != PEASANT || (*pieceFrom)->firstPiece.lastMove < turnsLeft + 3) {
		return false;
	}
	if (!addPiece(x2, y2, player1, p)) {
		return false;
	}
	
	(*pieceFrom)->firstPiece.lastMove = turnsLeft;
	
	return true;
}
/**
 * Chooses a field where a piece should be moved and returns coordinates.
 * @param[in] currentPiece Piece to be moved.
 * @param[in] x The value of currentPiece.x decreased by x coordinate of the nearest rival's pawn.
 * @param[in] y The value of currentPiece.y decreased by y coordinate of the nearest rival's pawn.
**/
Pair choosePosition(Piece currentPiece, int x, int y) {
	Pair* temp;
	Pair ret;
	if (x < 0 && y < 0) {
		temp = downRight;
	} else if (x < 0 && y == 0) {
		temp = right;
	} else if (x < 0 && y > 0) {
		temp = upRight;
	} else if (x == 0 && y < 0) {
		temp = down;
	} else if (x == 0 && y > 0) {
		temp = up;
	} else if (y < 0) {
		temp = downLeft;
	} else if (y == 0) {
		temp = left;
	} else {
		temp = upLeft;
	}
	
	int counter = 0;
	while (1) {
		if (temp[counter].x == 0 && temp[counter].y == 0) {
			ret.x = currentPiece.x;
			ret.y = currentPiece.y;
			break;
		}
		
		if (wrongPosition(currentPiece.x+temp[counter].x,
			currentPiece.y+temp[counter].y, 1, 1)) {
			counter++;
			continue;
		}
		
		PieceList** pointer = pointerToPosition(currentPiece.x + temp[counter].x,
			currentPiece.y + temp[counter].y, setPlayer1());
		if (pointer == NULL) {
			if (currentPiece.type == PEASANT) {
				PieceList** pointer2 = pointerToPosition(currentPiece.x + temp[counter].x,
				currentPiece.y + temp[counter].y, setPlayer2());
				if (pointer2 != NULL) {
						counter++;
						continue;
				}
			}
			ret.x = currentPiece.x + temp[counter].x;
			ret.y = currentPiece.y + temp[counter].y;
			break;			
		}
		counter++;
	}
	return ret;
}

Pair choosePeasantPosition(Piece currentPiece) {
	int tim = time(NULL);
	srand(tim);
	int num = rand() % 4;
	Pair *temp;
	Pair ret = {currentPiece.x, currentPiece.y};
	switch (num) {
		case 0:
			temp = tab1;
			break;
		case 1:
			temp = tab2;
			break;
		case 2:
			temp = tab3;
			break;
		case 3:
			temp = tab4;
			break;
		default:
			break;	
	}
	
	int counter = 0;
	while (1) {
		if (temp[counter].x == 0 && temp[counter].y == 0) {
			ret.x = currentPiece.x;
			ret.y = currentPiece.y;
			break;
		}
		
		if (wrongPosition(currentPiece.x+temp[counter].x,
			currentPiece.y+temp[counter].y, 1, 1)) {
			counter++;
			continue;
		}
		
		PieceList** pointer = pointerToPosition(currentPiece.x + temp[counter].x,
			currentPiece.y + temp[counter].y, setPlayer1());
		if (pointer == NULL) {
			if (currentPiece.type == PEASANT) {
				PieceList** pointer2 = pointerToPosition(currentPiece.x + temp[counter].x,
				currentPiece.y + temp[counter].y, setPlayer2());
				if (pointer2 != NULL) {
						counter++;
						continue;
				}
			}
			ret.x = currentPiece.x + temp[counter].x;
			ret.y = currentPiece.y + temp[counter].y;
			break;			
		}
		counter++;
	}
	return ret;
}	

/**
 * Return the coordinates of the rival's nearest pawn in the maximum metric. If there are
 * more than one such pawns, returns the coordinates of the one which is the closest
 * to my king.
 * @param[in] x Column of the piece.
 * #param[in] y Row of the piece.
 **/
Pair findNearestFoe(int x, int y) {
	int min = 2*(boardSize - 1);
	int minKing = 2*(boardSize - 1);
	int curr, currKing;
	Pair ret;
	PieceList* player2 = *setPlayer2();
	
	while (player2 != NULL) {
		curr = max(dist(x, (player2->firstPiece).x),
			dist(y, (player2->firstPiece).y));
		currKing = max(dist(x, (player2->firstPiece).x),
			dist(y, (player2->firstPiece).y));
		if (curr < min || (currKing < minKing && curr == min)) {
			min = curr;
			minKing = currKing;
			ret.x = (player2->firstPiece).x;
			ret.y = (player2->firstPiece).y;
		} 
		player2 = player2->next;
	}
	
	return ret;
}

/**
 * Moves a knight.
 * @param[in] currentPiece Piece to be moved;
 **/
void makeKnightMove(Piece currentPiece) {
	if (currentPiece.lastMove < turnsLeft + 1) {
		return;
	}
	Pair nearestFoe = findNearestFoe(currentPiece.x, currentPiece.y);
	int x = currentPiece.x - nearestFoe.x;
	int y = currentPiece.y - nearestFoe.y;
	Pair temp = choosePosition(currentPiece, x, y);
	if (temp.x == currentPiece.x && temp.y == currentPiece.y) {
		return;
	}
	printf("MOVE %d %d %d %d\n", currentPiece.x, currentPiece.y,
		temp.x, temp.y);
	move(currentPiece.x, currentPiece.y, temp.x, temp.y);
	return;
}

/**
 * Moves a peasant.
 * @param[in] currentPiece Piece to be moved.
 **/
void makePeasantMove(Piece currentPiece) {
	if (currentPiece.lastMove < turnsLeft + 3) {
		return;
	}
	
	if (producedPieces % howOften == 0) {
		Pair temp = choosePeasantPosition(currentPiece);
		if (temp.x == currentPiece.x && temp.y == currentPiece.y) {
			int x = currentPiece.x - foeKing.x;
			int y = currentPiece.y - foeKing.y;
			temp = choosePosition(currentPiece, x, y);
			if (temp.x == currentPiece.x && temp.y == currentPiece.y) {
				return;
			}
			printf("PRODUCE_KNIGHT %d %d %d %d\n", currentPiece.x, currentPiece.y,
				temp.x, temp.y);
			fflush(stdout);
			produceKnight(currentPiece.x, currentPiece.y, temp.x, temp.y);	
			return;		
		}
		producedPieces++;
		printf("PRODUCE_PEASANT %d %d %d %d\n", currentPiece.x, currentPiece.y,
			temp.x, temp.y);
		fflush(stdout);
		producePeasant(currentPiece.x, currentPiece.y, temp.x, temp.y);
	} else {
		int x = currentPiece.x - foeKing.x;
		int y = currentPiece.y - foeKing.y;
		Pair temp = choosePosition(currentPiece, x, y);
		if (temp.x == currentPiece.x && temp.y == currentPiece.y) {
			return;
		}
		printf("PRODUCE_KNIGHT %d %d %d %d\n", currentPiece.x, currentPiece.y,
			temp.x, temp.y);
		producedPieces++;
		fflush(stdout);
		produceKnight(currentPiece.x, currentPiece.y, temp.x, temp.y);
	}
	return;
}

/**
 * Makes a move of a given piece.
 * @param[in] currentPiece Piece to be moved.
 **/
void makeMove(Piece currentPiece) {
	switch ((int) currentPiece.type) {
		case KING:
			break;
		case PEASANT:
			makePeasantMove(currentPiece);
			break;
		case KNIGHT:
			makeKnightMove(currentPiece);
			break;
	}
}

/* REQUIRED FUNCTIONS */	
	
void startGame() {
	initCounter = 0;
	winner = 0;
	endTurnCounter = 0;
	firstPlayer = (PieceList*) malloc(sizeof(PieceList));
	secondPlayer = (PieceList*) malloc(sizeof(PieceList));
	firstPlayer->firstPiece.type = KING;
	firstPlayer->firstPiece.owner = 1;
	secondPlayer->firstPiece.type = KING;
	secondPlayer->firstPiece.owner = 2;
	
	PieceList** temp;
	PieceList** temp2;
	temp = &(firstPlayer->next);
	temp2 = &(secondPlayer->next);
	*temp = (PieceList*) malloc(sizeof(PieceList));
	*temp2 = (PieceList*) malloc(sizeof(PieceList));
	(*temp)->firstPiece.type = PEASANT;
	(*temp)->firstPiece.owner = 1;
	(*temp2)->firstPiece.type = PEASANT;
	(*temp2)->firstPiece.owner = 2;
	for (int i = 0; i < 2; i++) {
		temp = &(*temp)->next;
		temp2 = &(*temp2)->next;
		*temp = (PieceList*) malloc(sizeof(PieceList));
		*temp2 = (PieceList*) malloc(sizeof(PieceList));
		(*temp)->firstPiece.type = KNIGHT;
		(*temp)->firstPiece.owner = 1;
		(*temp2)->firstPiece.type = KNIGHT;
		(*temp2)->firstPiece.owner = 2;
	}
	(*temp)->next = NULL;
	(*temp2)->next = NULL;
	
	return;
}

int endGame() {
	clearAll();
	
	if (winner == 3 || winner == 0) {
			fprintf(stderr, "draw\n");
			return 1;
	} else {
		fprintf(stderr, "player %d won\n", winner);
	}
	
	if (MyID == winner) {
		return 0;
	}
	return 2;
}

bool init(int n, int k, int p, int x1, int y1, int x2, int y2) {
	if (initCounter == 0) {
		initCounter++;
		if (n < 9) {
			return false;
		}
		boardSize = n;
		if (k < 1) {
			return false;
		}
		turnsLeft = k-1;
		if (p != 1 && p != 2) {
			return false;
		}
		currentPlayer = 1;
		MyID = p;
		if (p == 1) {
			foeKing.x = x2;
			foeKing.y = y2;
			myKing.x = x1;
			myKing.y = y1;
		} else {
			foeKing.x = x1;
			foeKing.y = y1;
			myKing.x = x2;
			myKing.y = y2;
		}
		if (dist(x1, x2) < 8 && dist(y1, y2) < 8) {
			return false;
		}
		if (!checkPositions(x1, x2, y1, y2)) {
			return false;
		}
		
		PieceList** temp1 = &firstPlayer;
		PieceList** temp2 = &secondPlayer;
		while ((*temp1) != NULL) {
			(*temp1)->firstPiece.x = x1;
			(*temp1)->firstPiece.y = y1;
			(*temp1)->firstPiece.lastMove = k;
			(*temp2)->firstPiece.x = x2;
			(*temp2)->firstPiece.y = y2;
			(*temp2)->firstPiece.lastMove = k;
			temp1 = &(*temp1)->next;
			temp2 = &(*temp2)->next;
			x1++;
			x2++;
		}
		return true;
	} else {
		return false;
	}
}

int move(int x1, int y1, int x2, int y2) {
	if (incorrectMove(x1, y1, x2, y2)) {
		return 0;
	}
	
	PieceList** player1 = setPlayer1();
	PieceList** player2 = setPlayer2();
	PieceList** pieceFrom = pointerToPosition(x1, y1, player1);
	if (pieceFrom == NULL) {
		return 0;
	}
	if (pointerToPosition(x2, y2, player1) != NULL) {
		return 0;
	}
	PieceList** pieceTo = pointerToPosition(x2, y2, player2);
	
	if ((*pieceFrom)->firstPiece.lastMove == turnsLeft) {
		return 0;
	}

	if (pieceTo == NULL) {
		(*pieceFrom)->firstPiece.lastMove = turnsLeft;
		(*pieceFrom)->firstPiece.x = x2;
		(*pieceFrom)->firstPiece.y = y2;
		return 1;
	}
	
	PieceList* temp = (*pieceFrom)->next;
	PieceList* temp2 = (*pieceTo)->next;
	switch (fight((*pieceFrom)->firstPiece, (*pieceTo)->firstPiece)) {
		case 1:
			(*pieceFrom)->firstPiece.lastMove = turnsLeft;
			(*pieceFrom)->firstPiece.x = x2;
			(*pieceFrom)->firstPiece.y = y2;
			free(*pieceTo);
			*pieceTo = temp2;
			break;
		case 2:
			free(*pieceFrom);
			*pieceFrom = temp;
			break;
		case 3:
			free(*pieceFrom);
			*pieceFrom = temp;
			free(*pieceTo);
			*pieceTo = temp2;
			break;
	}
	return 2;
}

bool produceKnight(int x1, int y1, int x2, int y2) {
	return (produce(x1, y1, x2, y2, KNIGHT));
}

bool producePeasant(int x1, int y1, int x2, int y2) {
	return (produce(x1, y1, x2, y2, PEASANT));
}

bool endTurn() {
	endTurnCounter++;
	if (endTurnCounter % 2 == 0) {
		turnsLeft--;
		if (turnsLeft < 225) {
			howOften = 4;
		}
		if (turnsLeft < 205) {
			howOften = 6;
		}
		if (turnsLeft < 175) {
			howOften = 8;
		}
		if (turnsLeft < 150) {
			howOften = 12;
		}
		if (turnsLeft < 100) {
			howOften = 15;
		}
		if (turnsLeft < 75) {
			howOften = 18;
		}
		if (turnsLeft < 25) {
			howOften = 22;
		}
		currentPlayer = 1;
	} else {
		currentPlayer = 2;
	}
	return (turnsLeft < 0);
}

void makeMoves() {
	PieceList* player1 = *setPlayer1();
	
	while (player1 != NULL) {		
		makeMove(player1->firstPiece);
		if (winner != 0) {
			return;
		}
		player1 = player1->next;	
	}
	player1 = *setPlayer1();
	while (player1 != NULL) {		
		makeMove(player1->firstPiece);
		if (winner != 0) {
			return;
		}
		player1 = player1->next;	
	}	
	return;
}
