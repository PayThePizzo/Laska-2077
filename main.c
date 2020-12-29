#include "laska.h"
#include <stdio.h>

int main() {
    int winner = -1;
    debug_dama();
    /*
    hello();
    winner = decision_menu();
    result_menu(winner);
    goodbye();
     */
    credits();

    return 0;
}

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