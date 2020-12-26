#ifndef MINI_LASCA_C_LASKA_H
#define MINI_LASCA_C_LASKA_H
#endif //MINI_LASCA_C_LASKA_H


/*
leggenda id
0-> cella bianca
1-> cella nera
2-> pedina bianca
3-> pedina nera
4-> pedina bianca promossa
5-> pedina nera promossa
*/

enum ide {
    white_empty_box,
    black_box,
    white_pawn,
    black_pawn,
    w_dama_pawn,
    b_dama_pawn
};


typedef enum ide t_ide;


/**
 *
 */

typedef struct point{
    int x, y;
} point;


/**
 *
 */

typedef struct boxpawn {                /*se la cella è vuota rappresenta il colore, sennè rappresenta la pedina (ovviamente la cella è bianca)*/
    int id;
    struct boxpawn *next;
} boxpawn;


/**
 *
 */
typedef struct dama{
    int cols;
    int rows;
    boxpawn ***mat;
} tgame;

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
void official_print(tgame result, int rows , int cols);

/**
 *
 * @param result
 * @param rows
 * @param cols
 */
void private_print(tgame result, int rows , int cols);

/**
 *
 * @param result
 * @param rows
 * @param cols
 */
void freegame(tgame *result, int rows, int cols);

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
 * @param a
 * @param b
 */
void move (tgame *dama, point a, point b);

/**
 *
 * @param dama
 * @param a
 * @param b
 * @return
 */
int legal_move (tgame *dama, point a, point b);

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
 * @param dama
 * @param rows
 * @param cols
 * @return
 */

int coin_toss(){

}

/**
 *
 */
void main_menu();

/**
 *
 * @param dama
 * @param rows
 * @param cols
 * @return
 */
int game(tgame *dama, int rows, int cols);