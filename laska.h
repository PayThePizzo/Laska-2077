#ifndef MINI_LASCA_C_LASKA_H
#define MINI_LASCA_C_LASKA_H
#endif //MINI_LASCA_C_LASKA_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

/*
legenda id
0-> cella bianca
1-> cella nera
2-> pedina bianca
3-> pedina nera
4-> pedina bianca promossa
5-> pedina nera promossa
*/

/** \typedef
 *
 *  \enum
 */
typedef enum ide {
    white_empty_box,
    black_box,
    white_pawn,
    black_pawn,
    w_dama_pawn,
    b_dama_pawn
} t_ide;


/** \typedef
 *
 *  \enum
 */
typedef enum gamemode {
    one_p,
    two_p,
    p_pc_p,
    pc_pc_p
} t_gmode;


/** \typedef
 *
 *  \enum
 *
 */
typedef struct point{
    int x, y;
} point;


/** \typedef
 *
 *  \struct
 *
 */
typedef struct boxpawn {                /*se la cella è vuota rappresenta il colore, sennè rappresenta la pedina (ovviamente la cella è bianca)*/
    int id;
    struct boxpawn *next;
} boxpawn;


/** \typedef
 *
 *  \struct
 *
 */
typedef struct dama{
    int cols;
    int rows;
    boxpawn ***mat;
} tgame;

//vettore delle pedine disponibili
//Mi dice la posizione nella scacchiera di ogni pedina
//Mi dice quanto alta e'
//Mi da l'indirizzo di memoria di ciascuna pedina
typedef struct pawnvect{
    int cols;
    int rows;
    int height;

} pawnvect_t;


/********** Create & Free **********/

/**
 *
 * @param cols
 * @param rows
 * @return
 */
tgame* create(int cols,int rows);

/**
 *
 * @param result
 * @param rows
 * @param cols
 */

void freegame(tgame *result, int rows, int cols);

black_vet_create();

void black_vet_free();

white_vet_create();

void white_vet_free();

/********** Legal Choice & Move **********/

/**
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
 * @param dama
 * @param a
 * @param b
 * @return
 */
int legal_choice(tgame *dama, point a, point b);

/**
 *
 * @param dim
 * @return
 */
int check_number(int dim);

/********** Print **********/

/**
 *
 * @param result
 * @param rows
 * @param cols
 */
void official_print(tgame result, int rows , int cols);

/**
 *
 * @param result
 * @param rows
 * @param cols
 */
void private_print(tgame result, int rows , int cols);


/********** Conversion **********/

/**
 *
 * @return
 */
int convert();

/**
 *
 * @param dama
 * @param pedina
 * @param r
 * @param c
 */


/********** Grow & Remove, Auxiliary **********/

void add(tgame *dama, t_ide pedina, int r, int c);

/**
 *
 * @param dama
 * @param r
 * @param c
 * @return
 */
int remove_pawn(tgame *dama, int r, int c);

/**
 *
 * @param a
 * @param b
 * @return
 */
point findmiddle(point a, point b);

/**
 *
 * @param dama
 * @param turn
 */
void promotion(tgame *dama, int turn);


/********** Move Pawn **********/

/**
 *
 * @param dama
 * @param a
 * @param b
 */
void move (tgame *dama, point a, point b);


/********** Auxiliary General Functions **********/

/**
 *
 * @return
 */
int coin_toss();



/********** Menu & Auxiliary Game Functions **********/

/** \brief Main Menu from which it is possible to choose players and game modes.
 *
 */
int main_menu();

/** \brief Player vs Player Mode (can be a single or two human players).
 *
 * @param dama
 * @param rows
 * @param cols
 * @return
 */
int game(tgame *dama, int rows, int cols);

//dato il puntatore alla pedina, mi dice se la pedina e' troppo alta
int check_limit();

//dato il puntatore alla pedina e le coordinate in cui viene inserita, mi dice se la pedina cresce
int check_grow();

//date le regole del gioco, la scacchiera e le pedine rimaste, mi dice se una mossa fa vincere la partita
/**
 *
 * @param dama
 * @param rows
 * @param cols
 * @return
 */
int check_win(tgame *dama, int rows, int cols);


/********** Game Flow **********/

/**
 *
 * @param dama
 * @param rows
 * @param cols
 * @return
 */
int game_flow(tgame *dama, int rows, int cols);