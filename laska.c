#include "laska.h"

tgame * create(int cols,int rows){
    tgame *dama;
    int i, j;

/*allocates space to struct*/
    dama=(tgame*)malloc(sizeof(tgame));                       
    assert(dama!=NULL);

/*saves dimensions*/
    dama->rows=rows;                                          
    dama->cols=cols;

/* allocates vector rows pointers */
    dama->mat=(boxpawn***)malloc(sizeof(boxpawn**)*rows);     
    assert(dama->mat!=NULL);

/*allocates pawns pointers and boxes*/
    for(i=0;i<rows;i++){

        dama->mat[i]=(boxpawn**)malloc(sizeof(boxpawn*)*cols);
        assert(dama->mat[i]!=NULL);
        for(j=0;j<cols;j++){

            dama->mat[i][j]=(boxpawn*)malloc(sizeof(boxpawn));
            assert(dama->mat[i][j]!=NULL);
            dama->mat[i][j]->next=NULL;
        }
    }

    return dama;
}

point_list * create_choices_list(){
    point_list *l;

    l = (point_list *) malloc(sizeof(point_list));
    assert(l!=NULL);
    l->list = NULL;
    l->dim = 0;

    return l;
}

void initialize(tgame * dama, int cols, int rows){
    int i = 0, j = 0;

    /*chessboard creation*/
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

void freegame(tgame *dama, int rows, int cols) {
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

void free_choices_list(point_list * l){
    point_cell * temporary;

    if(l->list!=NULL){
        temporary = l->list;

        while(temporary->next!= NULL){
            temporary = temporary->next;
        }
        free (temporary);
    }
    free (l);
}

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

void print(tgame dama, int rows , int cols){
    int i = 0, j = 0, z = 0, empty = 0;
    boxpawn **t;

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

            for(z=0; z<3 && !empty ;z++){
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
                if((*t)->next!=NULL)
                    t = &(dama.mat[i][j]->next);
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

void add(tgame *dama, int pawn, int r, int c){

    if (dama->mat[r][c]->id==0){
        dama->mat[r][c]->id = pawn;
    }
    else{
        boxpawn *n = (boxpawn *) malloc(sizeof(boxpawn));
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

int remove_pawn(tgame *dama, int r, int c){
    int estract;
    
    if(dama->mat[r][c]->next==NULL){
       estract = dama->mat[r][c]->id;
       dama->mat[r][c]->id= 0;
   }
   else{
       boxpawn *element = dama->mat[r][c];
       estract = dama->mat[r][c]->id;
       dama->mat[r][c] = dama->mat[r][c]->next;
       free(element);
   }

   return estract;
}

int white_move_check(tgame *dama, point a){

    if(a.i == 0){
        return 0;
    }
    else if (a.j==0){
        if(dama->mat[a.i-1][a.j+1]->id == 0) {
            return 1;
        }else{
            return 0;
        }
    }
    else if(a.j==dama->cols-1){
        if (dama->mat[a.i-1][a.j-1]->id == 0) {
            return 1;
        }else {
            return 0;
        }
    }
    else{
        if(dama->mat[a.i-1][a.j+1]->id == 0 || dama->mat[a.i-1][a.j-1]->id == 0) {
            return 1;
        }else {
            return 0;
        }
    }
}

int black_move_check(tgame *dama, point a){

    if(a.i == dama->rows-1){
        return 0;

    }else if (a.j==0){

        if(dama->mat[a.i+1][a.j+1]->id == 0){
            return 1;
        }else {
            return 0;
        }
    }
    else if(a.j==dama->cols-1){

        if (dama->mat[a.i+1][a.j-1]->id == 0){
            return 1;
        }else {
            return 0;
        }
    }
    else{

        if(dama->mat[a.i+1][a.j+1]->id == 0 || dama->mat[a.i+1][a.j-1]->id == 0){
            return 1;
        }else {
            return 0;
        }
    }
}

int dama_move_check(tgame *dama, point a){
    return (white_move_check(dama, a) || black_move_check(dama, a));
}

int white_capture_check(tgame *dama, point a, int turn){
    int e;

    e = enemy(turn);

    if(a.i<2) {
        return 0;
    }else if(a.j==0 || a.j==1){
        if((dama->mat[a.i-1][a.j+1]->id == e+2 || dama->mat[a.i-1][a.j+1]->id == e+4)
            && dama->mat[a.i-2][a.j+2]->id == 0) {
            return 1;
        }else {
            return 0;
        }
    }
    else if (a.j==dama->cols-1 || a.j==dama->cols-2) {
        if ((dama->mat[a.i - 1][a.j - 1]->id == e + 2 || dama->mat[a.i - 1][a.j - 1]->id == e + 4)
            && dama->mat[a.i - 2][a.j - 2]->id == 0) {

            return 1;
        } else{
            return 0;
        }
    }
    else{
        if(((dama->mat[a.i-1][a.j+1]->id == e+2 || dama->mat[a.i-1][a.j+1]->id == e+4)
            && dama->mat[a.i-2][a.j+2]->id == 0)||
            ((dama->mat[a.i-1][a.j-1]->id == e+2 || dama->mat[a.i-1][a.j-1]->id == e+4)
            && dama->mat[a.i-2][a.j-2]->id == 0)) {

            return 1;
        }
        else {
            return 0;
        }
    }
}

int black_capture_check(tgame *dama, point a, int turn){
    int e;

    e = enemy(turn);

    if(a.i > (dama->rows-3)){
        return 0;
    } else if(a.j==0 || a.j==1){
        if((dama->mat[a.i+1][a.j+1]->id == e+2 || dama->mat[a.i+1][a.j+1]->id == e+4)
            && dama->mat[a.i+2][a.j+2]->id == 0) {
            return 1;
        }else {
            return 0;
        }
    }
    else if (a.j==dama->cols-1 || a.j==dama->cols-2){
        if((dama->mat[a.i+1][a.j-1]->id == e+2 || dama->mat[a.i+1][a.j-1]->id == e+4)
            && dama->mat[a.i+2][a.j-2]->id == 0){
            return 1;
        }else {
            return 0;
        }
    }
    else{
        if(((dama->mat[a.i+1][a.j+1]->id == e+2 || dama->mat[a.i+1][a.j+1]->id == e+4)
            && dama->mat[a.i+2][a.j+2]->id == 0)||
            ((dama->mat[a.i+1][a.j-1]->id == e+2 || dama->mat[a.i+1][a.j-1]->id == e+4)
            && dama->mat[a.i+2][a.j-2]->id == 0)) {
            return 1;
        }else {
            return 0;
        }
    }
}

int dama_capture_check(tgame *dama, point a, int turn){
    return white_capture_check(dama, a, turn) || black_capture_check(dama, a, turn);
}

int player_can_capture(tgame *dama, int turn){
    int i = 0, j = 0, flag = 0;
    
    for (i=0; i<dama->rows && flag == 0; i++){
        for(j=0; j<dama->cols && flag == 0; j++){

            point p;
            p.i = i;
            p.j = j;

            if(dama->mat[i][j]->id == turn+2 ){
                if((turn==0 && white_capture_check(dama, p, turn)) || (turn==1 && black_capture_check(dama, p, turn))) {
                    flag = 1;
                }
            }else if(dama->mat[i][j]->id == turn+4 ){
                if(dama_capture_check(dama, p, turn)) {
                    flag = 1;
                }
            }
        }
    }

    return flag;
}

int player_can_move(tgame *dama, int turn){
    int i = 0, j = 0, flag = 0;
    
    for (i=0; i<dama->rows && flag == 0; i++){
        for(j=0; j<dama->cols && flag == 0; j++){

            point p;
            p.i = i;
            p.j = j;

            if(dama->mat[i][j]->id == turn+2 ){
                if((turn==0 && white_move_check(dama, p)) || (turn==1 && black_move_check(dama, p))) {
                    flag = 1;
                }
            }else if((dama->mat[i][j]->id == turn+4) && (dama_move_check(dama, p))){
                flag = 1;
            }
        }
    }
    return flag;
}

int legal_choice(tgame *dama, int turn, point a){
    int choice;

    if(dama->mat[a.i][a.j]->id== turn+2 || dama->mat[a.i][a.j]->id== turn+4){
        if (player_can_capture(dama,turn)){

            if(is_promoted (dama,a,turn)){

                if (dama_capture_check(dama, a, turn)) {
                    choice = 8;
                }else {
                    choice = 11;
                }
            }else{

                if(turn == 0){

                    if(white_capture_check(dama, a, turn)){
                        choice = 8;
                    }else {
                        choice = 11;
                    }
                }else{

                    if(black_capture_check(dama, a, turn)) {
                        choice = 8;
                    }else {
                        choice = 11;
                    }
                }
            }
        }
        else if(is_promoted (dama,a,turn)){

            if(dama_move_check(dama, a)) {
                choice = 9;
            }else {
                choice = 10;
            }
        }else{

            if ((turn == 0 && white_move_check(dama, a)) || (turn == 0 && white_move_check(dama, a))) {
                choice = 9;
            }else{
                choice = 10;
            }
        }
    }else{
        choice = 7;
    }

    return choice;
}

int illegal_move (tgame *dama, int turn, point a, point b, int have_to_capture){
    int move;

    if(dama->mat[b.i][b.j]->id == 0){
        if(have_to_capture == 8){
            point p = findmiddle(a, b);
            if(dama->mat[p.i][p.j]->id == enemy(turn)+2 || dama->mat[p.i][p.j]->id == enemy(turn)+4){
                if(is_promoted (dama,a,turn)){
                    if ( abs(b.i - a.i)==2 && abs(b.j - a.j)==2) {
                        move = 0;
                    }else {
                        move = 2;
                    }
                }
                else if(turn == 0){
                    if(a.i == (b.i)+2 && (a.j == (b.j)+2 || a.j == (b.j)-2)) {
                        move = 0;
                    }else {
                        move = 3;
                    }
                }
                else if(turn == 1){
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
        else if(is_promoted (dama,a,turn)){
            if(abs(b.i - a.i)==1 && abs(b.j - a.j)==1) {
                move = 0;
            }else {
                move = 4;
            }
        }else if (turn == 0 && (((b.i==(a.i)-1)&& (b.j==(a.j)-1)) || ((b.i==(a.i)-1)&& (b.j==(a.j)+1)))){
            move = 0;
        }else if (turn == 1 && (((b.i==(a.i)+1)&& (b.j==(a.j)-1)) || ((b.i==(a.i)+1)&& (b.j==(a.j)+1)))){
            move = 0;
        }else{
            move = 5;
        }
    }else{
        move = 6;
    }

    return move;
}

point findmiddle(point a, point b){
    point middle;

    middle.i = (a.i+b.i)/2;
    middle.j = (a.j+b.j)/2;

    return middle;
}

void move (tgame *dama, point a, point b){
    int conquered;
    boxpawn * temporary;
    point middle;


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

int enemy(int turn){

    if(turn == 0)
        return 1;
    else{
        return 0;
    }
}

int is_promoted (tgame *dama, point a, int turn){

    if(dama->mat[a.i][a.j]->id == turn+4)
        return 1;
    else{
        return 0;
    }
}

void promotion(tgame *dama, int turn){
    int i = 0, j = 0;

    turn == 0 ? i=0 : (i=((dama->rows)-1));
        
    for (j=0; j<dama->cols; j++){
        if (dama->mat[i][j]->id == turn+2) {
            dama->mat[i][j]->id += 2;
        }
    }
}

/*returns 0 if no winner, 1 if white player is the winner, 2 if black player is the winner*/
int victory(tgame *dama, int rows, int cols, int turn, int moves){

    if(!player_can_capture(dama,enemy(turn)) && !player_can_move(dama,enemy(turn))){
        print (*dama, rows, cols);
        printf("Total moves = %d\n", moves);
        return turn+1;
    }
    else{
        return 0;
    }
}

void add_at_the_end(point_list *l, point p){
    point_cell * temporary;
    point_cell * i;

    temporary = (point_cell *) malloc (sizeof(point_cell));
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

point_list * avaiable_choices(tgame *dama, int rows, int cols, int turn){
    int i = 0, j = 0;
    point_list * l;

    l = create_choices_list();

    if(player_can_capture(dama, turn)){
        for (i=0; i<rows; i++){
            for(j=0; j<cols; j++){
                point p;
                p.i = i;
                p.j = j;

                if(turn ==1 && dama->mat[i][j]->id == turn+2 && black_capture_check(dama, p, turn)){
                    add_at_the_end(l, p);
                }
                else if (turn ==0 && dama->mat[i][j]->id == turn+2 && white_capture_check(dama, p, turn)){
                    add_at_the_end(l, p);
                }
                if(dama->mat[i][j]->id == turn+4 && dama_capture_check(dama, p, turn)){
                    add_at_the_end(l, p);
                }
            }
        }
    }
    else{
        for(i=0; i<rows; i++){
            for(j=0; j<cols; j++){
                point p;
                p.i = i;
                p.j = j;

                if(turn == 1 && dama->mat[i][j]->id == turn+2 && black_move_check(dama, p)){
                    add_at_the_end(l, p);
                }
                else if(turn == 0 && dama->mat[i][j]->id == turn+2 && white_move_check(dama, p)){
                    add_at_the_end(l, p);
                }
                if(dama->mat[i][j]->id == turn+4 && dama_move_check(dama, p)){
                    add_at_the_end(l, p);
                }
            }
        }
    }
    return l;
}

void computer_moves(tgame *dama, int rows, int cols, int turn){
    int flag = 0, i = 0 , j = 0, size=0, pos=0;
    point_list * l;
    point_cell * point_a ;
    point_cell * pos_point_a;
    point b;

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

void error(tgame *dama, int rows, int cols,int turn, int code_error){
    point_list * l;
    point_cell * point_a;

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
        printf("The Dama (promoted pawn) may capture only in the 4 diagonals if the adjacet is a foe's pawn and the next on the diagonal is free.\n");
    }else if(code_error ==3){
        printf("The pawn may capture only in the 2 diagonals forward if the adjacet is a foe's pawn and the next on the diagonal is free.\n");
    }else if(code_error ==4){
        printf("The Dama (promoted pawn) may move only in the 4 diagonals if it's free.\n");
    }else if(code_error ==5){
        printf("The pawn may move only in the 2 diagonals forward if it's free.\n");
    }else if(code_error ==6){
        printf("You can move only into free white empty bowes\n");
    }else if(code_error == 7){
        printf("The selected box have to contain your pawn\n");
    }else if(code_error == 10){
        printf("The pawn you choosed can not be moved\n");
    }else if(code_error == 11){
        printf("Unfortunately, you can't choose this pawn because you are forced to capture foe's pawns, so you have to choose an other pawn.\nYou can move only the pawn inside one of this boxes:\n");
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

int game(tgame *dama, int rows, int cols, int play_mode){
    point a,b;
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
            print (*dama, rows, cols);
            computer_moves(dama,dama->rows,dama->cols, turn);
            moves++;

            if(victory(dama, rows, cols, turn, moves)){   
                int winner;

                winner = victory(dama, rows, cols, turn, moves);                                  
                return --(winner);
            }

            turn = enemy(turn);
        }
    }

    return 10;
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

    return n;
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

    printf(" __       __            __                                                      __               \n"
           "|  \\  _  |  \\          |  \\                                                    |  \\              \n"
           "| $$ / \\ | $$  ______  | $$  _______   ______   ______ ____    ______         _| $$_     ______  \n"
           "| $$/  $\\| $$ /      \\ | $$ /       \\ /      \\ |      \\    \\  /      \\       |   $$ \\   /      \\ \n"
           "| $$  $$$\\ $$|  $$$$$$\\| $$|  $$$$$$$|  $$$$$$\\| $$$$$$\\$$$$\\|  $$$$$$\\       \\$$$$$$  |  $$$$$$\\\n"
           "| $$ $$\\$$\\$$| $$    $$| $$| $$      | $$  | $$| $$ | $$ | $$| $$    $$        | $$ __ | $$  | $$\n"
           "| $$$$  \\$$$$| $$$$$$$$| $$| $$_____ | $$__/ $$| $$ | $$ | $$| $$$$$$$$        | $$|  \\| $$__/ $$\n"
           "| $$$    \\$$$ \\$$     \\| $$ \\$$     \\ \\$$    $$| $$ | $$ | $$ \\$$     \\         \\$$  $$ \\$$    $$\n"
           " \\$$      \\$$  \\$$$$$$$ \\$$  \\$$$$$$$  \\$$$$$$  \\$$  \\$$  \\$$  \\$$$$$$$          \\$$$$   \\$$$$$$ \n"
           "                                                                                                 \n"
           "                                                                                                 \n"
           "                                                                                                 \n"
           " __                           __                        ______    ______   ________  ________    \n"
           "|  \\                         |  \\                      /      \\  /      \\ |        \\|        \\   \n"
           "| $$       ______    _______ | $$   __  ______        |  $$$$$$\\|  $$$$$$\\ \\$$$$$$$$ \\$$$$$$$$   \n"
           "| $$      |      \\  /       \\| $$  /  \\|      \\        \\$$__| $$| $$$\\| $$    /  $$     /  $$    \n"
           "| $$       \\$$$$$$\\|  $$$$$$$| $$_/  $$ \\$$$$$$\\       /      $$| $$$$\\ $$   /  $$     /  $$     \n"
           "| $$      /      $$ \\$$    \\ | $$   $$ /      $$      |  $$$$$$ | $$\\$$\\$$  /  $$     /  $$      \n"
           "| $$_____|  $$$$$$$ _\\$$$$$$\\| $$$$$$\\|  $$$$$$$      | $$_____ | $$_\\$$$$ /  $$     /  $$       \n"
           "| $$     \\\\$$    $$|       $$| $$  \\$$\\\\$$    $$      | $$     \\ \\$$  \\$$$|  $$     |  $$        \n"
           " \\$$$$$$$$ \\$$$$$$$ \\$$$$$$$  \\$$   \\$$ \\$$$$$$$       \\$$$$$$$$  \\$$$$$$  \\$$       \\$$         \n");
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
    printf("KKKKKKKKKKKXXKKKKKKK00OOOkkkO00Odl;'...'','.....'......,,,'....:lc;;;;ldx0KXKKKK000000OOOOkkkkkxxxxx\n"
           "KKKKKKKKKKKKKKKKKKK00OOkkkkkxo;.............';::::::::;;;::,...'....','..,:loxOOkkkxxdddooooollllccc\n"
           "KKKKKKKKKKKK00000000OOOkOkd:.   ...........',,'..........,:;,...    .  ......':lolcc::cccccllllccc::\n"
           "KKK00000000000OOOOOOOOOkx:.   .......                      .'...             ...,:::::clloooooooooll\n"
           "0000000000OOOOOOOOOOOkxl'     .               ...''',,,'..........               .,cllloodddxxxxxddd\n"
           "00000000000OOOOOOOOOkxc.                  ...':ldxkkxxxxdddddol:'.......           'cddddxxxxkkkkxxx\n"
           "00000000OOOOOOOOkkkkx:.       .....      .,:odk0KKXXKKKXXXXXKKK0kdc:coxdc'.         .lxxxxxkkkkkkkkk\n"
           "OOOOOOOOOkkkkkkkkkkd;.      ..   .     .':dk0KKXXXNNNNNNNNNNNNNNXK0OO0KXKkl'         'oxkkkkkkkkkkkk\n"
           "kkkkkxxxxxxxxxxxxxo;.                 .,lxO0KXXXNNNNNNNNNNNNNNNNNNNNNNNNXX0x;.       .cdkkkkkkkkkkkk\n"
           "ddddoooooooooddddc:,.              ...;oxO00KXXXXXXXNNNNNXNNNNNNNNNNNNNNXXK0k:        ,okOkkkkkkkkkk\n"
           "lccc::::ccllooddc::.                .,lxO0KKKKXXXXXXXXXXKKKKXXXXXXXXXXXXXKKK0d'       .:xOOOOOOkkkkk\n"
           ";;;;::cclloddxxl:c.                .';ldk0KKK0KKKKKKKK00000KK000KKKKKKKKKKK0OOl.      .,oOOOOOOkkkkk\n"
           "cccclloooddxxkd;,,.                .':lxkO00000KKKK000000OOOOOOOOO000000000OOOd'     .'':kkkkkkkkkkk\n"
           "ooddddddxxxkkxc,'.                 .,coxkO00000KKKKK00000OOOOkOOOOOOkOOOOOkOkkx;     .,',okxkxxxxxxk\n"
           "xkkkkkkkkkkkxo;..                 ..:odkOO000KKKKKKKKKKK0000000OOOOkkOOOOkkkOOk;     .,;,:xxxxxxxxxx\n"
           "OOOOOOOOOkkkoc,..                .'cdkOO0000KKXXXXXXXXXXXKKKKKK00OOO0000OO0OOkx;      ,:',dxdxxxxxxk\n"
           "KKOkO0KKK00kl;'.                .,lxO0KKKKKKKKKK00000KKKKK000000000KKXXKKKK00Ox,      ';.'lddddddxxx\n"
           "00kxk000000kl..                .;okO0KXXXK0Okxdlcc::;:clodxxxxxkkOOOOO000KKKK0x.      .'..:ccclllooo\n"
           "loooxkOOkkko,                 .,lkO0KKKKK0kdolllc::;;,''''';:clodxxxxdxkOOOO00x'      .....''',,;;;;\n"
           "',;:ldxkkkd;.                 .:dO00KKK0Okdlc:;,'.....''''',,;cdxxdoc:::;;;;::c.          ..........\n"
           ".',;:cllodl.             ...  'cxO00KKKKK0Okxdoooc:;,:c;.',,;cdkOko;......',;;,.          .         \n"
           ",,,,,,;;;c,              .....;ldkO0KKKXKKKKK0OOxdddoolc:cccldOKK0l...  ...';c,        . ..         \n"
           ":cc:,',,,,.           .......,;ldxO00KKKXXXKKKK0Okxxxdooodxxk0KXNXk:;:::cl:,;c'        ....         \n"
           "dxkxo:,','.           ..',,,,,:ldkkkOOO0KKKXXKKK000000OOO000KKXXNNKdcclloddddo,        .......      \n"
           "OOkkxl:,:;.            .,;;:;:lodxkkOkkO000KKKKKKKKKKKKKKKKKKKXXNNXOddxdxxkkxd'        . ..... .    \n"
           "00Okkxocc:.              ':::cooldkkkkxkkOO00KKKKKKXXXK0OOO000KXNNX0OOOOOOOkko.        ..........   \n"
           "KKK00OOxl;.              .:cloloooxkkxxxxxkOO00000K00OkdxOKXKKKXNXXKOO000Okxx:.        ......... .  \n"
           "XXXXKK0kl.               .cddllddlllllodddxkkkkOOOkkxdllkXXNNNXXXXX0xdkOOOkxc.         .............\n"
           "XXXXKKOl'..        ..    .cddloxxl:;'',;ccldxkkkkxxdodddddooddxO0OOkxooxkkxc.         ..............\n"
           "O00O0k:...         ...   .cdolloo:''....',;ldkkkxxdxkOOko:'...,cllcllcldxxc.          .,,'''''......\n"
           "dxdol,..  .        ...   .;oxdc;;,........;odxxxxkOOOOOkdc,.......;do:lddc.          .:c,''''''''...\n"
           ",,,'.    ..         ..    .:ddl;,'.....  .;dxxxxdooolll:,''........:llll;.           .;:'''''',,,'''\n"
           "....    ...               .'cllc;,'''.   .;dOkd:,'...','............'cl,             .'''''',,,,,,;;\n"
           "'.. ......                 .;clll:,'..  .,lxkd;......................;,              .''',,,,,;;;;::\n"
           ",;'.',,..                   .;cll:;,.....,col;..,;:::;;,,,,,',,,,.  .,.             .',;;;;;;;:::ccc\n"
           ",..'...                      .,::,'..,,...,;;',coodxdloooolllllll,..'.              .;::::::::ccclll\n"
           ". ..                          .'''..':l;'',,'':ldxxdolll::c:;:cll;...             ..'clllcccccccllll\n"
           ":,'..         ....             ..'..',;'...'',:lxOOkxol:;,,:;,;:;'.              .',cllooollccclllll\n"
           "kdc::;,.   ........              ........ ...';lxO00Oxoc;,'';cc:'.              .,,;cllooollcclllllo\n"
           "clollc'. ............                      ...':loodxdl:,',,,;:'.              .''',clooooollllllloo\n"
           "...''''......''.......                       .',;;;;;;;:;..,'''.               .'',:loooooollllloooo\n"
           ".',;;cc;,...'''''.......                     ..... ....',......                .:llooooooooolllooooo\n"
           "cllccllc:;'....''...........                    .       ..       .,;;..,;.    ..cooooooodooolllooooo\n"
           "ddoooodolc:;,'................     .                        .;c;',cc;:lk0x;...',cododdooddoolloooood\n"
           "xxxdddddolcc:;'................     .                    'lodO00kdol:;cx0KOo::clllodxxddddoooloooodd\n"
           "xxxxxxdollllc:,'................                    ...  ,0X00O000OkolloxOOOkdxdlcldxdddddoooooodddd\n"
           "kxxxxdooooolcc:;,'...............                        .dOO0OOOkdl:;'.';lolc::;:ldxxxddddooooddddd\n"
           "xxxdooooooollc::;,'..............                         .';cll:,..      ...   .'cdxxxddddooddddddd\n"
           "xxdoodddooollcc:;;,'...............                                              .cdxxxddddddddddddd\n"
           "xoodddddoolllcc:;;,,'...............      ...        .         ..                .:xkkxxxddddddddddx");
    printf("\n");
    printf("\n");
    printf("Keanu says goodbye!");
    printf("\n");
    printf("\n");

}

void credits(){
    printf("\n");
    printf("\n");
    printf("Credits to: Gianmaria & Aleksandra");
    printf("\n");
}

