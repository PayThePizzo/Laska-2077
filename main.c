#include <stdio.h>
#include "laska.h"

int main() {
    int winner = -99 , sup = -99;

    tgame *dama = create(7,7);
    initialize(dama,dama->cols,dama->rows);
    hello();
    sup = decision_menu();

    if(sup){
        switch (main_menu()) {
            case 0:
                // player solo
                winner = game(dama, dama->rows, dama->cols,2);
            case 1:
                // player vs player
                winner = game(dama, dama->rows, dama->cols,2);
            case 2:
                // pc vs player
                winner = game(dama, dama->rows, dama->cols,3);
            case 3:
                // pc vs pc
                winner = game(dama, dama->rows, dama->cols,4);
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
 * 0) Coin Toss
 * 1) Scelta
 *      DISCLAIMER se si scrivono cose a caso
 *
 *
 */


/*  Games
 * 1) Single Player     - Game
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
 *
 *
 *  STRINGA SCELTA yes no
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
 *  warning C4715: 'illegal_move': not all control paths return a value
    warning C4715: 'main_menu': not all control paths return a value
    warning C4715: 'decision_menu': not all control paths return a value
 */
