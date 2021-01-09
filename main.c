#include <stdio.h>
#include "laska.h"

int main() {
    int winner = -99, sup = -99;
    tgame *dama = create(7,7);
    initialize(dama,dama->cols,dama->rows);

    hello();
    sup = decision_menu();

    if(sup){
        switch (main_menu()) {
            case 0:
                winner = game(dama, dama->rows, dama->cols,0);
            case 1:
                winner = game(dama, dama->rows, dama->cols,0);
            case 2:
                winner = 2;
            case 3:
                winner = 3;
            default:
                printf("Error in Play or Not section of Main");
                EXIT_FAILURE;
        }
    }
    result_menu(winner);

    freegame(dama,dama->rows,dama->cols);

    goodbye();
    credits();

    return 0;
}


/*Functions for the game
 * -2) Coin Toss
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


/*  Games
 * 1) Single Player    - Game
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
 *
 *  warning C4715: 'illegal_move': not all control paths return a value
    warning C4715: 'main_menu': not all control paths return a value
    warning C4715: 'decision_menu': not all control paths return a value
 */
