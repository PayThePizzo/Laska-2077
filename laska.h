#ifndef LASKA_LASKA_H
#define LASKA_LASKA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <string.h>

/** \mainpage Laska
 *
 *  This library implements the Mini-Laska Project of Gianmaria Pizzo and Aleksandra Gjorgievska
 *
 */

/**
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
 * This struct rappresents one element of a list of points.
 *
 * @struct point node
 */
typedef struct point_cell{
    point p;
    struct point_cell * next;
} point_cell;

/**
 * This struct has the size of the list and the pointer to the head of the list.
 *
 * @struct list of points
 */
typedef struct point_list{
    int dim;
    point_cell * list;
} point_list;

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
 * @struct Laska board
 */
typedef struct dama{
    int cols;
    int rows;
    boxpawn ***mat;
} tgame;




/**
 * Creates a new Laska Board.
 *
 * @param cols columns size
 * @param rows rows size
 * @return a pointer to the new structure.
 */
tgame* create(int cols,int rows);

/**
 * Creates a list of the possible pawn you can choose to move.
 *
 * 
 * 
 * @return the list and the size of the new points list
 */
point_list * create_choices_list();

/**
 * Initializes the colors of the boxes and places the pawns.
 *
 * @param dama laska board
 * @param cols columns size
 * @param rows rows size
 */
void initialize(tgame * dama, int cols, int rows);

/**
 * Frees the whole Laska board structure.
 *
 * @param result laska board
 * @param rows rows size
 * @param cols columns size
 */
void freegame(tgame *result, int rows, int cols);

/**
 * Frees the list of points.
 *
 * 
 * @param pointer to the head of the list to free
 */
void free_choices_list(point_list * l);

/**
 * Read a character from the keyboard. In case the letter is not correct, the function is repeated until a valid letter is typed.
 *
 * @param dim
 * @return  the ASCII code corresponding to the letter representing the column
 */
int convert(int dim);

/**
 * Checks the number.
 *
 * @param dim Laska board size
 * @return the row number
 */
int check_number(int dim);

/**
 * Prints the laska board at the moment, full board.
 *
 * @param dama Laska board
 * @param rows rows size
 * @param cols columns size
 */
void print(tgame dama, int rows , int cols);



/**
 * Puts the pawn given in input at the end of the list of pieces of the position given in input.
 *
 * @param dama Laska board
 * @param pawn the captured pawn that ca be placed on the bottom of the pawn stack
 * @param r the row number of the box in which to place the pawn on bottom of the stack
 * @param c the column number of the box in which to place the pawn on bottom of the stack
 */
void add(tgame *dama, int pawn, int r, int c);

/**
 * Removes the top piece of the tower in the given position and returns it in output.
 *
 * @param dama Laska board
 * @param r the row number of the box in which to place the pawn on top of the stack
 * @param c the column number of the box in which to place the pawn on top of the stack
 * @return the top pawn in position [r][c]
 */
int remove_pawn(tgame *dama, int r, int c);

/**
 * Checks if a non-promoted white pawn has the possibility to move, it means that at least one between the 2 diagonals forward is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @return returns 1 if it has the possibility to move, 0 otherwise
 */
int white_move_check(tgame *dama, point a);

/**
 * Checks if a non-promoted black pawn has the possibility to move, it means that at least one between the 2 diagonals forward is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @return returns 1 if it has the possibility to move, 0 otherwise
 */
int black_move_check(tgame *dama, point a);

/**
 * Checks if promoted dama pawn has the possibility to move, it means that at least one between the 4 diagonals is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @return returns 1 if it has the possibility to move, 0 otherwise
 */
int dama_move_check(tgame *dama, point a);

/**
 * Checks if a non-promoted white pawn has the possibility to capture,
 * if that box has on the diagonal ahead an enemy pawn and the next one on the diagonal is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @param turn current game turn
 * @return returns 1 if it has the possibility to capture a foe, 0 otherwise
 */
int white_capture_check(tgame *dama, point a, int turn);

/**
 * Checks if a non-promoted black pawn has the possibility to capture,
 * if that box has on the diagonal ahead an enemy pawn and the next one on the diagonal is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @param turn current game turn
 * @return returns 1 if it has the possibility to capture a foe, 0 otherwise
 */
int black_capture_check(tgame *dama, point a, int turn);

/**
 * Checks if a promoted dama pawn has the possibility to capture,
 * if that box has on one of the 4 diagonal an enemy pawn and the next one on the diagonal is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @param turn current game turn
 * @return returns 1 if it has the possibility to capture a foe, 0 otherwise
 */
int dama_capture_check(tgame *dama, point a, int turn);

/**
 * Checks all the pawns on the board and checks if at least one of your pieces has a chance to capture the opponent's one.
 *
 * @param dama Laska board
 * @param turn current game turn
 * @return returns 1 if the player can capture in the current turn, 0 otherwise
 */
int player_can_capture(tgame *dama,int turn);

