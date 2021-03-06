#ifndef LASKA_LASKA_H
#define LASKA_LASKA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <math.h>


/** @mainpage Laska
 *
 *  @file laska.h
 *  @authors Gianmaria Pizzo & Aleksandra Gjorgievska
 *  @brief This library implements the Mini-Laska Project called "Laska-2077"
 *  @date 17/01/2020
 */

/**
 * @brief Laska board coordinates.
 * @struct
 */
struct point{
    int j; /**< the j coordinate */
    int i; /**< the i coordinate */
};

/**
* @brief type point.
* @typedef 
*/
typedef struct point point_t;

/**
 * @brief element of a point list.
 * @struct 
 */
struct point_cell{
    point_t p;    /**< the coordinates of the cell*/
    struct point_cell * next;   /**< pointer to the very next cell*/
};

/**
* @brief type point cell.
* @typedef
*/
typedef struct point_cell point_cell_t;

/**
 * @brief list of point cells.
 * @struct 
 */
struct point_list{
    int dim;    /**< the dimension*/
    point_cell_t * list; /**< a list of cells*/
};

/**
* @brief  type list of point cells.
* @typedef 
*/
typedef struct point_list point_list_t;

/**
 * @brief Box of Laska board, if the cell is empty it represents the color, otherwise it represents the pawn (obviously the cell is white).
 * @struct
 */
struct boxpawn {
    int id;     /**< the color*/
    struct boxpawn *next;   /**< pointer to the next boxpawn*/
};

/**
* @brief type box or pawn.
* @typedef
*/
typedef struct boxpawn boxpawn_t;

/**
 * @brief Laska-board.
 * @struct
 */
struct dama{
    int cols;   /**< the columns*/
    int rows;   /**< the rows*/
    boxpawn_t ***mat;     /**< the main structure*/
};

/**
 * @brief type game.
 * @typedef
 */
typedef struct dama game_t;


/* ----------------------------------------------------- Part 1 ----------------------------------------------------- */

/**
 * Creates a new Laska Board.
 *
 * @param cols columns size
 * @param rows rows size
 * @return a pointer to the new structure.
 */
game_t* create(int cols,int rows);

/**
 * Initializes the colors of the boxes and places the pawns.
 *
 * @param dama laska board
 * @param cols columns size
 * @param rows rows size
 */
void initialize(game_t * dama, int cols, int rows);

/**
 * Frees the whole Laska board structure.
 *
 * @param result laska board
 * @param rows rows size
 * @param cols columns size
 */
void freegame(game_t *result, int rows, int cols);

/**
 * Creates a list of the possible pawn you can choose to move.
 *
 * @return the list and the size of the new points list
 */
point_list_t * create_choices_list();

/**
 * Frees the list of points.
 * 
 * @param pointer to the head of the list to free
 */
void free_choices_list(point_list_t * l);


/* ----------------------------------------------------- Part 2 ----------------------------------------------------- */

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
void print(game_t dama, int rows , int cols);

/**
 * Contains the main function for user interaction from standard input.
 *
 * @param dama Laska board
 * @param rows rows size
 * @param cols columns size
 * @param play_mode 2 if player vs player, 3 if player vs pc, 4 if pc vs pc
 *
 * @return 0 if white won, 1 if black won, 10 if someone left hte game
 */
int game(game_t *dama, int rows, int cols, int play_mode);

/* ----------------------------------------------------- Part 3 ----------------------------------------------------- */

/**
 * Puts the pawn given in input at the end of the list of pieces of the position given in input.
 *
 * @param dama Laska board
 * @param pawn the captured pawn that ca be placed on the bottom of the pawn stack
 * @param r the row number of the box in which to place the pawn on bottom of the stack
 * @param c the column number of the box in which to place the pawn on bottom of the stack
 */
void add(game_t *dama, int pawn, int r, int c);

