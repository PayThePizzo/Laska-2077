#include "laska.h"

/**
 *  @file laska.c
 *  @authors Gianmaria Pizzo & Aleksandra Gjorgievska
 *  @brief This is the source code file of the Mini-Laska Project called "Laska-2077"
 *  @date 18/01/2020
 */

/* ----------------------------------------------------- Part 1 ----------------------------------------------------- */

game_t * create(int cols,int rows){
    game_t *dama;
    int i, j;

/*allocates space to struct*/
    dama=(game_t*)malloc(sizeof(game_t));
    assert(dama!=NULL);

/*saves dimensions*/
    dama->rows=rows;
    dama->cols=cols;

/* allocates vector rows pointers */
    dama->mat=(boxpawn_t***)malloc(sizeof(boxpawn_t**)*rows);
    assert(dama->mat!=NULL);

/*allocates pawns pointers and boxes*/
    for(i=0;i<rows;i++){

        dama->mat[i]=(boxpawn_t**)malloc(sizeof(boxpawn_t*)*cols);
        assert(dama->mat[i]!=NULL);
        for(j=0;j<cols;j++){

            dama->mat[i][j]=(boxpawn_t*)malloc(sizeof(boxpawn_t));
            assert(dama->mat[i][j]!=NULL);
            dama->mat[i][j]->next=NULL;
        }
    }

    return dama;
}

void initialize(game_t * dama, int cols, int rows){
    int i = 0, j = 0;

    /*chessboard creation*/
    for(i = 0;i<rows;i++){
        for(j=0;j<cols;j++) {

            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0)) {
                dama->mat[i][j]->id = 0;
            } else {
                dama->mat[i][j]->id = 1;
            }
        }
    }
    /*pawn placement*/
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
}

void freegame(game_t *dama, int rows, int cols) {
    int i = 0 , j = 0;

    for(i = 0; i<rows; i++){
        for (j=0; j<cols; j++){

            if(dama->mat[i][j]->next==NULL) {
                free(dama->mat[i][j]);
            }
            else if(dama->mat[i][j]->next->next==NULL){
                free(dama->mat[i][j]->next);
                free(dama->mat[i][j]);
            }
            else{
                free(dama->mat[i][j]->next->next);
                free(dama->mat[i][j]->next);
                free(dama->mat[i][j]);
            }
        }

        free(dama->mat[i]);
    }

    free(dama->mat);
    free(dama);
}

point_list_t * create_choices_list(){
    point_list_t *l;

    l = (point_list_t *) malloc(sizeof(point_list_t));
    assert(l!=NULL);
    l->list = NULL;
    l->dim = 0;

    return l;
}

void free_choices_list(point_list_t * l){
    point_cell_t * temporary;

    if(l->list!=NULL){
        temporary = l->list;

        while(temporary->next!= NULL){
            temporary = temporary->next;
        }
        free (temporary);
    }
    free (l);
}

/* ----------------------------------------------------- Part 2 ----------------------------------------------------- */
int convert(int dim){
    char a;
    int cond = 1;

    while (cond){
        scanf(" %c",&a);

        if(a>='A' && a<=('A'+dim-1)) {
            a -= 65;
            cond = 0;
        }
        else if(a>='a' && a<=('a'+dim-1)) {
            a -= 97;
            cond = 0;
        }else if(a == 'x' || a == 'X'){
            printf("Quitting session.\n");
            a = 88;
            cond = 0;
        }else if(a == 'k' || a == 'K'){
            printf("Giving Up\n");
            a = 75;
            cond = 0;
        }
        else{
            printf("The selected box doesn't exist. Please select a letter from %c to %c\n", 65, 65+dim-1);
        }
    }

    return a;
}

int check_number(int dim){
    char i;
    int cond = 1;

    while (cond){
        scanf(" %c", &i);

        if(i>='1' && i<='1'+dim) {
            i = ((int) i - '0');
            cond = 0;
        }
        else {
            printf("The selected box doesn't exist. Please select a number from %d to %d\n", 1, dim);
        }
    }

    return i;
}

void print(game_t dama, int rows , int cols){
    int i = 0, j = 0, z = 0, empty = 0;
    boxpawn_t **t;

    printf("%43s","LASKA GAME\n");
    printf("\t");

    for(i = 0; i < rows; ++i) {
        printf(" %c\t",65+i);
    }

    printf("\n        _________________________________________________________\n");

    for (i = 0; i < rows; ++i) {
        t = &(dama.mat[i])[j];
        printf("      %d\t|",i+1);

        for (j = 0; j <cols; ++j) {
            t = &(dama.mat[i])[j];

            for(z=0; z<3 && !empty;z++){
                if((*t)->id==0){
                    printf("%c%c%c%c%c%c",219,219,219,219,219,219);
                }else if((*t)->id==2){
                    printf("%c ",'w');
                }else if((*t)->id==3){
                    printf("%c ",'b');
                }else if((*t)->id==4){
                    printf("%c ",'W');
                }else if((*t)->id==5){
                    printf("%c ",'B');
                }
                if(z==0 && (*t)->next!=NULL)
                    t = &(dama.mat[i][j]->next);
                else if(z==1 && (*t)->next!=NULL)
                    t = &(dama.mat[i][j]->next->next);
                else{
                    empty=1;
                }
            }
            empty = 0;
            printf("\t|");
        }
        printf("\n        _________________________________________________________");
        printf("\n");
    }        
}

