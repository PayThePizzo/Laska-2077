#include <stdio.h>
#include "laska.h"

int main() {
    int winner;

    tgame *dama = create(7,7);
    initialize(dama,dama->cols,dama->rows);
    winner = game (dama, dama->rows, dama->cols);

    if(winner==0){
        printf("White gamer is the winner!!!");
    }else {
        printf("Black player is the winner!!!");
    }
    printf("\n");
    freegame(dama,dama->rows,dama->cols);

    return 0;
}

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
 *
 * Features
 * - Give Up
 * - Quit
 * - Reset the game
 * - Undo move
 * - Pass turn
 *
 */


/*  Menu
 *  - Scelta modalita' player singolo
 *  - Scelta modalita' player vs player
 *  - Scelta modalita' player vs pc (commenti del pc)
 *  - Scelta modalita' pc vs pc (commenti di entrambi i pc)
 *
 *  - Scelta colore casuale con una moneta
 *  - Scelta personaggio tradizionale
 *
 *  - Funzionalita' di Quit in qualsiasi momento
 *  - Funzionalita' di Give Up in qualsiasi momento
 *
 *  - Suggerimenti del computer.
 *  -
 *
 */
