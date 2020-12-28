#ifndef MINI_LASCA_C_LASKA_H
#define MINI_LASCA_C_LASKA_H
#endif //MINI_LASCA_C_LASKA_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

// Enum & Struct for creation of Matrix and Vectors

/** \brief Struct for coordinates
 *  \struct i & j are the matrix coordinates
 *  \typedef newpoint_t is the new type
 */
typedef struct newpoint{
    int i;
    int j;
} newpoint_t;


/** \brief New type that defines what we can find on the Laska table
 *
 * \typedef This type is to be used with every element of the board
 *
 *  \enum
 */
typedef enum board_elem {
    white_box,
    black_box,
    white_pawn,
    black_pawn,
} elem_t;


/** \brief This struct is used to create a dynamic vector for each type of element we defined in elem_t.
 *
 */
typedef struct newbox{
    newpoint_t loc;
    elem_t type;
    int height;
    int dim;
    struct newbox *next;
    struct newbox *prev;
} piece_t;



// Create & Free - Dama
/*  1) Create
 *  2) Free
 *  3) Print
 */

//Inserisci qui



//Vectors for Pawns
/* 1) Crea Vettore generico
 * 2) Libera Vettore
 * 3) Printa Vettore
 */

/** \brief Creates a vector of fixed dimension (7).
 *
 * @param dama
 * @param rows
 * @param cols
 * @param type
 * @return vectors whose elements are all type "type"
 */
piece_t * create_vet(tgame * dama, int rows, int cols, elem_t type);

/** \brief Frees memory of the vector
 *
 * @param vet
 */
void free_vet(piece_t *vet);

/** \brief Prints all the elements of the vector
 *
 * @param vet
 * @param dim
 */
void print_vet(piece_t *vet, int dim);



//Auxiliary functions

/**
 *
 * @param dim
 * @return
 */
int check_number(int dim);


/**
 *
 * @return
 */
int convert();


/**
 *
 * @param a
 * @param b
 * @return
 */
point findmiddle(point a, point b);



// Menu & Auxiliary Game Functions

/** \brief Main Menu from which it is possible to choose players and game modes.
 *  @return A number 0-3 used to select the game mode.
 */
int main_menu();


/** \brief Player vs Player Mode (can be a single or two human players).
 *
 * @param dama
 * @param rows
 * @param cols
 * @return
 */



// Functions for the game

/*  -2) Coin Toss
 *  -1) Legal Choice
 *   0) Legal Move
 *
 *  1) Check Limit -> dato il puntatore alla pedina, mi dice se la pedina e' troppo alta
 *  2) Check Grow -> dato il puntatore alla pedina e le coordinate in cui viene inserita, mi dice se la pedina cresce
 *  3) Move
 *  4) Remove Pawn
 *  5) Grow -> Aggiunge uno alla pedina, rimuove la pedina avversaria
 *  6) Check Win -> date le regole del gioco, la scacchiera e le pedine rimaste, mi dice se una mossa fa vincere la partita
 */



// Games

/*  1) Single Player    - Game
 *  2) 2 Players        - Game
 *  3) Player vs Pc     - Gamepc
 *  4) Pc vs Pc         - BotFight
 */

int game();
