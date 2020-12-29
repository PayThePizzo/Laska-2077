#ifndef MINI_LASCA_C_LASKA_H
#define MINI_LASCA_C_LASKA_H
#endif //MINI_LASCA_C_LASKA_H
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>


// Enum & Struct for creation of Matrix and Vectors

/**
 *  @struct Struct for coordinates, i & j are the matrix coordinates
 *  @typedef location_t is the new type
 */
typedef struct location{
    int i;
    int j;
} location_t;


/** \brief New type that defines what we can find on the Laska table
 *
 * \typedef This type is to be used with every element of the board and to debug Vectors
 *
 *  \enum
 */
typedef enum element {
    excluded,
    empty,
    white_box,
    black_box,
    white_pawn,
    black_pawn,
} elem_t;


/** \brief Status defines whether a Pawn is free to move, conquered, or removed
 *
 */
typedef enum status{
    free_to_move,
    conquered,
    removed,
} status_t;


/** \brief This struct is used to create the Laska Board
 *
 */
typedef struct dama{
    location_t loc;     /* Location inside the board [i][j]*/
    elem_t type;        /* Type of Board Element */
    int height;         /* Position inside the Stack of Pawn*/
} dama_t;

/* height
 *
 *  0           Casella
 *  1           Pedina livello 1 (base)
 *  2           Pedina livello 2
 *  3           Pedina livello 3 (top)
 */

/**
 * @Struct This struct is used to create a dynamic vector for each type of element we defined in elem_t.
 */
typedef struct vector {
    dama_t *vet; /* Every element has a pointer to where it is located inside the dama*/
    status_t status;
    int top;
    int vet_dim;            /* Dimension of the vector of elements*/
    struct newbox *next;
    struct newbox *prev;
} vet_t;

/* top
 *
 * Top Pawn of the Stack    1
 * Not Top Pawn             0
 */


// Create & Free - Dama

/**
 *
 * @param rows
 * @param cols
 * @return
 */
dama_t* dama_create(int rows,int cols);


/**
 *
 * @param dama
 * @param rows
 * @param cols
 */
void dama_initialize(dama_t *dama, int rows, int cols);

/**
 *
 * @param dama
 * @param rows
 * @param cols
 */
void dama_free (dama_t *dama, int rows, int cols);

/**
 *
 * @param dama
 * @param rows
 * @param cols
 * @return
 */
int check_memory(dama_t *dama, int rows, int cols);

/**
 *
 * @param dama
 * @param rows
 * @param cols
 */
void print (dama_t *dama, int rows, int cols);

/**
 *
 * @param dama
 * @param black_vet
 * @param white_vet
 * @param w_box
 * @param b_box
 */
void dama_print(dama_t **dama, vet_t* black_vet, vet_t* white_vet, vet_t * w_box, vet_t * b_box);


//Vectors for Pawns - Vector
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
vet_t * create_vet(dama_t ** dama, int rows, int cols, elem_t type);

/** \brief Frees memory of the vector
 *
 * @param vet
 */
void free_vet(dama_t ** vet);

/** \brief Prints all the elements of the vector
 *
 * @param vet
 * @param dim
 */
void print_vet(dama_t ** vet, int dim);



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
location_t findmiddle(location_t x, location_t y);



// Menu & Auxiliary Game Functions

/** \brief Main Menu from which it is possible to choose players and game modes.
 *  @return A number 0-3 used to select the game mode.
 */
int main_menu();

/**
 *
 * @return
 */
int decision_menu();

/** @brief Displays the winner
 *
 * @param winner indicates who is the winner, either black or white.
 */
void result_menu(int winner);

// Functions for the game

/*  -2) Coin Toss
 *  -1) Legal Choice
 *      - Pedina potrebbe non potersi muovere, troppe pedine bianche intorno
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

int gamepc();

int botfight;



// Messages

/**
 *
 */
void hello();

/**
 *
 */
void goodbye();

/**
 *
 */
void credits();



// Debug Dama
void debug_dama();