int game(game_t *dama, int rows, int cols, int play_mode){
    point_t a,b;
    int turn = 0, moves = 0, code_error;
    char color [6];

    while(!victory(dama, rows, cols, turn, moves)){
        if(play_mode==2 || play_mode==3){

            do{
                print (*dama, rows, cols);
                if (turn==0) {
                    strcpy(color, "White");
                }else {
                    strcpy(color,"Black");
                }

                printf("\nIt's %s turn\n\n", color);
                printf("Write the start and the destination coordinate without spaces, for example a5b4\n");
                printf("\n");
                printf("\n");

                a.j = convert(dama->cols);

                /* quitting or giving up */
                if(a.j == 88){
                    return 10;
                }else if(a.j == 75){
                    return enemy(turn);
                }

                a.i = check_number(dama->cols);
                (a.i) --;

                code_error = legal_choice(dama, turn, a);

                b.j = convert(dama->rows);

                /* quitting or giving up*/
                if(a.j == 88){
                    return 10;
                } else if(b.j == 75){
                    return enemy(turn);
                }

                b.i = check_number(dama->rows);
                (b.i) --;

                if (code_error!=7&&code_error!=10&&code_error!=11) {
                    code_error = (illegal_move(dama, turn, a, b, legal_choice(dama, turn, a)));
                }
                if(code_error){
                    error(dama, dama->rows, dama->cols, turn, code_error);
                }
            } while (code_error);  

            move(dama, a, b);
            moves++;
            promotion(dama, turn);

            if(victory(dama, rows, cols, turn, moves)){
                return turn;
            }
        }
        if(play_mode==2){
            turn = enemy(turn);
        }
        else if(play_mode==3){
            print (*dama, rows, cols);
            computer_moves(dama,dama->rows,dama->cols,1);
            moves++;

            if(victory(dama, rows, cols, 1, moves)){                                        
                return 1;
            }
        }
        else if(play_mode==4){
            int winner=0;
            print (*dama, rows, cols);
            computer_moves(dama,dama->rows,dama->cols, turn);
            moves++;
            winner = victory(dama, rows, cols, turn, moves);
            if(winner!=0){                                    
                return --(winner);
            }
            else{
                turn = enemy(turn);
            }
            
        }
    }

    return 10;
}

/* ----------------------------------------------------- Part 3 ----------------------------------------------------- */

void add(game_t *dama, int pawn, int r, int c){

    if (dama->mat[r][c]->id==0){
        dama->mat[r][c]->id = pawn;
    }
    else{
        boxpawn_t *n = (boxpawn_t *) malloc(sizeof(boxpawn_t));
        n->next = NULL;
        n->id = pawn;

        if (dama->mat[r][c]->next==NULL){
            dama->mat[r][c]->next= n;
        }
        else if(dama->mat[r][c]->next==NULL){
            dama->mat[r][c]->next->next= n;
        }
        else {
            free(dama->mat[r][c]->next->next);
            dama->mat[r][c]->next->next = n;
        }
    }
}

int remove_pawn(game_t *dama, int r, int c){
    int estract;

    if(dama->mat[r][c]->next==NULL){
        estract = dama->mat[r][c]->id;
        dama->mat[r][c]->id= 0;
    }
    else{
        boxpawn_t *element = dama->mat[r][c];
        estract = dama->mat[r][c]->id;
        dama->mat[r][c] = dama->mat[r][c]->next;
        free(element);
    }

    return estract;
}

point_t findmiddle(point_t a, point_t b){
    point_t middle;

    middle.i = (a.i+b.i)/2;
    middle.j = (a.j+b.j)/2;

    return middle;
}

void move (game_t *dama, point_t a, point_t b){
    int conquered;
    boxpawn_t * temporary;
    point_t middle;


    if (abs(b.j - a.j)==1){
        temporary = dama->mat[b.i][b.j];
        dama->mat[b.i][b.j]= dama->mat[a.i][a.j];
        dama->mat[a.i][a.j]= temporary;
    }
    else if(abs(b.i - a.i)==2){

        temporary = dama->mat[b.i][b.j];
        middle = findmiddle( a, b);
        conquered = remove_pawn(dama, middle.i, middle.j);
        add(dama, conquered, a.i, a.j);
        dama->mat[b.i][b.j] = dama->mat[a.i][a.j];
        dama->mat[a.i][a.j]= temporary;
    }
    else {
        printf("Error move function\n");
    }
}

void promotion(game_t *dama, int turn){
    int i = 0, j = 0;

    turn == 0 ? i=0 : (i=((dama->rows)-1));

    for (j=0; j<dama->cols; j++){
        if (dama->mat[i][j]->id == turn+2) {
            dama->mat[i][j]->id += 2;
        }
    }
}

/* ----------------------------------------------------- Part 4 ----------------------------------------------------- */

int white_move_check(game_t *dama, point_t a){

    if(a.i == 0){
        return 0;
    }
    else if ((a.j==0 && dama->mat[a.i-1][a.j+1]->id == 0)                                   ||
              (a.j==dama->cols-1 && dama->mat[a.i-1][a.j-1]->id == 0)                       || 
              (a.j!=0 && a.j!=dama->cols-1 && dama->mat[a.i-1][a.j+1]->id == 0)             ||
              (a.j!=0 && a.j!=dama->cols-1 && dama->mat[a.i-1][a.j-1]->id == 0)              )
            return 1;
        else
            return 0;
}

int black_move_check(game_t *dama, point_t a){

    if(a.i == dama->rows-1){
        return 0;
    }
    else if ((a.j==0 && dama->mat[a.i+1][a.j+1]->id == 0)                                   ||
              (a.j==dama->cols-1 && dama->mat[a.i+1][a.j-1]->id == 0)                       ||
              (a.j!=0 && a.j!=dama->cols-1 && dama->mat[a.i+1][a.j+1]->id == 0)             ||
              (a.j!=0 && a.j!=dama->cols-1 && dama->mat[a.i+1][a.j-1]->id == 0)              )
            return 1;
        else
            return 0;
}

int dama_move_check(game_t *dama, point_t a){
    return (white_move_check(dama, a) || black_move_check(dama, a));
}

