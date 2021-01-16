#include <stdio.h>
#include "laska.h"

int main() {
    int winner, sup;
    tgame *dama;
    srand(time(NULL));

    dama = create(7,7);
    initialize(dama,dama->cols,dama->rows);
    hello();

    if(decision_menu()){
        switch (main_menu()) {
            case 0:
                // player solo
                printf("\n");
                printf("You're playing solo. Since life's been hard for you, you can play both an decide who wins.\n");
                printf("\n");
                winner = game(dama, dama->rows, dama->cols,2);
                result_menu(winner);
                goodbye();
            case 1:
                // player vs player
                printf("\n");
                printf("Hey you guys, let's decide your colors first!\n");
                printf("\n");
                choose_menu();
                printf("\n");
                winner = game(dama, dama->rows, dama->cols,2);
                result_menu(winner);
                goodbye();
            case 2:
                // pc vs player
                printf("\n");
                printf("This pc is too arrogant to start first, you'll use the white pawns\n");
                printf("\n");
                winner = game(dama, dama->rows, dama->cols,3);
                result_menu(winner);
                goodbye();
            case 3:
                // pc vs pc
                printf("\n");
                printf("Keep the eyes on the ball, or at least try to!\n");
                printf("Shall they start?(yes/no)\n");
                sup = check_answer();
                if(sup){
                    winner = game(dama, dama->rows, dama->cols,4);
                    result_menu(winner);
                }

        }
    }
    freegame(dama,dama->rows,dama->cols);
    credits();



    return 0;
}



/*  What is left to implement ?
 *
 *  - Funzionalita' di Quit in qualsiasi momento
 *  - Funzionalita' di Give Up in qualsiasi momento
 *  - Reset Game ()
 *  - Passa il turno
 *  - Undo Move
 *  -
 *
 *  REFACTOR CODICE
 */
