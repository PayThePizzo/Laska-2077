#include "laska.h"

// Create and Free

tgame* create(int cols,int rows){
    tgame *dama;
    int i, j;

    dama=(tgame*)malloc(sizeof(tgame));                       /*alloca lo spazio alla struct*/
    assert(dama!=NULL);

    dama->rows=rows;                                          /*salva le dimensioni*/
    dama->cols=cols;

    dama->mat=(boxpawn***)malloc(sizeof(boxpawn**)*rows);     /*alloca vettore righe*/
    assert(dama->mat!=NULL);

    for(i=0;i<rows;i++){
        dama->mat[i]=(boxpawn**)malloc(sizeof(boxpawn*)*cols);/*alloca le varie righe*/
        assert(dama->mat[i]!=NULL);
        for(j=0;j<cols;j++){
            dama->mat[i][j]=(boxpawn*)malloc(sizeof(boxpawn));/*alloca 1 casella contenente colore o pedina per ciascun punto della schacchiera*/
            assert(dama->mat[i][j]!=NULL);
            dama->mat[i][j]->next=NULL;
        }
    }
    /*creazione scacchiera*/
    for(i = 0;i<rows;i++){
        for(j=0;j<cols;j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                dama->mat[i][j]->id = 0;
            } else if (i % 2 != 0 && j % 2 != 0) {
                dama->mat[i][j]->id = 0;
            } else {
                dama->mat[i][j]->id = 1;
            }
        }
    }
    /*posizionamento pedine*/
    for (i = 0; i <rows ; i++) {
        for (j = 0; j < cols; j++) {
            if (dama->mat[i][j]->id == 0) {
                if (i > rows / 2 && i <= rows) {
                    dama->mat[i][j]->id = 2;
                } else if (i >= 0 && i < rows / 2) {
                    dama->mat[i][j]->id = 3;
                }
            }

        }
    }
    return dama;
}

black_vet_create(tgame *dama, int rows, int cols){

}

void black_vet_free(){

}

white_vet_create(tgame *dama, int rows, int cols){

}

void white_vet_free(){

}



void freegame(tgame *dama, int rows, int cols) {
    int i , j;

    for(i = 0; i<rows; i++){
        for (j=0; j<cols; j++){
            if(dama->mat[i][j]->next==NULL)
                free(dama->mat[i][j]);                      /*caso con 1 sola bowpawn*/
            else if(dama->mat[i][j]->next->next==NULL){ 
                free(dama->mat[i][j]->next);                /*caso con 2 boxpawn*/
                free(dama->mat[i][j]);
            }
            else{
                free(dama->mat[i][j]->next->next);          /*caso con 3 boxpawn*/
                free(dama->mat[i][j]->next);
                free(dama->mat[i][j]); 
            }
        }
        free(dama->mat[i]);
    }
    free(dama->mat);
    free(dama);
}


// Legal Side

