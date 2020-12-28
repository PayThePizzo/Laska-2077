#include "laska.h"

// Create, Free & Print - Dama



void official_print(tgame result, int rows , int cols){
    printf("%32s","LASKA GAME\n");
    printf(" ");
    int i , j;
    for (int i = 0; i < rows; ++i) {
        printf(" %c   ",65+i);
    }

    printf("\n");
    for (i = 0; i < rows; ++i) {
        printf("%d ",i+1);
        for (j = 0; j <cols; ++j) {
            if(result.mat[i][j]->id==0){
                printf("%c ",219);
            }else if(result.mat[i][j]->id==1){
                printf("%c ",' ');
            }else if(result.mat[i][j]->id==2){
                printf("%c ",'w');
            }else if(result.mat[i][j]->id==3){
                printf("%c ",'b');
            }else if(result.mat[i][j]->id==4){
                printf("%c ",'W');
            }else if(result.mat[i][j]->id==5){
                printf("%c ",'B');
            }
        }
        printf("\n");
    }
}

void private_print(tgame result, int rows , int cols){
    printf("%25s","LASKA GAME\n");
    printf(" ");
    int i , j;
    for (int i = 0; i < rows; ++i) {
        printf(" %c    ",65+i);
    }

    printf("\n");
    for (i = 0; i < rows; ++i) {
        printf("%d ",i+1);
        for (j = 0; j <cols; ++j) {
            if(result.mat[i][j]->id==0){
                printf("%c ",219);
            }else if(result.mat[i][j]->id==1){
                printf("%c ",' ');
            }else if(result.mat[i][j]->id==2){
                printf("%c ",'W');
            }else if(result.mat[i][j]->id==3){
                printf("%c ",'B');
            }
            if(result.mat[i][j]->next!=NULL){ /*torre di 2 elementi*/
                if(result.mat[i][j]->next->id==0){
                    printf("%c ",219);
                }else if(result.mat[i][j]->next->id==1){
                    printf("%c ",' ');
                }else if(result.mat[i][j]->next->id==2){
                    printf("%c ",'W');
                }else if(result.mat[i][j]->next->id==3){
                printf("%c ",'B');
                }
                if(result.mat[i][j]->next->next!=NULL){ /* torre di 3 elementi */
                    if(result.mat[i][j]->next->next->id==0){
                        printf("%c ",219);
                    }else if(result.mat[i][j]->next->next->id==1){
                        printf("%c ",' ');
                    }else if(result.mat[i][j]->next->next->id==2){
                        printf("%c ",'W');
                    }else if(result.mat[i][j]->next->next->id==3){
                        printf("%c ",'B');
                    }
                }
                else{
                    printf(" ");
                }

            }
            else{
                printf("   ");
            }
            printf("|");
        }
        printf("\n  __________________________________________");
        printf("\n");

    }
}



//Vectors for Pawns
/* 1) Crea Vettore generico
 * 2) Libera Vettore
 * 3) Printa Vettore
 */




//Auxiliary Generic Functions

int coin_toss(){
    double flip = (double)rand()/(double)RAND_MAX;
    if(flip >= 0.5){
        return 1;
    }else{
        return 0;
    }
}

int convert(){
    char a;
    int i = 0;
    scanf("%c",&a);
    if(a>='A' && a<='G')
        return i=a-65;
    else if(a>='a' && a<='g')
        return i=a-97;
    else if (a=='x'||a=='X')
        return -1;
    else{
        convert();
    }
}

point findmiddle(point a, point b){
    point middle;
    if(a.y>b.y){
        if(a.x>b.x){   /*alto a sinistra*/
            middle.x = a.x-1;
            middle.y = a.y-1;
        }
        else{           /*alto a destra*/
            middle.x = a.x+1;
            middle.y = a.y-1;
        }
    }
    else{
        if(a.x>b.x){        /*basso a sinistra*/
            middle.x = a.x-1;
            middle.y = a.y+1;
        }
        else{
            middle.x = a.x+1;   /*basso a destra*/
            middle.y = a.y+1;
        }
    }

    return middle;

}



// Menu & Auxiliary Game Functions
int main_menu(){
    int input = -1;
    int cond= 1;
    printf("\n");
    printf("Now, let's choose what game we shall play. Type the right code here:");
    printf("\n");

    do{
        scanf("%d", &input);
        if(input >= 0 && input <= 3){
            cond = 0;
        } else{
            printf("Yoda says: Bugs here, you won't find");
        }
    }while(cond);

    switch (input) {
        case 0:
            printf("You chose: Single Player");
            printf("\n");
            printf("Man, if I were you, I'd make some new friends...");
            printf("\n");
            return input;
        case 1:
            printf("You chose: Player vs Player");
            printf("\n");
            printf("Finally, you got some friends to play with!");
            printf("\n");
            return input;
        case 2:
            printf("You chose: Player vs Pc");
            printf("\n");
            printf("I'm impressed you managed to lose your friends that fast, you really are a disaster at social life");
            printf("\n");
            return input;
        case 3:
            printf("You chose: Pc vs Pc");
            printf("\n");
            printf("I know you might not care, but watching two computers play against each other... is pretty lame");
            printf("\n");
            return input;
        default:
            printf("Error in main_menu");
            EXIT_FAILURE;
    }
}

//Data la pedina, la scacchiera, fai una mossa legale random


/*  Flow of the Game
 *  1) Choose Players
 *      - Coin Toss
 *      - Choice
 *
 *  2) Let White play first
 *      - Choose Pawn   -> legal_choice -> Yes  -> Choose Move
 *                                      -> No   -> Error + Ask Again
 *
 *      - Choose Move   -> legal_move   -> Yes  -> check_win -> No  ->  check_grow -> Yes -> check_limit -> 3<=  -> Keep Playing + Change Player
 *                                                                                                       -> >3   -> Remove First Pawn + Change Player
 *                                                                                 -> No  -> Change Player
 *                                                           -> Yes  ->  Stop the Game
 *                                      -> No   -> Error + Ask Again
 *
*/


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
 */