int white_capture_check(game_t *dama, point_t a, int turn){
    int e;

    e = enemy(turn);

    /* checks whether there are at least 2 rows above*/
    if(a.i<2) {
        /* if not, you cannot capture, there must be at least 3 rows */
        return 0;
    }
        /* checks if the pawn is at the upper left margin (col 0 and col 1) */
        /*  (3) if the move goes towards north-east, the boxpawn of arrival is empty and the boxpawn in the middle
         *  is occupied by an enemy, then returns 1; else 0. */
        /* checks if the pawn is at the upper right margin */
        /* (5) if the move goes towards north-west, the boxpawn of arrival is empty and the boxpawn in the middle
        *  is occupied by an enemy, then returns 1; else 0. */
        /* checks whether (3) or (5) are true, then move towards N-E or N-W*/
    else if(((a.j==0 || a.j==1) && ((dama->mat[a.i-1][a.j+1]->id == e+2 || dama->mat[a.i-1][a.j+1]->id == e+4) 
                && dama->mat[a.i-2][a.j+2]->id == 0))                                                                                           ||

            ((a.j==dama->cols-1 || a.j==dama->cols-2) && ((dama->mat[a.i - 1][a.j - 1]->id == e + 2 || dama->mat[a.i - 1][a.j - 1]->id == e + 4) 
                && dama->mat[a.i - 2][a.j - 2]->id == 0))                                                                                       ||

            ((a.j!=0 && a.j!=1 &&a.j!=dama->cols-1 && a.j!=dama->cols-2) &&
                (((dama->mat[a.i-1][a.j+1]->id == e+2 || dama->mat[a.i-1][a.j+1]->id == e+4)
                && dama->mat[a.i-2][a.j+2]->id == 0)||
                ((dama->mat[a.i-1][a.j-1]->id == e+2 || dama->mat[a.i-1][a.j-1]->id == e+4)
                && dama->mat[a.i-2][a.j-2]->id == 0)))                                                                                          ){

        return 1;
    }
    else {
        return 0;
    }
}

int black_capture_check(game_t *dama, point_t a, int turn){
    int e;

    e = enemy(turn);

    /* checks whether there are at least 2 rows below*/
    if(a.i > (dama->rows-3)){
        /* if not, you cannot capture, there must be at least 3 rows */
        return 0;
    }
        /* checks if the pawn is at the upper left margin (col 0 and col 1) */
        /*  (3) if the move goes towards south-east, the boxpawn of arrival is empty and the boxpawn in the middle
         *  is occupied by an enemy, then returns 1; else 0. */
        /* checks if the pawn is at the upper right margin */
        /*  (5) if the move goes towards south-west, the boxpawn of arrival is empty and the boxpawn in the middle
         *  is occupied by an enemy, then returns 1; else 0. */
        /* checks whether (3) or (5) are true, then move towards S-E or S-W*/

    else if(((a.j==0 || a.j==1) && ((dama->mat[a.i+1][a.j+1]->id == e+2 || dama->mat[a.i+1][a.j+1]->id == e+4)
           && dama->mat[a.i+2][a.j+2]->id == 0))                                                                                                ||

           ((a.j==dama->cols-1 || a.j==dama->cols-2) && ((dama->mat[a.i+1][a.j-1]->id == e+2 || dama->mat[a.i+1][a.j-1]->id == e+4)
           && dama->mat[a.i+2][a.j-2]->id == 0))                                                                                                ||
    
            ((a.j!=0 && a.j!=1 &&a.j!=dama->cols-1 && a.j!=dama->cols-2) &&  
            (((dama->mat[a.i+1][a.j+1]->id == e+2 || dama->mat[a.i+1][a.j+1]->id == e+4)
            && dama->mat[a.i+2][a.j+2]->id == 0)||
            ((dama->mat[a.i+1][a.j-1]->id == e+2 || dama->mat[a.i+1][a.j-1]->id == e+4)
            && dama->mat[a.i+2][a.j-2]->id == 0)))                                                                                              ){
        return 1;
    }else {
        return 0;
    }
}



int dama_capture_check(game_t *dama, point_t a, int turn){
    return white_capture_check(dama, a, turn) || black_capture_check(dama, a, turn);
}

int player_can_capture(game_t *dama, int turn){
    int i = 0, j = 0, flag = 0;
    
    for (i=0; i<dama->rows && flag == 0; i++){
        for(j=0; j<dama->cols && flag == 0; j++){

            point_t p;
            p.i = i;
            p.j = j;

            if(dama->mat[i][j]->id == turn+2 && ((turn==0 && white_capture_check(dama, p, turn)) || (turn==1 && black_capture_check(dama, p, turn))) ||
              (dama->mat[i][j]->id == turn+4 && dama_capture_check(dama, p, turn))                                                                   ){ 
                flag = 1;
            }
        }
    }

    return flag;
}

int player_can_move(game_t *dama, int turn){
    int i = 0, j = 0, flag = 0;

    for (i=0; i<dama->rows && flag == 0; i++){
        for(j=0; j<dama->cols && flag == 0; j++){

            point_t p;
            p.i = i;
            p.j = j;

            if(dama->mat[i][j]->id == turn+2 && ((turn==0 && white_move_check(dama, p)) || (turn==1 && black_move_check(dama, p)))                  ||
               (dama->mat[i][j]->id == turn+4 && dama_move_check(dama, p))                                                                          ){
                flag = 1;
            }
        }
    }
    return flag;
}