/**
 * Removes the top piece of the tower in the given position and returns it in output.
 *
 * @param dama Laska board
 * @param r the row number of the box in which to place the pawn on top of the stack
 * @param c the column number of the box in which to place the pawn on top of the stack
 *
 * @returns the top pawn in position [r][c]
 */
int remove_pawn(game_t *dama, int r, int c);

/**
 * Takes 2 points and returns the point in between.
 *
 * @param a the row and column coordinates of the origin box
 * @param b the row and column coordinates of the destination box
 *
 * @return the row and column coordinates of the middle box
 */
point_t findmiddle(point_t a, point_t b);

/**
 * Moves the pawn from point a to point b.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the origin box
 * @param b the row and column coordinates of the destination box
 */
void move (game_t *dama, point_t a, point_t b);

/**
 * Promotes the pawn if it reaches the other side of the board.
 *
 * @param dama Laska board
 * @param turn current game turn
 */
void promotion(game_t *dama, int turn);


/* ----------------------------------------------------- Part 4 ----------------------------------------------------- */

/**
 * Checks if a non-promoted white pawn has the possibility to move, it means that at least one between the 2 diagonals forward is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 *
 * @returns returns 1 if it has the possibility to move, 0 otherwise
 */
int white_move_check(game_t *dama, point_t a);

/**
 * Checks if a non-promoted black pawn has the possibility to move, it means that at least one between the 2 diagonals forward is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 *
 * @return returns 1 if it has the possibility to move, 0 otherwise
 */
int black_move_check(game_t *dama, point_t a);

/**
 * Checks if promoted dama pawn has the possibility to move, it means that at least one between the 4 diagonals is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 *
 * @return returns 1 if it has the possibility to move, 0 otherwise
 */
int dama_move_check(game_t *dama, point_t a);

/**
 * Checks if a non-promoted white pawn has the possibility to capture,
 * if that box has on the diagonal ahead an enemy pawn and the next one on the diagonal is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @param turn current game turn
 *
 * @return returns 1 if it has the possibility to capture a foe, 0 otherwise
 */
int white_capture_check(game_t *dama, point_t a, int turn);

/**
 * Checks if a non-promoted black pawn has the possibility to capture,
 * if that box has on the diagonal ahead an enemy pawn and the next one on the diagonal is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @param turn current game turn
 *
 * @return returns 1 if it has the possibility to capture a foe, 0 otherwise
 */
int black_capture_check(game_t *dama, point_t a, int turn);

/**
 * Checks if a promoted dama pawn has the possibility to capture,
 * if that box has on one of the 4 diagonal an enemy pawn and the next one on the diagonal is free.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @param turn current game turn
 *
 * @return returns 1 if it has the possibility to capture a foe, 0 otherwise
 */
int dama_capture_check(game_t *dama, point_t a, int turn);

/**
 * Checks all the pawns on the board and checks if at least one of your pieces has a chance to capture the opponent's one.
 *
 * @param dama Laska board
 * @param turn current game turn
 *
 * @return returns 1 if the player can capture in the current turn, 0 otherwise
 */
int player_can_capture(game_t *dama,int turn);

/**
 * Checks all the pawns on the board and checks if at least one of your pieces has a chance to move to an other box.
 *
 * @param dama Laska board
 * @param turn current game turn
 *
 * @return returns 1 if the player can move at least 1 pawn, 0 otherwise
 */
int player_can_move(game_t *dama, int turn);

/**
 * Checks that the pawn contained in the selected box is the pawn of the player whose turn it is,
 * also checks if the pawn can be moved and if there is the possibility of conquering, the player select that pawn.
 *
 * @param dama Laska board
 * @param turn current game turn
 * @param a the row and column coordinates of the selected box
 *
 * @return  7 if you can't select that box because i's not your pawn, 8 if the player can choose that box but now you
 * must capture foe's pawn, 9 if you can move, 10 if the selected pawn is not free to move, 11 if you are forced to
 * capture so you have to choose an other pawn
 */