int legal_move (tgame *dama, int turn, point a, point b, int have_to_capture){

    /*
        return 1;
    */
    if (turn ==0){                              /*bianchi*/
        if(dama->mat[a.y][a.x]->id == 2){            /*soldato semplice*/
            if (have_to_capture==1){             /*deve conquistare affinchè la mossa sia valida */
                if (dama->mat[b.y][b.x]->id== 0 && b.y==a.y-2 && (b.x==a.x+2||b.x==a.x-2) && (dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id==3 ||dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==5 ))
                    return 1;
                else{
                    printf("Mossa non valida\n");
                    return 0;
                }
            }
            else {                              /* muovi soltanto senza conquistare */
                if (dama->mat[b.y][b.x]->id== 0 && b.y==a.y-2 && (b.x==a.x+2||b.x==a.x-2) && (dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id==3 ||dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==5 ))
                    return 1;
                if(dama->mat[b.y][b.x]->id == 0 && b.y==a.y-1 && (b.x==a.x+1||b.x==a.x-1))
                    return 1;
                else{
                    printf("Mossa non valida\n");
                    return 0;
                }
            }
        }
        else {                                  /* se sto muovendo una dama */
            if (have_to_capture==1){             /*deve conquistare affinchè la mossa sia valida */
                if (dama->mat[b.y][b.x]->id == 0 && abs(b.y - a.y)==2 && abs(b.x - a.x)==2 && (dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==3 ||dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==5 ))
                    return 1;
                else{
                    printf("Mossa non valida\n");
                    return 0;
                }
            }
            else {                              /* muovi soltanto senza conquistare */
                if (dama->mat[b.y][b.x]->id == 0 && abs(b.y - a.y)==2 && abs(b.x - a.x)==2 && (dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==3 ||dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==5 ))
                    return 1;
                if(dama->mat[b.y][b.x]->id == 0 && abs(b.x - a.x)==1 && abs(b.y - a.y)==1)
                    return 1;
                else{
                    printf("Mossa non valida\n");
                    return 0;
                }
            }
        }
    }
    else {                                         /* turno neri*/
        if(dama->mat[a.y][a.x]->id == 3){            /*soldato semplice*/
            if (have_to_capture==1){             /*deve conquistare affinchè la mossa sia valida */
                if (dama->mat[b.y][b.x]->id == 0 && b.y==a.y+2 && (b.x==a.x+2||b.x==a.x-2) && (dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==2 ||dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==4 ))
                    return 1;
                else{
                    printf("Mossa non valida\n");
                    return 0;
                }
            }
            else {
                if (dama->mat[b.y][b.x]->id == 0 && b.y==a.y+2 && (b.x==a.x+2||b.x==a.x-2) && (dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==2 ||dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==4 ))
                    return 1;                          /* muovi soltanto senza conquistare */
                if(dama->mat[b.y][b.x]->id == 0 && b.y==a.y+1 && (b.x==a.x+1||b.x==a.x-1))
                    return 1;
                else{
                    printf("Mossa non valida\n");
                    return 0;
                }
            }
        }
        else {                                  /* se sto muovendo una dama */
            if (have_to_capture==1){             /*deve conquistare affinchè la mossa sia valida */
                if (dama->mat[b.y][b.x]->id == 0 && abs(b.y - a.y)==2 && abs(b.x - a.x)==2 && (dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==2 ||dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==4 ))
                    return 1;
                else{
                    printf("Mossa non valida\n");
                    return 0;
                }
            }
            else {
                if (dama->mat[b.y][b.x]->id == 0 && abs(b.y - a.y)==2 && abs(b.x - a.x)==2 && (dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==2 ||dama->mat[findmiddle( a, b).y][findmiddle( a, b).x]->id ==4 ))
                    return 1;                         /* muovi soltanto senza conquistare */
                if(dama->mat[b.y][b.x]->id == 0 && abs(b.x - a.x)==1 && abs(b.y - a.y)==1)
                    return 1;
                else{
                    printf("Mossa non valida\n");
                    return 0;
                }
            }
        }
    }
}


//Posso scegliere solo le mie pedine
//Controllo se la pedina scelta e' nello stesso indirizzo di quelle che ho dentro il mio vettore
//
int legal_choice(tgame *dama, point a, point b){\

}

int check_number(int dim){
    int i;
    while (1){
        scanf("%d",&i);
        if(i>=1 && i<=dim)
            return i;
        else {
            printf("The selected box doesn't exist. Please select a number from %d to %d\n", 1, dim);
        }
    }
}

// Print

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


// Conversion

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


// Pawn Grow Function
void add(tgame *dama, t_ide pawn, int r, int c){
    /*
    if (dama->arr[r][c]->id==1){
    printf("mistake! pawn in black box");
    exit(1);
    }
    */
    if (dama->mat[r][c]->id==0){
    dama->mat[r][c]->id = pawn;
    }
    else{
    boxpawn *n= (boxpawn *) malloc(sizeof(boxpawn));
    n->next = NULL;
    n->id = pawn;
    if (dama->mat[r][c]->next==NULL){
        dama->mat[r][c]->next=n;
    }
    else if(dama->mat[r][c]->next==NULL){
        dama->mat[r][c]->next->next=n;
    }
    else{
            free(dama->mat[r][c]->next->next);
            dama->mat[r][c]->next->next = n;
        }
    }
}