int legal_choice(game_t *dama, int turn, point_t a){
    int choice;

    if(dama->mat[a.i][a.j]->id== turn+2 || dama->mat[a.i][a.j]->id== turn+4){
        if (player_can_capture(dama,turn)){

            if((is_promoted (dama,a,turn) && (dama_capture_check(dama, a, turn)))               ||
              (!is_promoted (dama,a,turn) && turn == 0 && (white_capture_check(dama, a, turn))) ||
              (!is_promoted (dama,a,turn) && turn == 1 && (black_capture_check(dama, a, turn))) ){
                choice = 8;
            }else {
                choice = 11;
            }
        }
        else if((is_promoted (dama,a,turn) && (dama_move_check(dama, a)))                       ||
               (!is_promoted (dama,a,turn) && turn == 0 && white_move_check(dama, a))           ||
               (!is_promoted (dama,a,turn) && turn == 1 && black_move_check(dama, a))           ){
            choice = 9;
        }
        else {
            choice = 10;
        }
    }else{
        choice = 7;
    }
    return choice;
}


int illegal_move (game_t *dama, int turn, point_t a, point_t b, int have_to_capture){
    int move;
    point_t p;

    /* boxpawn is empty*/
    if(dama->mat[b.i][b.j]->id == 0){

        /* check forced capture */
        if(have_to_capture == 8){
            p = findmiddle(a, b);

            /* checks if the boxpawn you leaped over is occupied by an enemy */
            if(dama->mat[p.i][p.j]->id == enemy(turn)+2 || dama->mat[p.i][p.j]->id == enemy(turn)+4){

                /* checks if it is an officer */
                if(is_promoted (dama,a,turn)){

                    /* if distance, vertically and horizontally speaking, is equal to 2 */
                    if ( abs(b.i - a.i)==2 && abs(b.j - a.j)==2) {
                        move = 0;
                    }else {
                        move = 2;
                    }
                }

                    /* white's turn */
                else if(turn == 0){

                    /* checks if pawn is moved towards N-E or N-W */
                    if(a.i == (b.i)+2 && (a.j == (b.j)+2 || a.j == (b.j)-2)) {
                        move = 0;
                    }else {
                        move = 3;
                    }
                }
                    /* black's turn */
                else if(turn == 1){

                    /* checks if pawn is moved towards S-E or S-W */
                    if (a.i == b.i-2 && (a.j == b.j+2 || a.j == b.j-2)){
                        move = 0;
                    }else {
                        move = 3;
                    }
                }
            }else{
                move = 1;
            }
        }
            /* checks if you can only move without capturing */
        else if(is_promoted (dama,a,turn)){

            /* checks distance == 1*/
            if(abs(b.i - a.i)==1 && abs(b.j - a.j)==1) {
                move = 0;
            }else {
                move = 4;
            }
        }
            /* white pawn can move only N-E or N-W & black pawn can move only S-E or S-W*/
        else if ((turn == 0 && (((b.i==(a.i)-1) && (b.j==(a.j)-1)) || ((b.i==(a.i)-1)&& (b.j==(a.j)+1)))) ||
                (turn == 1 && (((b.i==(a.i)+1) && (b.j==(a.j)-1)) || ((b.i==(a.i)+1)&& (b.j==(a.j)+1))))){
            move = 0;
        }
        else{
            move = 5;
        }
    }
    else{
        move = 6;
    }

    return move;
}

int enemy(int turn){

    if(turn == 0)
        return 1;
    else{
        return 0;
    }
}

int is_promoted (game_t *dama, point_t a, int turn){

    if(dama->mat[a.i][a.j]->id == turn+4)
        return 1;
    else{
        return 0;
    }
}

/*returns 0 if no winner, 1 if white player is the winner, 2 if black player is the winner*/
int victory(game_t *dama, int rows, int cols, int turn, int moves){

    if(!player_can_capture(dama,enemy(turn)) && !player_can_move(dama,enemy(turn))){
        print (*dama, rows, cols);
        printf("Total moves = %d\n", moves);
        return turn+1;
    }
    else if(!player_can_capture(dama,turn) && !player_can_move(dama,turn)){
        print (*dama, rows, cols);
        printf("Total moves = %d\n", moves);
        return (enemy(turn)+1);
    }

    else{
        return 0;
    }
}

/* ----------------------------------------------------- Part 5 ----------------------------------------------------- */

void add_at_the_end(point_list_t *l, point_t p){
    point_cell_t * temporary;
    point_cell_t * i;

    temporary = (point_cell_t *) malloc (sizeof(point_cell_t));
    assert(temporary!=NULL);
    temporary->p = p;
    temporary->next = NULL;

    if(l->list==NULL){

        l->list=temporary;
    }else{
        i=l->list;

        while (i->next!=NULL){
            i = i->next;
        }
        i->next = temporary;
    }

    l->dim +=1;
}

point_list_t * avaiable_choices(game_t *dama, int rows, int cols, int turn){
    int i = 0, j = 0;
    point_list_t * l;

    l = create_choices_list();

    for (i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            point_t p;
            p.i = i;
            p.j = j;

            /* Checks if the pawn is a soldier and whether it is forced to capture*/
            /* if it is an officer, checks whether it can capture*/
            /* Checks the if it is a soldier and whether it may be moved*/
            /* if it is an officer, checks whether it can move*/
            if((turn ==1 && dama->mat[i][j]->id == turn+2 && black_capture_check(dama, p, turn))                            || 

               (turn ==0 && dama->mat[i][j]->id == turn+2 && white_capture_check(dama, p, turn))                            ||

               (dama->mat[i][j]->id == turn+4 && dama_capture_check(dama, p, turn))                                         ||

               (turn == 1 && dama->mat[i][j]->id == turn+2 && black_move_check(dama, p)) && !player_can_capture(dama, turn) || 

               (turn == 0 && dama->mat[i][j]->id == turn+2 && white_move_check(dama, p)) && !player_can_capture(dama, turn) || 

               (dama->mat[i][j]->id == turn+4 && dama_move_check(dama, p))               && !player_can_capture(dama, turn)  ){

            add_at_the_end(l, p);
            }
        }
    }
    return l;
}

