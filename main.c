#include <stdio.h>
#include "laska.h"

int main() {
    int winner, sup, cond = 1, answer, aux;
    tgame *dama;
    srand(time(NULL));

    do {
        dama = create(7, 7);
        initialize(dama, dama->cols, dama->rows);
        hello();

        if (decision_menu()) {
            aux = main_menu();

            if(aux == 0) {
                /*player solo*/
                printf("\n");
                printf("You're playing solo. Since life's been hard for you, you can play both players and decide who wins.\n");
                printf("\n");
                winner = game(dama, dama->rows, dama->cols, 2);
                result_menu(winner);
            }
            else if(aux == 1) {
                /*player vs player*/
                printf("\n");
                printf("Hey you guys, let's decide your colors first!\n");
                printf("\n");
                choose_menu();
                printf("\n");
                winner = game(dama, dama->rows, dama->cols, 2);
                result_menu(winner);
            }
            else if(aux == 2) {
                /*pc vs player*/
                printf("\n");
                printf("This pc is too arrogant to start first, you'll use the white pawns\n");
                printf("\n");
                winner = game(dama, dama->rows, dama->cols, 3);
                result_menu(winner);
            }
            else if(aux == 3) {
                /* pc vs pc */
                printf("\n");
                printf("Keep the eyes on the ball, or at least try to!\n");
                printf("Shall they start?(yes/no)\n");
                printf("\n");
                printf("\n");
                sup = check_answer();

                if (sup) {
                    winner = game(dama, dama->rows, dama->cols, 4);
                    result_menu(winner);
                }
            }
        }
        freegame(dama, dama->rows, dama->cols);

        printf("\n");
        printf("\n");
        printf("Would you like to play again? (yes/no)\n");
        printf("If you want to play again, you will go back to the welcome section!\n");
        printf("\n");
        printf("\n");
        answer = check_answer();

        if(answer != 1){
            cond = 0;
        }
    }while(cond);

    goodbye();
    credits();

    return 0;
}