// Remove Pawn
int remove_pawn(tgame *dama, int r, int c){
    int estract;
    /*
    if (dama->arr[r][c]->id==1){
    printf("mistake! pawn in black box");
    exit(1);
    }
    
    if (dama->arr[r][c]->id==0){
    printf("box already empty");
    exit(1);
    }
    */
   if(dama->mat[r][c]->next==NULL){
       estract = dama->mat[r][c]->id;
       dama->mat[r][c]->id= 0;
       return estract;
   }
   else{
       boxpawn *element = dama->mat[r][c];
       estract = dama->mat[r][c]->id;
       dama->mat[r][c] = dama->mat[r][c]->next;
       free(element);
       return estract;
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

void promotion(tgame *dama, int turn){
    int i,j;
    turn == 0? i=0 : (i=((dama->rows)-1));

    for (j=0; j<dama->cols; j++){
        if (dama->mat[i][j]->id == turn+2)
            dama->mat[i][j]->id +=2;
    }
}


void move (tgame *dama, point a, point b){
    if (abs(b.x - a.x)==1 && dama->mat[b.y][b.x]->id == 0){
        boxpawn * temporary = dama->mat[b.y][b.x];                    /*swap spostamento cella vuola*/
        dama->mat[b.y][b.x]= dama->mat[a.y][a.x];
        dama->mat[a.y][a.x]= temporary;
    }
    else if(abs(b.y - a.y)==2 && dama->mat[b.y][b.x]->id == 0){ /*spostamento con conquista*/
        int conquered;
        boxpawn * temporary = dama->mat[b.y][b.x];  
        point middle = findmiddle( a, b);

        conquered = remove_pawn(dama, middle.y, middle.x);
        add(dama, conquered, a.y, a.x);
        dama->mat[b.y][b.x] = dama->mat[a.y][a.x];
        dama->mat[a.y][a.x]= temporary;
    }
    else {
        printf("Error move function");
    }

}

//Auxiliary

int coin_toss(){
    double flip = (double)rand()/(double)RAND_MAX;
    if(flip >= 0.5){
        return 1;
    }else{
        return 0;
    }
}


// Main Menu
/*  1) Scegli Modalita' 
 *  2) Scegli Colore oppure Toss a Coin
 *
 */
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

//mossa del pc
void random_move(){
}

// Game

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
 * */

int game(tgame *dama, int rows, int cols){
    point a,b;
    int turn = 0;
    int endgame = 0;

    while(!endgame) {
        private_print(*dama, rows, cols);
        printf("\n");
        printf("\n");
        printf("Write the start coordinate or type 'Quit'/'Give Up' to leave the game\n");
        if (turn == 0)
            printf("It's white turn\n");
        else
            printf("It's black turn\n");
        printf("Letter:");

        a.x = convert();
        if (a.x == -1)
            return (turn == 0 ? 1 : 0);
        else {
            printf("Number:");
            scanf("%d", &a.y);
            --(a.y);
            /* è una mia pedina?*/
            if (dama->mat[a.y][a.x]->id == turn + 2 || dama->mat[a.y][a.x]->id == turn + 4) {
                do {
                    printf("Write the destination coordinate\n");
                    printf("Letter:");
                    b.x = convert();
                    printf("Number:");
                    scanf("%d", &b.y);
                    --(b.y);
                } while (!legal_move(dama, a, b));

                move(dama, a, b);
                /*private_print (*dama,dama->rows,dama->cols);  magari solo all'ultima mossa */
                /* if vittoria (...) return 0/1 */

                if (turn == 0)
                    turn = 1;
                else
                    turn = 0;;
            } else {
                printf("Please select your pawn\n");
            }
        }
    }
}

/*

int game_p(tgame *dama, int rows, int cols){
    point a,b;
    int turn = 0;
    int endgame = 0;

    while(!endgame){
        private_print (*dama, rows, cols);
        printf("Write the start coordinate or Press x to give up\n");
        if(turn ==0)
            printf("It's white turn\n");
        else
            printf("It's black turn\n");
        printf("Letter:");
        a.x=convert(dama->cols);
        if(a.x == -1)
            return (turn == 0 ? 1 : 0);
        else{
            printf("Number:");
            a.y = check_number(dama->cols);
            (a.y) --;
            if(legal_selection(dama, turn, a)){
                if(dama->mat[a.y][a.x]->id== turn+2 || dama->mat[a.y][a.x]->id== turn+4){
                    do
                    {
                        printf("Write the destination coordinate\n");
                        printf("Letter:");
                        b.x=convert(dama->cols);
                        printf("Number:");
                        b.y = check_number(dama->cols);
                        (b.y) --;
                    } while (!legal_move (dama, turn, a, b, 2));
                    move(dama, a, b);
                    promotion(dama, turn);

                    if(turn == 0)
                        turn = 1;
                    else
                        turn = 0;;
                }
                else {
                    printf("Please select your pawn\n");
                }
            }

            else{
                printf("the selected move is not valid beacause you have to capture enemy's pawn\n");
            }
        }
    }
}
*/

//dato il puntatore alla pedina, mi dice se la pedina e' troppo alta
int check_limit(){

}

//dato il puntatore alla pedina e le coordinate in cui viene inserita, mi dice se la pedina cresce
int check_grow(){
}

//date le regole del gioco, la scacchiera e le pedine rimaste, mi dice se una mossa fa vincere la partita
// 1) Giocatore senza pedine
// 2) Giocatore non puo' piu conquistare o muovere (check mate)
// 3) Resa
int check_win(tgame *dama, int rows, int cols){
}


int game_flow(tgame *dama, int rows, int cols){

}