void computer_moves(game_t *dama, int rows, int cols, int turn){
    int flag = 0, i = 0 , j = 0, size=0, pos=0;
    point_list_t * l;
    point_cell_t * point_a ;
    point_cell_t * pos_point_a;
    point_t b;

    srand(time(NULL));
    l = avaiable_choices(dama, rows, cols, turn);
    pos_point_a = l->list;
    size = l->dim;
    pos = rand() % size;

    for(i=0;i<pos;i++){
        pos_point_a = pos_point_a->next;
    }

    point_a = pos_point_a;

    for(i=0; i<rows && flag==0; i++){
        for(j=0; j<cols && flag==0; j++){

            b.i = i;
            b.j = j;

            if (!illegal_move (dama, turn, point_a->p, b, legal_choice(dama, turn, point_a->p))){
                flag = 1;
            }
        }
    }

    move(dama, point_a->p , b);
    printf("Computer moves from %c%d to %c%d\n", (point_a->p.j)+65, ++(point_a->p.i), (b.j)+65, ++(b.i));
    promotion(dama, turn);
    free_choices_list(l);
}

/* ----------------------------------------------------- Part 6 ----------------------------------------------------- */

void error(game_t *dama, int rows, int cols,int turn, int code_error){
    point_list_t * l;
    point_cell_t * point_a;

    printf("Laska-Bot Says:\n");

    if (code_error ==1){
        printf("FORCING CAPTURE - Pieces must capture if in a position to do so.\n You can move only the pawn inside one of this boxes:\n");
        l = avaiable_choices(dama, rows, cols, turn);
        point_a = l->list;

        while(point_a->next!=NULL){
            printf(" %c%d  or ", (point_a->p.j)+65 , ++(point_a->p.i));
            point_a = point_a->next;
        }

        printf(" %c%d .\n", (point_a->p.j)+65 , ++(point_a->p.i));
        free_choices_list(l);
    }
    else if(code_error ==2){
        printf("The Officer (promoted pawn) may capture only in the 4 diagonals if the adjacet is a foe's pawn and the next on the diagonal is free.\n");
    }else if(code_error ==3){
        printf("The pawn may capture only in the 2 diagonals forward if the adjacet is a foe's pawn and the next on the diagonal is free.\n");
    }else if(code_error ==4){
        printf("The Officer (promoted pawn) may move only in the 4 diagonals if it's free.\n");
    }else if(code_error ==5){
        printf("The pawn may move only in the 2 diagonals forward if it's free.\n");
    }else if(code_error ==6){
        printf("You can move only into free white empty bowes\n");
    }else if(code_error == 7){
        printf("The selected box must contain your pawn\n");
    }else if(code_error == 10){
        printf("The pawn you choosed can not be moved\n");
    }else if(code_error == 11){
        printf("Unfortunately, you can't choose this pawn because you are forced to capture foe's pawns, so you must choose an other pawn.\nYou can move only the pawn inside one of this boxes:\n");
        l = avaiable_choices(dama, rows, cols, turn);
        point_a = l->list;

        while(point_a->next!=NULL){
            printf(" %c%d  or ", (point_a->p.j)+65 , ++(point_a->p.i));
            point_a = point_a->next;
        }

        printf(" %c%d .\n", (point_a->p.j)+65 , ++(point_a->p.i));
        free_choices_list(l);
    }
}

int coin_toss(){
    double n;
    int i;

    for(i = 0; i<100; i++){
        n = ((double)rand() / (RAND_MAX));
    }

    if(n>= 0.5){
        n = 1;
    }else{
        n = 0;
    }

    return (int)n;
}

int check_answer(){
    int answer = 0, cond = 1;
    char decision[3];

    while (cond){
        scanf("%s", decision);
        if (decision[0] == 'y' && decision [1] == 'e' && decision[2] == 's') {
            printf("\n");
            answer = 1;
            cond = 0;

        } else if (decision[0] == 'n' && decision[1]== 'o') {
            answer = 0;
            cond = 0;
        }
    }

    return answer;
}

void choose_menu(){
    int cond = 1, input = -1, sup = -1;

    printf("\n");
    printf("You on the left will be Player-1 and you on the right will lose.\n");
    printf("Sorry, I'm a jokester. You, on the right, will be Player-2.\n");
    printf("\n");
    printf("You can either toss a coin (type: 0) or decide for yourselves (type: 1), just let me know");
    printf("\n");
    printf("\n");

    while(cond){
        scanf("%d", &input);

        if(input == 1){
            printf("Good job, less work for my algorithm. YAYYY\n");
            printf("Remember: White starts first.\n");
            cond = 0;
        }else if (input == 0){
            printf("Oh no, I don't have any spare change on me\n");
            printf("\n");
            printf("Luckily for you I had a bitcoin left. We can toss this one, but don't lose it pls\n");
            printf("As now, it is worth over 40k $\n");
            printf("\n");
            printf("Now, here it comes!\n");
            printf("\n");
            sup = coin_toss();

            if(sup == 1){
                printf("\n");
                printf("Player-1 you will be using the white pawns.\n");
                printf("Player-2 you will move after they are done.\n");
                printf("\n");
            }else if (sup == 0){
                printf("\n");
                printf("Player-2 you will be using the white pawns.\n");
                printf("Player-1 you will move after they are done.\n");
                printf("\n");
            }
            cond = 0;
        }
    }
}

