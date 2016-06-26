#include <stdio.h>
#include <stdarg.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cmocka.h"
#include "engine.h"
#include "parse.h"

/* Funkcja main modułu middle_ages.c jest zamieniana na funkcję middle_ages_main. */
extern int middle_ages_main();

/* Deklaracje funkcji określonych w engine.c jako statyczne, które
 * dodatkowo testuję */
extern struct pieceList** setPlayer1();

extern struct pieceList** setPlayer2();

extern struct pieceList** pointerToPosition(int x, int y, struct pieceList** tempList);

/* Pomocnicza funkcja inicjalizująca grę. */
	void initialise(int n, int k, int p, int x1, int y1, int x2, int y2) {
	startGame();
	init(n, k, p, x1, y1, x2, y2);
	return;
}

/* Sprawdza, czy program wyłapuje błąd, gdy próbujemy ruszyć poza planszę */
static void testMoveOutsideTheBoard(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	assert_int_equal(move(1, 1, 1, 0), 0);
	clearAll();
	initialise(9, 9, 2, 1, 9, 1, 1);
	assert_int_equal(move(1, 9, 1, 10), 0);
	clearAll();
	return;
}

/* Sprawdza, czy program wyłapuje błąd, gdy próbujemy ruszyć na pole
 * zajmowane przez inną naszą jednostkę */
static void testMoveIntoOtherPawn(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	assert_int_equal(move(1, 1, 2, 1), 0);
	clearAll();
	initialise(9, 9, 2, 1, 9, 1, 1);
	assert_int_equal(move(4, 9, 3, 9), 0);
	clearAll();
	return;
}

/* Sprawdza, czy program wyłapuje błąd, gdy próbujemy ruszyć na pole oddalone
 * o więcej lub mniej niż 1 w metryce maksimum. */
static void testTooFarMove(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	assert_int_equal(move(1, 1, 1, 3), 0);
	assert_int_equal(move(1, 1, 1, 1), 0);
	clearAll();
	return;
}

/* Sprawdza, czy program wyłapuje błąd, gdy próbujemy wykonać ruch
 * nieistniejącą jednostką. */
static void testMoveOfNotExistingPawn(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	assert_int_equal(move(1, 4, 1, 5), 0);
	clearAll();
	return;
}
/* Sprawdza, czy program wyłapuje błąd, gdy próbujemy wykonać ruch
 * jednostką, ktorą wykonaliśmy już ruch w danej turze. */
static void testMoveOfAlreadyMovedPawn(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	move(1, 1, 1, 2);
	assert_int_equal(move(1, 2, 1, 3), 0);
	clearAll();
	return;
}

/* Sprawdza, czy program wykrywa poprawne ruchy */
static void testOfCorrectMove(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	assert_int_equal(move(1, 1, 1, 2), 1);
	assert_int_equal(move(2, 1, 2, 2), 1);
	assert_int_equal(move(3, 1, 4, 2), 1);
	assert_int_equal(move(4, 1, 3, 2), 1);
	endTurn();
	assert_int_equal(move(1, 9, 2, 8), 1);
	assert_int_equal(move(2, 9, 1, 9), 1);
	assert_int_equal(move(4, 9, 5, 9), 1);
	clearAll();
	return;
}

/* Sprawdza, czy program wykrywa walkę */
static void testOfMoveToFight(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	move(2, 1, 2, 2);
	endTurn();
	move(2, 9, 2, 8);
	endTurn();
	move(2, 2, 2, 3);
	endTurn();
	move(2, 8, 2, 7);
	endTurn();
	move(2, 3, 2, 4);
	endTurn();
	move(2, 7, 2, 6);
	endTurn();
	move(2, 4, 2, 5);
	endTurn();
	assert_int_equal(move(2,6,2,5), 2);
	clearAll();
	return;
}

/* Sprawdza, czy program wykrywa nieprawidłową liczbę argumentów */
static void testOfMoveIncorrectArgumentsNumber(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	Command newCommand = parseCommand("MOVE 1 1 1 2 2\n");
	assert_string_equal("WRONG_INPUT", newCommand.name);
	newCommand = parseCommand("MOVE 1 1\n");
	assert_string_equal("WRONG_INPUT", newCommand.name);
	return;
}

