#ifndef LASKA_LASKA_H
#define LASKA_LASKA_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>

/** \mainpage Laska
 *
 *  This library implements the Mini-Laska Project of Gianmaria Pizzo and Aleksandra Gjorgievska
 *
 */

/**
 *
 *
 * @struct Laska board coordinates
 */
typedef struct point{
    int j, i;
} point;

/*
 * Id
 * 0-> white box
 * 1-> black box
 * 2-> white pawn
 * 3-> black pawn
 * 4-> white dama
 * 5-> black dama
*/

/**
 * If the cell is empty it represents the color, otherwise it represents the pawn (obviously the cell is white).
 *
 * @struct Box of Laska board
 */
typedef struct boxpawn {
    int id;
    struct boxpawn *next;
} boxpawn;


/**
 *
 *
 * @struct Laska board
 */
typedef struct dama{
    int cols;
    int rows;
    boxpawn ***mat;
} tgame;



// Create, Initialize & Free
/**
 * Creates a new Laska Board
 *
 * @param cols
 * @param rows
 * @return
 */
tgame* create(int cols,int rows);

/**
 *
 * @param dama
 * @param cols
 * @param rows
 */
void initialize(tgame * dama, int cols, int rows);

/**
 *
 * @param result
 * @param rows
 * @param cols
 */
void freegame(tgame *result, int rows, int cols);



// Auxiliary Functions

/**
 *
 * @return
 */
int coin_toss();

/**
 *
 *
 * @param dim
 * @return
 */
int convert(int dim);

/**
 * Checks the number
 *
 * @param dim
 * @return
 */
int check_number(int dim);

/**
 *
 *
 * @param result
 * @param rows
 * @param cols
 */
void print(tgame result, int rows , int cols);



// Core Functions

/**
 *
 *
 * @param dama
 * @param pedina
 * @param r
 * @param c
 */
void add(tgame *dama, int pedina, int r, int c);

/**
 *
 *
 * @param dama
 * @param r
 * @param c
 * @return
 */
int remove_pawn(tgame *dama, int r, int c);

/**
 *
 *
 * @param dama
 * @param a
 * @return
 */
int white_move_check(tgame *dama, point a);

/**
 *
 *
 * @param dama
 * @param a
 * @return
 */
int black_move_check(tgame *dama, point a);

/**
 *
 *
 * @param dama
 * @param a
 * @return
 */
int dama_move_check(tgame *dama, point a);

/**
 *
 *
 * @param dama
 * @param a
 * @param turn
 * @return
 */
int white_capture_check(tgame *dama, point a, int turn);

/**
 *
 *
 * @param dama
 * @param a
 * @param turn
 * @return
 */
int black_capture_check(tgame *dama, point a, int turn);

/**
 *
 *
 * @param dama
 * @param a
 * @param turn
 * @return
 */
int dama_capture_check(tgame *dama, point a, int turn);

/**
 *
 *
 * @param dama
 * @param turn
 * @return
 */
int player_can_capture(tgame *dama,int turn);

/**
 *
 *
 * @param dama
 * @param turn
 * @return
 */
int player_can_move(tgame *dama, int turn);

/**
 *
 *
 * @param dama
 * @param turn
 * @param a
 * @return
 */
int legal_choice(tgame *dama, int turn, point a);

/**
 *
 *
 * @param dama
 * @param turn
 * @param a
 * @param b
 * @param have_to_capture
 * @return
 */
int legal_move (tgame *dama, int turn, point a, point b, int have_to_capture);

/**
 *
 *
 * @param a
 * @param b
 * @return
 */
point findmiddle(point a, point b);

/**
 *
 *
 * @param dama
 * @param a
 * @param b
 */
void move (tgame *dama, point a, point b);

/**
 *
 *
 * @param turn
 * @return
 */
int enemy(int turn);

/**
 *
 *
 * @param dama
 * @param a
 * @param turn
 * @return
 */
int is_promoted (tgame *dama, point a, int turn);

/**
 *
 *
 * @param dama
 * @param turn
 */
void promotion(tgame *dama, int turn);

/**
 *
 *
 * @param dama
 * @param turn
 * @return
 */
int victory(tgame *dama, int turn);

/**
 *
 *
 * @param dama
 * @param rows
 * @param cols
 * @return
 */
int game(tgame *dama, int rows, int cols);



//Menu

/**
 *
 *
 * @return
 */
int main_menu();

/**
 *
 *
 * @return
 */
int decision_menu();

/**
 *
 *
 * @param winner
 * @return
 */
void result_menu(int winner);



//Messages
/**
 *
 *
 *
 */
void hello();

/**
 *
 *
 *
 */
void goodbye();

/**
 *
 *
 *
 */
void credits();


#endif //LASKA_LASKA_H