int main_menu(){
    int input;
    int cond = 1;

    printf("\n");
    printf("Now, let me introduce you what modalities we built. Here you find the menu:\n");

    printf("# //==================[]======\\\\\n"
           "# ||    Game Mode     || Code ||\n"
           "# |]==================[]======[|\n"
           "# || Single Player    ||    0 ||\n"
           "# || Player vs Player ||    1 ||\n"
           "# || Player vs Pc     ||    2 ||\n"
           "# || Pc vs Pc         ||    3 ||\n"
           "# \\\\==================[]======//");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("You can Quit at any time by typing (type: x) or give up (type: k), unless two PCs are playing.\n");
    printf("Yeah, they are super-Fast\n");
    printf("\n");
    printf("Let's hear it then, have you made up your mind? Type the code of the game to play");
    printf("\n");
    printf("\n");

    do{
        scanf("%d", &input);
        if(input >= 0 && input <= 3){
            cond = 0;
        }
    }while(cond);

    if(input == 0) {
        printf("You chose: Single Player");
        printf("\n");
        printf("Man, if I were you, I'd make some new friends...");
        printf("\n");
        printf("\n");
        return input;
    }else if (input == 1) {
        printf("You chose: Player vs Player");
        printf("\n");
        printf("Finally, you got some friends to play with!");
        printf("\n");
        printf("\n");
        return input;
    }else if (input == 2) {
        printf("You chose: Player vs Pc");
        printf("\n");
        printf("I'm impressed you managed to lose your friends that fast, you really are a disaster at social life");
        printf("\n");
        printf("\n");
        return input;
    }else if (input == 3) {
        printf("You chose: Pc vs Pc");
        printf("\n");
        printf("I know you might not care, but watching two computers play against each other... is pretty lame");
        printf("\n");
        printf("\n");
        return input;
    }

}

int decision_menu() {
    int res = 0, cond = 1;
    char decision[3];

    printf("Are you ready to play?(yes/no)\n");
    printf("\n");

    while (cond){
        scanf("%s", decision);
        if (decision[0] == 'y' && decision [1] == 'e' && decision[2] == 's') {
            printf("Very Well, let's go on\n");
            printf("\n");
            res = 1;
            cond = 0;

        } else if (decision[0] == 'n' && decision[1]== 'o') {
            res = 0;
            cond = 0;
            goodbye();
        }
    }

    return res;
}

void result_menu(int winner) {

    if (winner == 0) {
        printf("\n");
        printf("White gamer is the winner!");
        printf("\n");
    } else if (winner == 1) {
        printf("\n");
        printf("Black player is the winner!");
        printf("\n");
    } else if (winner == 10) {
        printf("\n");
        printf("Thanks for trying.");
        printf("\n");
    }
}