/* Sprawdza, czy program wykrywa błędy na wejściu innego typu */
static void testOfMoveDifferentInputErrors(void **state) {
	initialise(9, 9, 2, 1, 1, 1, 9);
	Command newCommand = parseCommand("MOVE 1 1 1 2 \n");
	assert_string_equal("WRONG_INPUT", newCommand.name);
	newCommand = parseCommand("MOVE 1 1 1 2");
	assert_string_equal("WRONG_INPUT", newCommand.name);
	newCommand = parseCommand("MOVE 1 1 1d 2\n");
	assert_string_equal("WRONG_INPUT", newCommand.name);
	newCommand = parseCommand(" MOVE 1 1 1 2\n");
	assert_string_equal("WRONG_INPUT", newCommand.name);
	newCommand = parseCommand("MOVE 1 1 1   2\n");
	assert_string_equal("WRONG_INPUT", newCommand.name);
	clearAll();
	return;
}
/* Sprawdza, czy program podaje poprawny kod wyjścia */
static void testOfReturnCodeCorrectness(void **state) {
 	initialise(9, 9, 2, 1, 1, 1, 9);
 	move(1, 1, 1, 2);
	endTurn();
	move(1, 9, 1, 8);
	endTurn();
	move(1, 2, 1, 3);
	endTurn();
	move(1, 8, 1, 7);
	endTurn();
	move(1, 3, 1, 4);
	endTurn();
	move(1, 7, 1, 6);
	endTurn();
	move(1, 4, 1, 5);
	endTurn();	
	move(1, 6, 1, 5);
	assert_int_equal(endGame(), 1);
 	initialise(9, 9, 2, 1, 1, 1, 9);
 	move(3, 1, 2, 2);
	endTurn();
	move(1, 9, 2, 8);
	endTurn();
	move(2, 2, 2, 3);
	endTurn();
	move(2, 8, 2, 7);
	endTurn();
	move(2, 3, 2, 4);
	endTurn();
	move(2, 7, 2, 6);
	endTurn();
	move(2, 4, 2, 5);
	endTurn();	
	move(2, 6, 2, 5);
	assert_int_equal(endGame(), 2);
 	initialise(9, 9, 2, 1, 1, 1, 9);
 	move(1, 1, 2, 2);
	endTurn();
	move(3, 9, 2, 8);
	endTurn();
	move(2, 2, 2, 3);
	endTurn();
	move(2, 8, 2, 7);
	endTurn();
	move(2, 3, 2, 4);
	endTurn();
	move(2, 7, 2, 6);
	endTurn();
	move(2, 4, 2, 5);
	endTurn();	
	move(2, 6, 2, 5);
	assert_int_equal(endGame(), 0);
	return;
}

/* Sprawdza, czy funkcja pointerToPosition() zwraca poprawny wynik dla różnych,
 * poprawnych danych. */
static void testOfCorrectDataPTP(void **state) {
 	initialise(9, 9, 2, 1, 1, 1, 9);
	struct pieceList** list = pointerToPosition(1, 1, setPlayer1());
	assert_true(!(list == NULL));
    list = pointerToPosition(4, 1, setPlayer1());	
	assert_true(!(list == NULL));
	move(1, 1, 1, 2);
	endTurn();
    list = pointerToPosition(4, 1, setPlayer2());
	assert_true(!(list == NULL)); 
	list = pointerToPosition(4, 9, setPlayer1());
	assert_true(!(list == NULL));
	endTurn();
	endTurn();
	endTurn();
	produceKnight(2, 1, 2, 2);
	endTurn();
	producePeasant(2, 9, 2, 8);
    list = pointerToPosition(2, 2, setPlayer2());
	assert_true(!(list == NULL));
    list = pointerToPosition(2, 8, setPlayer1());
	assert_true(!(list == NULL));	
	endTurn();	
	return;
}

/* Testuje, czy funkcja pointerToPosition() wykrywa, 
 * że dane na wejściu są niepoprawne. */
static void testOfIncorrectDataPTP(void **state) {
	struct pieceList** list = pointerToPosition(1, 1, setPlayer1());
	assert_true(list == NULL);
    list = pointerToPosition(5, 1, setPlayer1());	
	assert_true(list == NULL);
    list = pointerToPosition(8, 8, setPlayer2());	
	assert_true(list == NULL);	
	move(2, 2, 2, 3);
	endTurn();
	move(2, 8, 2, 7);
	endTurn();
	move(2, 3, 2, 4);
	endTurn();
	move(2, 7, 2, 6);
	endTurn();
	move(2, 4, 2, 5);
	endTurn();
	move(2, 6, 2, 5);
    list = pointerToPosition(2, 5, setPlayer1());	
	assert_true(list == NULL);
	clearAll();
	return;
}
int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testMoveOutsideTheBoard),
        cmocka_unit_test(testMoveIntoOtherPawn),
        cmocka_unit_test(testTooFarMove),
        cmocka_unit_test(testMoveOfNotExistingPawn),
        cmocka_unit_test(testMoveOfAlreadyMovedPawn),
        cmocka_unit_test(testOfCorrectMove),
        cmocka_unit_test(testOfMoveToFight),
        cmocka_unit_test(testOfMoveIncorrectArgumentsNumber),
        cmocka_unit_test(testOfMoveDifferentInputErrors),
        cmocka_unit_test(testOfReturnCodeCorrectness),
        cmocka_unit_test(testOfCorrectDataPTP),
        cmocka_unit_test(testOfIncorrectDataPTP)
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
