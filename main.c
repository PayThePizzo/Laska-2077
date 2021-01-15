#include <stdio.h>
#include "laska.h"

int main() {
    int winner = -99;
    tgame *dama;

    dama = create(7,7);
    initialize(dama,dama->cols,dama->rows);
    hello();

    if(decision_menu()){
        switch (main_menu()) {
            case 0:
                // player solo
                winner = game(dama, dama->rows, dama->cols,2);
                result_menu(winner);
                goodbye();
            case 1:
                // player vs player
                winner = game(dama, dama->rows, dama->cols,2);
                result_menu(winner);
                goodbye();
            case 2:
                // pc vs player
                winner = game(dama, dama->rows, dama->cols,3);
                result_menu(winner);
                goodbye();
            case 3:
                // pc vs pc
                winner = game(dama, dama->rows, dama->cols,4);
        }
    }
    freegame(dama,dama->rows,dama->cols);
    credits();

    return 0;
}



/*  What is left to implement ?
 *
 *  - Scelta colore casuale con una moneta
 *  - Scelta personaggio tradizionale
 *  - Funzionalita' di Quit in qualsiasi momento
 *  - Funzionalita' di Give Up in qualsiasi momento
 *  - Reset Game ()
 *  - Passa il turno
 *  - Undo Move
 */