void hello(){
    int cond = 1;
    char decision[3];

    printf(" __       __            __                                                      __               \n");
    printf("|  \\  _  |  \\          |  \\                                                    |  \\              \n");
    printf("| $$ / \\ | $$  ______  | $$  _______   ______   ______ ____    ______         _| $$_     ______  \n");
    printf("| $$/  $\\| $$ /      \\ | $$ /       \\ /      \\ |      \\    \\  /      \\       |   $$ \\   /      \\ \n");
    printf("| $$  $$$\\ $$|  $$$$$$\\| $$|  $$$$$$$|  $$$$$$\\| $$$$$$\\$$$$\\|  $$$$$$\\       \\$$$$$$  |  $$$$$$\\\n");
    printf("| $$ $$\\$$\\$$| $$    $$| $$| $$      | $$  | $$| $$ | $$ | $$| $$    $$        | $$ __ | $$  | $$\n");
    printf("| $$$$  \\$$$$| $$$$$$$$| $$| $$_____ | $$__/ $$| $$ | $$ | $$| $$$$$$$$        | $$|  \\| $$__/ $$\n");
    printf("| $$$    \\$$$ \\$$     \\| $$ \\$$     \\ \\$$    $$| $$ | $$ | $$ \\$$     \\         \\$$  $$ \\$$    $$\n");
    printf(" \\$$      \\$$  \\$$$$$$$ \\$$  \\$$$$$$$  \\$$$$$$  \\$$  \\$$  \\$$  \\$$$$$$$          \\$$$$   \\$$$$$$ \n");
    printf("                                                                                                 \n");
    printf("                                                                                                 \n");
    printf("                                                                                                 \n");
    printf(" __                           __                        ______    ______   ________  ________    \n");
    printf("|  \\                         |  \\                      /      \\  /      \\ |        \\|        \\   \n");
    printf("| $$       ______    _______ | $$   __  ______        |  $$$$$$\\|  $$$$$$\\ \\$$$$$$$$ \\$$$$$$$$   \n");
    printf("| $$      |      \\  /       \\| $$  /  \\|      \\        \\$$__| $$| $$$\\| $$    /  $$     /  $$    \n");
    printf("| $$       \\$$$$$$\\|  $$$$$$$| $$_/  $$ \\$$$$$$\\       /      $$| $$$$\\ $$   /  $$     /  $$     \n");
    printf("| $$      /      $$ \\$$    \\ | $$   $$ /      $$      |  $$$$$$ | $$\\$$\\$$  /  $$     /  $$      \n");
    printf("| $$_____|  $$$$$$$ _\\$$$$$$\\| $$$$$$\\|  $$$$$$$      | $$_____ | $$_\\$$$$ /  $$     /  $$       \n");
    printf("| $$     \\\\$$    $$|       $$| $$  \\$$\\\\$$    $$      | $$     \\ \\$$  \\$$$|  $$     |  $$        \n");
    printf(" \\$$$$$$$$ \\$$$$$$$ \\$$$$$$$  \\$$   \\$$ \\$$$$$$$       \\$$$$$$$$  \\$$$$$$  \\$$       \\$$         \n");
    printf("\n");
    printf("\n");
    printf("Hi there, welcome to Laska 2077!\n");
    printf("Check out the official site of the game here: http://www.lasca.org/ \n");
    printf(" ******** DISCLAIMER: The input you may type is always shown, other kinds of input may make the game fail. *********\n");
    printf("\n");
    printf("\n");
    printf("Now, let's welcome Lask-Bot from the year 2077. It will give you a brief insight of the game.");
    printf("\n");
    printf("Laska-Bot: Here I am fellow player, would you like me to explain the game to you?(yes/no)\n");
    printf("\n");

    while (cond){
        scanf("%s", decision);

        if (decision[0] == 'y' && decision [1] == 'e' && decision[2] == 's') {
            printf("\n");
            printf("Laska-Bot: Awesome, here you can find the rules!\n");
            printf("\n");
            printf(" - - - - - The Equipment - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf("A 7x7 board, 11 black pawns and 11 white pawns.\n");
            printf("\n");
            printf(" - Why is it 7x7?\n");
            printf("\tThe reason for using a 7 x 7 board is to remove the possibility for the game to end in a draw.\n");
            printf("\n");
            printf(" - - - - - The Pawns - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf("SOLDIER: A single counter. It can move only diagonally forwards.\n");
            printf("\tWhen it reaches the opponent 's side of the board, it is promoted to an officer.\n");
            printf("OFFICER: A single counter. It can move in either direction, forwards or backwards diagonally.\n");
            printf("COLUMN:  A stack of two or more soldiers or officers of one colour, possibly containing prisoners\n");
            printf("\tIt is moved as a single piece. The top counter, the commander, determines who owns and moves the column.\n");
            printf("COMMANDER: The top counter of a column. Only if it is an officer may the column move in either direction.\n");
            printf("\n");
            printf(" - - - - - The Moves & Constraints - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf(" - Who moves first?:\n");
            printf("\tWhite Player starts first. When they their turn is over, e.g. after their move, it's Black's turn and viceversa.");
            printf(" - How to move a pawn:\n");
            printf("\tJust type the coordinates as the game is going to ask you. If it is a legal move, the pawn will be moved there\n");
            printf(" - The Capture:\n");
            printf("\tWhen you move your pawn, if there's another pawn in the way and it's your enemy's you capture it automatically.\n");
            printf(" - Forcing Capture:\n");
            printf("\tIf you have the possibility to capture a pawn, you must do it.\n");
            printf(" - Freeing prisoners:\n");
            printf("\tIf you leap over an enemy column, you capture the commander and free your pawn.\n");
            printf("\n");
            printf(" - - - - - The Promotion - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf(" - Becoming an OFFICER:\n");
            printf("\tWhen a column reaches the opposite end of the board, the opponent’s front line, its commander is promoted.\n");
            printf("\tHowever, promotion only comes at the end of a move.\n");
            printf("\tIf captured, an officer retains its rank for use if later released.\n");
            printf("\n");
            printf(" - - - - - Extra Rules for MINI LASCA VERSION ONLY - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf("\t1) You can only capture one prisoner per turn.\n");
            printf("\t2) Columns have a maximum height of 3 pawns. The very next prisoner captured is removed from the table.\n");
            printf("\n");
            printf(" - - - - - The End of the Game - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
            printf("When a player can only make illegal moves or loses all of their pawns, they lose the game.\n");
            printf("\n");
            printf("\n");
            printf("\n");
            cond = 0;
        } else if (decision[0] == 'n' && decision[1]== 'o') {
            printf("You sure are an expert then. I'll keep an eye on you, anyway.\n");
            printf("Don't make any silly mistake!\n");
            printf("\n");
            cond = 0;
        }
    }
}

void goodbye(){
    printf("\n");
    printf("KKKKKKKKKKKXXKKKKKKK00OOOkkkO00Odl;'...'','.....'......,,,'....:lc;;;;ldx0KXKKKK000000OOOOkkkkkxxxxx\n");
    printf("KKKKKKKKKKKKKKKKKKK00OOkkkkkxo;.............';::::::::;;;::,...'....','..,:loxOOkkkxxdddooooollllccc\n");
    printf("KKKKKKKKKKKK00000000OOOkOkd:.   ...........',,'..........,:;,...    .  ......':lolcc::cccccllllccc::\n");
    printf("KKK00000000000OOOOOOOOOkx:.   .......                      .'...             ...,:::::clloooooooooll\n");
    printf("0000000000OOOOOOOOOOOkxl'     .               ...''',,,'..........               .,cllloodddxxxxxddd\n");
    printf("00000000000OOOOOOOOOkxc.                  ...':ldxkkxxxxdddddol:'.......           'cddddxxxxkkkkxxx\n");
    printf("00000000OOOOOOOOkkkkx:.       .....      .,:odk0KKXXKKKXXXXXKKK0kdc:coxdc'.         .lxxxxxkkkkkkkkk\n");
    printf("OOOOOOOOOkkkkkkkkkkd;.      ..   .     .':dk0KKXXXNNNNNNNNNNNNNNXK0OO0KXKkl'         'oxkkkkkkkkkkkk\n");
    printf("kkkkkxxxxxxxxxxxxxo;.                 .,lxO0KXXXNNNNNNNNNNNNNNNNNNNNNNNNXX0x;.       .cdkkkkkkkkkkkk\n");
    printf("ddddoooooooooddddc:,.              ...;oxO00KXXXXXXXNNNNNXNNNNNNNNNNNNNNXXK0k:        ,okOkkkkkkkkkk\n");
    printf("lccc::::ccllooddc::.                .,lxO0KKKKXXXXXXXXXXKKKKXXXXXXXXXXXXXKKK0d'       .:xOOOOOOkkkkk\n");
    printf(";;;;::cclloddxxl:c.                .';ldk0KKK0KKKKKKKK00000KK000KKKKKKKKKKK0OOl.      .,oOOOOOOkkkkk\n");
    printf("cccclloooddxxkd;,,.                .':lxkO00000KKKK000000OOOOOOOOO000000000OOOd'     .'':kkkkkkkkkkk\n");
    printf("ooddddddxxxkkxc,'.                 .,coxkO00000KKKKK00000OOOOkOOOOOOkOOOOOkOkkx;     .,',okxkxxxxxxk\n");
    printf("xkkkkkkkkkkkxo;..                 ..:odkOO000KKKKKKKKKKK0000000OOOOkkOOOOkkkOOk;     .,;,:xxxxxxxxxx\n");
    printf("OOOOOOOOOkkkoc,..                .'cdkOO0000KKXXXXXXXXXXXKKKKKK00OOO0000OO0OOkx;      ,:',dxdxxxxxxk\n");
    printf("KKOkO0KKK00kl;'.                .,lxO0KKKKKKKKKK00000KKKKK000000000KKXXKKKK00Ox,      ';.'lddddddxxx\n");
    printf("00kxk000000kl..                .;okO0KXXXK0Okxdlcc::;:clodxxxxxkkOOOOO000KKKK0x.      .'..:ccclllooo\n");
    printf("loooxkOOkkko,                 .,lkO0KKKKK0kdolllc::;;,''''';:clodxxxxdxkOOOO00x'      .....''',,;;;;\n");
    printf("',;:ldxkkkd;.                 .:dO00KKK0Okdlc:;,'.....''''',,;cdxxdoc:::;;;;::c.          ..........\n");
    printf(".',;:cllodl.             ...  'cxO00KKKKK0Okxdoooc:;,:c;.',,;cdkOko;......',;;,.          .         \n");
    printf(",,,,,,;;;c,              .....;ldkO0KKKXKKKKK0OOxdddoolc:cccldOKK0l...  ...';c,        . ..         \n");
    printf(":cc:,',,,,.           .......,;ldxO00KKKXXXKKKK0Okxxxdooodxxk0KXNXk:;:::cl:,;c'        ....         \n");
    printf("dxkxo:,','.           ..',,,,,:ldkkkOOO0KKKXXKKK000000OOO000KKXXNNKdcclloddddo,        .......      \n");
    printf("OOkkxl:,:;.            .,;;:;:lodxkkOkkO000KKKKKKKKKKKKKKKKKKKXXNNXOddxdxxkkxd'        . ..... .    \n");
    printf("00Okkxocc:.              ':::cooldkkkkxkkOO00KKKKKKXXXK0OOO000KXNNX0OOOOOOOkko.        ..........   \n");
    printf("KKK00OOxl;.              .:cloloooxkkxxxxxkOO00000K00OkdxOKXKKKXNXXKOO000Okxx:.        ......... .  \n");
    printf("XXXXKK0kl.               .cddllddlllllodddxkkkkOOOkkxdllkXXNNNXXXXX0xdkOOOkxc.         .............\n");
    printf("XXXXKKOl'..        ..    .cddloxxl:;'',;ccldxkkkkxxdodddddooddxO0OOkxooxkkxc.         ..............\n");
    printf("O00O0k:...         ...   .cdolloo:''....',;ldkkkxxdxkOOko:'...,cllcllcldxxc.          .,,'''''......\n");
    printf("dxdol,..  .        ...   .;oxdc;;,........;odxxxxkOOOOOkdc,.......;do:lddc.          .:c,''''''''...\n");
    printf(",,,'.    ..         ..    .:ddl;,'.....  .;dxxxxdooolll:,''........:llll;.           .;:'''''',,,'''\n");
    printf("....    ...               .'cllc;,'''.   .;dOkd:,'...','............'cl,             .'''''',,,,,,;;\n");
    printf("'.. ......                 .;clll:,'..  .,lxkd;......................;,              .''',,,,,;;;;::\n");
    printf(",;'.',,..                   .;cll:;,.....,col;..,;:::;;,,,,,',,,,.  .,.             .',;;;;;;;:::ccc\n");
    printf(",..'...                      .,::,'..,,...,;;',coodxdloooolllllll,..'.              .;::::::::ccclll\n");
    printf(". ..                          .'''..':l;'',,'':ldxxdolll::c:;:cll;...             ..'clllcccccccllll\n");
    printf(":,'..         ....             ..'..',;'...'',:lxOOkxol:;,,:;,;:;'.              .',cllooollccclllll\n");
    printf("kdc::;,.   ........              ........ ...';lxO00Oxoc;,'';cc:'.              .,,;cllooollcclllllo\n");
    printf("clollc'. ............                      ...':loodxdl:,',,,;:'.              .''',clooooollllllloo\n");
    printf("...''''......''.......                       .',;;;;;;;:;..,'''.               .'',:loooooollllloooo\n");
    printf(".',;;cc;,...'''''.......                     ..... ....',......                .:llooooooooolllooooo\n");
    printf("cllccllc:;'....''...........                    .       ..       .,;;..,;.    ..cooooooodooolllooooo\n");
    printf("ddoooodolc:;,'................     .                        .;c;',cc;:lk0x;...',cododdooddoolloooood\n");
    printf("xxxdddddolcc:;'................     .                    'lodO00kdol:;cx0KOo::clllodxxddddoooloooodd\n");
    printf("xxxxxxdollllc:,'................                    ...  ,0X00O000OkolloxOOOkdxdlcldxdddddoooooodddd\n");
    printf("kxxxxdooooolcc:;,'...............                        .dOO0OOOkdl:;'.';lolc::;:ldxxxddddooooddddd\n");
    printf("xxxdooooooollc::;,'..............                         .';cll:,..      ...   .'cdxxxddddooddddddd\n");
    printf("xxdoodddooollcc:;;,'...............                                              .cdxxxddddddddddddd\n");
    printf("xoodddddoolllcc:;;,,'...............      ...        .         ..                .:xkkxxxddddddddddx");
    printf("\n");
    printf("\n");
    printf("Keanu says 'You're breathtaking!' ");
    printf("\n");
    printf("\n");

}

void credits(){
    printf("\n");
    printf("\n");
    printf("Credits to: Gianmaria & Aleksandra");
    printf("\n");

}