/**
 * Checks all the pawns on the board and checks if at least one of your pieces has a chance to move to an other box.
 *
 * @param dama Laska board
 * @param turn current game turn
 * @return returns 1 if the player can move at least 1 pawn, 0 otherwise
 */
int player_can_move(tgame *dama, int turn);

/**
 * Checks that the pawn contained in the selected box is the pawn of the player whose turn it is,
 * also checks if the pawn can be moved and if there is the possibility of conquering, the player select that pawn.
 *
 * @param dama Laska board
 * @param turn current game turn
 * @param a the row and column coordinates of the selected box
 * @return  7 if you can't select that box because i's not your pawn, 8 if the player can choose that box but now you must capture foe's pawn, 9 if you can move, 10 if the selected pawn is not free to move ,11 if you are forced to capture so you have to choose an other pawn
 */
int legal_choice(tgame *dama, int turn, point a);

/**
 * Controls the player can move from pawn a to b following the Mini-Laska-rules.
 *
 * @param dama Laska board
 * @param turn current game turn
 * @param a the row and column coordinates of the origin box
 * @param b the row and column coordinates of the destination box
 * @param have_to_capture the parameter returned by legal_chice, if the value is 8, it means that the choosed pawn is correct but now the player is forced to capture
 * @return 0 if it doesn't violate the rules, code_error(1) if you are forced to capture foe's pawn but you are moving somewhere else,
 *         code_error(2) if dama is trying to capture in a wrong way, code_error(3) if a pawn is trying to capture in a wrong way,
 *         code_error(4) if dama is not moving on one of the 4 free nearby diagonals, code_error(5) id a pawn is not moving on one of the 2 forward diagonals,
 *         code_error(6) it's not possible to move in boxes that aren't white and empty
 */
int illegal_move (tgame *dama, int turn, point a, point b, int have_to_capture);

/**
 * Takes 2 points and returns the point in between.
 *
 * @param a the row and column coordinates of the origin box
 * @param b the row and column coordinates of the destination box
 * @return the row and column coordinates of the middle box
 */
point findmiddle(point a, point b);

/**
 * Moves the pawn from point a to point b.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the origin box
 * @param b the row and column coordinates of the destination box
 */
void move (tgame *dama, point a, point b);

/**
 * Returns the opponent's id code, it is used to change turns or to find opponent's pieces.
 *
 * @param turn current game turn
 * @return if it takes white as input it returns black, if it takes black input it returns white
 */
int enemy(int turn);

/**
 * Checks if the pawn is a dama.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @param turn current game turn
 * @return returns 1 if the selected box contains a promoted pawn, 0 otherwise.
 */
int is_promoted (tgame *dama, point a, int turn);

/**
 * Promotes the pawn if it reaches the other side of the board.
 *
 * @param dama Laska board
 * @param turn current game turn
 */
void promotion(tgame *dama, int turn);

/**
 * Checks if there has been a victory.
 *
 * @param dama Laska board
 * @param rows rows size
 * @param cols columns size
 * @param turn current game turn
 * @param moves current moves to print
 * @return 0 if no one has won yet, 1 if white has won, 2 if black has won
 */
int victory(tgame *dama, int rows, int cols, int turn, int moves);

/**
 * It adds at the end of a list the coordinates of a pawn.
 *
 * @param l the list to modify
 * @param p the point that have to be added to the list
 */
void add_at_the_end(point_list *l, point p);

/**
 * it finds all the possible pawns the player may move.
 *
 * @param dama laska board
 * @param cols columns size
 * @param rows rows size
 * @return a pointer to the structure of the list of points
 */
point_list * avaiable_choices(tgame *dama, int rows, int cols, int turn);

/**
 * it finds all the possible pawns the player may move.
 *
 * @param dama laska board
 * @param cols columns size
 * @param rows rows size
 * @param turn white(0) or black(1)
 */
void computer_moves(tgame *dama, int rows, int cols, int turn);

/**
 * Prints the type of error or a suggestion.
 *
 * @param dama Laska board
 * @param rows rows size
 * @param cols columns size
 * @param turn 0 white or 1 black
 * @param code_error the type of error
 */
void error(tgame *dama, int rows, int cols,int turn, int code_error);

/**
 * Contains the main function for user interaction from standard input.
 *
 * @param dama Laska board
 * @param rows rows size
 * @param cols columns size
 * @param play_mode 2 if 2 players, 3 if player vs pc, 4 if pc vs pc
 * @return 0 if white won, 1 if black won
 */
int game(tgame *dama, int rows, int cols, int play_mode);

/**
 *
 * @return
 */
int coin_toss();

/**
 *
 * @return
 */
int check_answer();

/**
 *
 */
void choose_menu();

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
 *
 */
void result_menu(int winner);




/**
 * Greetings menu for player. It is used to show some basic rules to the player if they want to.
 */
void hello();

/**
 *  Funny goodbye menu with easter eggs from the infamous game: Cyberpunk 2077.
 */
void goodbye();

/**
 *  Credits for creation of this game.
 */
void credits();


#endif //LASKA_LASKA_H
