#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/* DATA STRUCTURE */

enum PieceType {KING, KNIGHT, PEASANT};

typedef struct piece {
	enum PieceType type;
	int owner, x, y, lastMove;
} Piece;

typedef struct pieceList {
	Piece firstPiece;
	struct pieceList* next;
} PieceList;

/* REQUIRED DATA */

	PieceList* firstPlayer;
	PieceList* secondPlayer;
	int boardSize;
	int turnsLeft;
	char topleft[11][11];
	
/* AUXILIARY FUNCTIONS */

void clearPieceList(PieceList* list) {
	if (list == NULL) {
		return;
	}
	if (list->next != NULL) {
		clearPieceList(list->next);
	}
	free(list);
	return;
}
void clearAll() {
	clearPieceList(firstPlayer);
	clearPieceList(secondPlayer);
	return;
}

void putTopleft(int x, int y, enum PieceType p, int pl) {
	if (x > 10 || y > 10) {
		return;
	}
	
	switch ((int) p) {
		case KING:
			topleft[y][x] = (pl == 1) ?'K':'k';
 			break;
		case KNIGHT:
			topleft[y][x] = (pl == 1) ?'R':'r';
			break;
		case PEASANT:
			topleft[y][x] = (pl == 1) ?'C':'c';
			break;
		}
	return;
}

void clearPosition(int x, int y) {
	if (x > 10 || y > 10) {
		return;
	}
	topleft[y][x] = '.';
}

int dist(int a, int b) {
	if (a > b) {
		return a - b;
	}
	return b - a;
}

int currentPlayer;
int winner = 0;
int endTurnCounter = 0;
int initCounter = 0;
int initValue[7];

bool checkWinner() {
	return (winner != 0);
}