int legal_choice(game_t *dama, int turn, point_t a);

/**
 * Controls the player can move from pawn a to b following the Mini-Laska-rules.
 *
 * @param dama Laska board
 * @param turn current game turn
 * @param a the row and column coordinates of the origin box
 * @param b the row and column coordinates of the destination box
 * @param have_to_capture the parameter returned by legal_chice, if the value is 8, it means that the choosed pawn
 * is correct but now the player is forced to capture
 *
 * @return
 * @code
 *         0 if it doesn't violate the rules.
 *         code_error(1) if you are forced to capture foe's pawn but you are moving somewhere else.
 *         code_error(2) if dama is trying to capture in a wrong way.
 *         code_error(3) if a pawn is trying to capture in a wrong way.
 *         code_error(4) if dama is not moving on one of the 4 free nearby diagonals.
 *         code_error(5) id a pawn is not moving on one of the 2 forward diagonals.
 *         code_error(6) it's not possible to move in boxes that aren't white and empty.
 * @endcode
 */
int illegal_move (game_t *dama, int turn, point_t a, point_t b, int have_to_capture);

/**
 * Returns the opponent's id code, it is used to change turns or to find opponent's pieces.
 *
 * @param turn current game turn
 *
 * @return if it takes white as input it returns black, if it takes black input it returns white
 */
int enemy(int turn);

/**
 * Checks if the pawn is a dama.
 *
 * @param dama Laska board
 * @param a the row and column coordinates of the selected box
 * @param turn current game turn
 *
 * @return returns 1 if the selected box contains a promoted pawn, 0 otherwise.
 */
int is_promoted (game_t *dama, point_t a, int turn);

/**
 * Checks if there has been a victory.
 *
 * @param dama Laska board
 * @param rows rows size
 * @param cols columns size
 * @param turn current game turn
 * @param moves current moves to print
 *
 * @return 0 if no one has won yet, 1 if white has won, 2 if black has won
 */
int victory(game_t *dama, int rows, int cols, int turn, int moves);

/* ----------------------------------------------------- Part 5 ----------------------------------------------------- */

/**
 * It adds at the end of a list the coordinates of a pawn.
 *
 * @param l the list to modify
 * @param p the point that have to be added to the list
 */
void add_at_the_end(point_list_t *l, point_t p);

/**
 * it finds all the possible pawns the player may move.
 *
 * @param dama laska board
 * @param cols columns size
 * @param rows rows size
 *
 * @return a pointer to the structure of the list of points
 */
point_list_t * avaiable_choices(game_t *dama, int rows, int cols, int turn);

/**
 * it finds all the possible pawns the player may move.
 *
 * @param dama laska board
 * @param cols columns size
 * @param rows rows size
 * @param turn white(0) or black(1)
 */
void computer_moves(game_t *dama, int rows, int cols, int turn);


/* ----------------------------------------------------- Part 6 ----------------------------------------------------- */

/**
 * Prints the type of error or a suggestion.
 *
 * @param dama Laska board
 * @param rows rows size
 * @param cols columns size
 * @param turn 0 white or 1 black
 * @param code_error the type of error
 */
void error(game_t *dama, int rows, int cols,int turn, int code_error);

/**
 * Function which returns a random toin coss
 *
 * @returns 1 or 0 randomly
 */
int coin_toss();

/**
 * Function that checks the input and returns an integer
 *
 * @return 1 if the input is "yes", and 0 if the input is "no"
 */
int check_answer();

/**
 * Intermediate menu that helps deciding which player starts first
 */
void choose_menu();

/**
 * The main menu, which introduces all the modalities our guest(s) can choose from
 *
 * @return
 */
int main_menu();

/**
 * Intermediate menu that confirms the willingness to play/leave the game
 *
 * @return
 */
int decision_menu();

/**
 * Menu that displays the winner of the game or the message "thanks for trying"
 *
 * @param winner
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


#endif /* LASKA_LASKA_H */