int fight(Piece p1, Piece p2) {
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

bool checkPositions(int x1, int x2, int y1, int y2) {
	bool ret = true;
	ret &= (x1 > 0 && x1 < boardSize - 2);
	ret &= (x2 > 0 && x2 < boardSize - 2);
	ret &= (y1 > 0 && y1 <= boardSize);
	ret &= (y2 > 0 && y2 <= boardSize);
	return ret;
}

bool wrongPosition(int x1, int y1, int x2, int y2) {
	bool ret = true;
	ret &= (x1 > 0 && x1 <= boardSize);
	ret &= (x2 > 0 && x2 <= boardSize);
	ret &= (y1 > 0 && y1 <= boardSize);
	ret &= (y2 > 0 && y2 <= boardSize);
	return !ret;
}

bool incorrectMove(int x1, int y1, int x2, int y2) {
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

bool checkInitValues(int n, int k, int p, int x1, int y1, int x2, int y2) {
	bool ret = true;
	ret &= (n == initValue[0]);
	ret &= (k == initValue[1]);
	ret &= (p == initValue[2]);
	ret &= (x1 == initValue[3]);
	ret &= (y1 == initValue[4]);
	ret &= (x2 == initValue[5]);
	ret &= (y2 == initValue[6]);
	return ret;
}

PieceList** setPlayer1() {
	if (currentPlayer == 1) {
		return &firstPlayer;
	} else {
		return &secondPlayer;
	}
}

PieceList** setPlayer2() {
	if (currentPlayer == 1) {
		return &secondPlayer;
	} else {
		return &firstPlayer;
	}	
}	

PieceList** pointerToPosition(int x, int y, PieceList** tempList) {
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

bool addPiece(int x, int y, PieceList** tempList, enum PieceType p) {
	
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

bool produce(int x1, int y1, int x2, int y2, enum PieceType p) {
	if (incorrectMove(x1, y1, x2, y2)) {
		return 0;
	}
	
	PieceList** player1 = setPlayer1();
	PieceList** player2 = setPlayer2();
	PieceList** pieceFrom = pointerToPosition(x1, y1, player1);
	if (pieceFrom == NULL) {
		return 0;
	}
	if (pointerToPosition(x2, y2, player2) != NULL) {
		return 0;
	}
	if ((*pieceFrom)->firstPiece.type != PEASANT || (*pieceFrom)->firstPiece.lastMove < turnsLeft + 3) {
		return 0;
	}
	if (!addPiece(x2, y2, player1, p)) {
		return 0;
	}
	
	(*pieceFrom)->firstPiece.lastMove = turnsLeft;
	putTopleft(x2, y2, p, currentPlayer);
	
	return 1;
}

/* REQUIRED FUNCTIONS */	
	
void startGame() {
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
	
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			topleft[i][j] = '.';
		}
	}
	return;
}

void endGame() {
	clearAll();
	if (winner == 3 || winner == 0) {
			fprintf(stderr, "draw\n");
	} else {
		fprintf(stderr, "player %d won\n", winner);
	}
	return;
}

void printTopleft() {
	int k = boardSize;
	if (10 < k) {
		k = 10;
	}
	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= k; j++) {
			printf("%c", topleft[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

bool init(int n, int k, int p, int x1, int y1, int x2, int y2) {
	if (initCounter == 0) {
		initCounter++;
		if (n < 9) {
			return false;
		}
		initValue[0] = n;
		boardSize = n;
		if (k < 1) {
			return false;
		}
		initValue[1] = k;
		turnsLeft = k-1;
		if (p != 1 && p != 2) {
			return false;
		}
		currentPlayer = 1;
		initValue[2] = 3 - p;
		if (dist(x1, x2) < 8 && dist(y1, y2) < 8) {
			return false;
		}
		if (!checkPositions(x1, x2, y1, y2)) {
			return false;
		}
		initValue[3] = x1;
		initValue[4] = y1;
		initValue[5] = x2;
		initValue[6] = y2;
		PieceList** temp1 = &firstPlayer;
		PieceList** temp2 = &secondPlayer;
		while ((*temp1) != NULL) {
			(*temp1)->firstPiece.x = x1;
			(*temp1)->firstPiece.y = y1;
			(*temp1)->firstPiece.lastMove = k;
			(*temp2)->firstPiece.x = x2;
			(*temp2)->firstPiece.y = y2;
			(*temp2)->firstPiece.lastMove = k;
			putTopleft(x1, y1, (*temp1)->firstPiece.type, 1);
			putTopleft(x2, y2, (*temp2)->firstPiece.type, 2);
			temp1 = &(*temp1)->next;
			temp2 = &(*temp2)->next;
			x1++;
			x2++;
		}
		return true;
	} else {
		return checkInitValues(n, k, p, x1, y1, x2, y2);
	}
}

bool move(int x1, int y1, int x2, int y2) {
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
	
	clearPosition(x1, y1);
	if (pieceTo == NULL) {
		(*pieceFrom)->firstPiece.lastMove = turnsLeft;
		(*pieceFrom)->firstPiece.x = x2;
		(*pieceFrom)->firstPiece.y = y2;
		putTopleft(x2, y2, (*pieceFrom)->firstPiece.type, (*pieceFrom)->firstPiece.owner);
		return 1;
	}
	PieceList* temp = (*pieceFrom)->next;
	PieceList* temp2 = (*pieceTo)->next;
	switch (fight((*pieceFrom)->firstPiece, (*pieceTo)->firstPiece)) {
		case 1:
			(*pieceFrom)->firstPiece.lastMove = turnsLeft;
			(*pieceFrom)->firstPiece.x = x2;
			(*pieceFrom)->firstPiece.y = y2;
			putTopleft(x2, y2, (*pieceFrom)->firstPiece.type, (*pieceFrom)->firstPiece.owner);
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
			clearPosition(x2, y2);
			free(*pieceTo);
			*pieceTo = temp2;
	}
	return 1;
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
		currentPlayer = 1;
	} else {
		currentPlayer = 2;
	}
	return (turnsLeft < 0);
}
