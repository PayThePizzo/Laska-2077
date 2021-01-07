#include "laska.h"

/*
legend id
0-> white box
1-> black box
2-> white pawn
3-> black pawn
4-> white dama
5-> black dama
*/

tgame* create(int cols,int rows){
    tgame *dama;
    int i, j;

/*allocates space to struct*/
    dama=(tgame*)malloc(sizeof(tgame));
    assert(dama!=NULL);
/*save dimensions*/
    dama->rows=rows;
    dama->cols=cols;
/* allocate vector rows pointers */
    dama->mat=(boxpawn***)malloc(sizeof(boxpawn**)*rows);
    assert(dama->mat!=NULL);
/*allocate pawns pointers and boxes*/
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

void initialize(tgame * dama, int cols, int rows){
    int i, j;
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
    int i , j;

    for(i = 0; i<rows; i++){
        for (j=0; j<cols; j++){
            if(dama->mat[i][j]->next==NULL)
                free(dama->mat[i][j]);
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

int convert(int dim){
    char a;
    int i = 0;
    while (1){
        scanf(" %c",&a);
        if(a>='A' && a<=('A'+dim-1))
            return a-65;
        else if(a>='a' && a<=('a'+dim-1))
            return a-97;
        else{
            printf("The selected box doesn't exist. Please select a letter from %c to %c\n", 65, 65+dim-1);
        }
    }
}

int check_number(int dim){
    char i;
    while (1){
        scanf(" %c",&i);
        if(i>='1' && i<='1'+dim)
            return ((int) i-'0');
        else {
            printf("The selected box doesn't exist. Please select a number from %d to %d\n", 1, dim);
        }
    }
}

void print(tgame dama, int rows , int cols){
    int i , j, z;
    int empty=0;
    boxpawn **t;
    printf("%43s","LASKA GAME\n");
    printf("\t");
    for (int i = 0; i < rows; ++i) {
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

void top_print(tgame dama, int rows , int cols){
    int i , j, z;
    printf("%43s","LASKA GAME\n");
    printf("\t");
    for (int i = 0; i < rows; ++i) {
        printf("    %c\t",65+i);
    }
    printf("\n        _________________________________________________________\n");;
    for (i = 0; i < rows; ++i) {
        printf("      %d\t",i+1);
        for (j = 0; j <cols; ++j) {    
                if(dama.mat[i][j]->id==0){
                    printf("%c%c%c%c%c%c",219,219,219,219,219,219);
                }else if(dama.mat[i][j]->id==2){
                    printf("   %c ",'w');
                }else if(dama.mat[i][j]->id==3){
                    printf("   %c ",'b');
                }else if(dama.mat[i][j]->id==4){
                    printf("   %c ",'W');
                }else if(dama.mat[i][j]->id==5){
                    printf("   %c ",'B');
                }
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

int remove_pawn(tgame *dama, int r, int c){
    int estract;

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

int white_move_check(tgame *dama, point a){
    if(a.i == 0)
        return 0;
    else if (a.j==0){
        if(dama->mat[a.i-1][a.j+1]->id == 0)
            return 1;
        else
            return 0;
    }
    else if(a.j==dama->cols-1){
        if (dama->mat[a.i-1][a.j-1]->id == 0)
            return 1;
        else
            return 0;
    }
    else{
        if(dama->mat[a.i-1][a.j+1]->id == 0 || dama->mat[a.i-1][a.j-1]->id == 0)
            return 1;
        else
            return 0;
    }
}

int black_move_check(tgame *dama, point a){
    if(a.i == dama->rows-1)
        return 0;
    else if (a.j==0){
        if(dama->mat[a.i+1][a.j+1]->id == 0)
            return 1;
        else
            return 0;
    }
    else if(a.j==dama->cols-1){
        if (dama->mat[a.i+1][a.j-1]->id == 0)
            return 1;
        else
            return 0;
    }
    else{
        if(dama->mat[a.i+1][a.j+1]->id == 0 || dama->mat[a.i+1][a.j-1]->id == 0)
            return 1;
        else
            return 0;
    }
}

int dama_move_check(tgame *dama, point a){
    return (white_move_check(dama, a) || black_move_check(dama, a));
}

int white_capture_check(tgame *dama, point a, int turn){
    int e = enemy(turn);
    if(a.i<2)
        return 0;
    else if(a.j==0 || a.j==1){
        if((dama->mat[a.i-1][a.j+1]->id == e+2 || dama->mat[a.i-1][a.j+1]->id == e+4) && dama->mat[a.i-2][a.j+2]->id == 0)
            return 1;
        else
            return 0;
    }
    else if (a.j==dama->cols-1 || a.j==dama->cols-2){
        if((dama->mat[a.i-1][a.j-1]->id == e+2 || dama->mat[a.i-1][a.j-1]->id == e+4) && dama->mat[a.i-2][a.j-2]->id == 0)
            return 1;
        else
            return 0;
    }
    else{
        if(((dama->mat[a.i-1][a.j+1]->id == e+2 || dama->mat[a.i-1][a.j+1]->id == e+4) && dama->mat[a.i-2][a.j+2]->id == 0)||
           ((dama->mat[a.i-1][a.j-1]->id == e+2 || dama->mat[a.i-1][a.j-1]->id == e+4) && dama->mat[a.i-2][a.j-2]->id == 0))
            return 1;
        else
            return 0;
    }
}

int black_capture_check(tgame *dama, point a, int turn){
    int e = enemy(turn);
    if(a.i > (dama->rows-3))
        return 0;
    else if(a.j==0 || a.j==1){
        if((dama->mat[a.i+1][a.j+1]->id == e+2 || dama->mat[a.i+1][a.j+1]->id == e+4) && dama->mat[a.i+2][a.j+2]->id == 0)
            return 1;
        else
            return 0;
    }
    else if (a.j==dama->cols-1 || a.j==dama->cols-2){
        if((dama->mat[a.i+1][a.j-1]->id == e+2 || dama->mat[a.i+1][a.j-1]->id == e+4) && dama->mat[a.i+2][a.j-2]->id == 0)
            return 1;
        else
            return 0;
    }
    else{
        if(((dama->mat[a.i+1][a.j+1]->id == e+2 || dama->mat[a.i+1][a.j+1]->id == e+4) && dama->mat[a.i+2][a.j+2]->id == 0)||
           ((dama->mat[a.i+1][a.j-1]->id == e+2 || dama->mat[a.i+1][a.j-1]->id == e+4) && dama->mat[a.i+2][a.j-2]->id == 0))
            return 1;
        else
            return 0;
    }
}

int dama_capture_check(tgame *dama, point a, int turn){
    return white_capture_check(dama, a, turn) || black_capture_check(dama, a, turn);
}

int player_can_capture(tgame *dama, int turn){
    int i, j;
    int flag = 0;

    for (i=0; i<dama->rows && flag == 0; i++){
        for(j=0; j<dama->cols && flag == 0; j++){
            point p;
            p.i = i;
            p.j = j;
            if(dama->mat[i][j]->id == turn+2 ){
                if(turn==0 && white_capture_check(dama, p, turn))
                    flag = 1;
                else if(turn==1 && black_capture_check(dama, p, turn))
                    flag = 1;
            }
            else if(dama->mat[i][j]->id == turn+4 ){
                if(dama_capture_check(dama, p, turn))
                    flag = 1;
            }
        }
    }
    return flag;
}

int player_can_move(tgame *dama, int turn){
    int i, j;
    int flag = 0;

    for (i=0; i<dama->rows && flag == 0; i++){
        for(j=0; j<dama->cols && flag == 0; j++){
            point p;
            p.i = i;
            p.j = j;
            if(dama->mat[i][j]->id == turn+2 ){
                if(turn==0 && white_move_check(dama, p))
                    flag = 1;
                else if(turn==1 && black_move_check(dama, p))
                    flag = 1;
            }
            else if(dama->mat[i][j]->id == turn+4 ){
                if(dama_move_check(dama, p))
                    flag = 1;
            }
        }
    }
    return flag;
}

int legal_choice(tgame *dama, int turn, point a){
    if(dama->mat[a.i][a.j]->id== turn+2 || dama->mat[a.i][a.j]->id== turn+4){
        if (player_can_capture(dama,turn)){
            if(is_promoted (dama,a,turn)){
                if (dama_capture_check(dama, a, turn))
                    return 1;
                else
                    return 4;
            }
            else{
                if(turn == 0){
                    if(white_capture_check(dama, a, turn))
                        return 1;
                    else
                        return 4;
                }
                else{
                    if(black_capture_check(dama, a, turn))
                        return 1;
                    else
                        return 4;
                }
            }
        }
        else if(is_promoted (dama,a,turn)){
            if(dama_move_check(dama, a))
                return 2;
            else
                return 3;
        }
        else{
            if (turn == 0 && white_move_check(dama, a))
                return 2;
            else if (turn == 1 && black_move_check(dama, a))
                return 2;
            else{
                return 3;
            }
        }
    }
    else{
        return 0;
    }
}

int illegal_move (tgame *dama, int turn, point a, point b, int have_to_capture){
    if(dama->mat[b.i][b.j]->id == 0){
        if(have_to_capture == 1){
            point p = findmiddle(a, b);
            if(dama->mat[p.i][p.j]->id == enemy(turn)+2 || dama->mat[p.i][p.j]->id == enemy(turn)+4){
                if(is_promoted (dama,a,turn)){
                    if ( abs(b.i - a.i)==2)
                        return 0;
                    else
                        return 2;
                }
                else if(turn == 0){
                    if(a.i == (b.i)+2 && (a.j == (b.j)+2 || a.j == (b.j)-2))
                        return 0;
                    else
                        return 3;
                }
                else if(turn == 1){
                    if (a.i == b.i-2 && (a.j == b.j+2 || a.j == b.j-2))
                        return 0;
                    else
                        return 3;
                }
            }
            else{
                return 1;
            }
        }
        else if(is_promoted (dama,a,turn)){
            if(abs(b.i - a.i)==1)
                return 0;
            else
                return 4;
        }
        else if (turn == 0 && (((b.i==(a.i)-1)&& (b.j==(a.j)-1)) || ((b.i==(a.i)-1)&& (b.j==(a.j)+1)))){
            return 0;
        }
        else if (turn == 1 && (((b.i==(a.i)+1)&& (b.j==(a.j)-1)) || ((b.i==(a.i)+1)&& (b.j==(a.j)+1)))){
            return 0;
        }
        else{
            return 5;
        }
    }
    else{
        return 6;
    }
}

point findmiddle(point a, point b){
    point middle;
    middle.i = 0;
    middle.j = 0;

    if(a.i>b.i){
        if(a.j>b.j){
            middle.j = a.j-1;
            middle.i = a.i-1;
        }
        else{
            middle.j = a.j+1;
            middle.i = a.i-1;
        }
    }
    else{
        if(a.j>b.j){
            middle.j = a.j-1;
            middle.i = a.i+1;
        }
        else{
            middle.j = a.j+1;
            middle.i = a.i+1;
        }
    }
    return middle;
}

void move (tgame *dama, point a, point b){
    if (abs(b.j - a.j)==1){
        boxpawn * temporary = dama->mat[b.i][b.j];
        dama->mat[b.i][b.j]= dama->mat[a.i][a.j];
        dama->mat[a.i][a.j]= temporary;
    }
    else if(abs(b.i - a.i)==2){
        int conquered;
        boxpawn * temporary = dama->mat[b.i][b.j];
        point middle = findmiddle( a, b);

        conquered = remove_pawn(dama, middle.i, middle.j);
        add(dama, conquered, a.i, a.j);
        dama->mat[b.i][b.j] = dama->mat[a.i][a.j];
        dama->mat[a.i][a.j]= temporary;
    }
    else {
        printf("Error move function");
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
    int i, j;
    turn == 0? i=0 : (i=((dama->rows)-1));

    for (j=0; j<dama->cols; j++){
        if (dama->mat[i][j]->id == turn+2)
            dama->mat[i][j]->id +=2;
    }
}

/*returns 0 if no winner, 1 if white player is the winner, 2 if vlack player is the winner*/
int victory(tgame *dama, int turn){
    if(!player_can_capture(dama,enemy(turn)) && !player_can_move(dama,enemy(turn)))
        return turn+1;
    else{
        return 0;
    }
}

int game(tgame *dama, int rows, int cols, int print_version){
    point a,b;
    int turn = 0;
    int code_error;
    int endgame = 0;
    int moves =0;

    while(!endgame){
        do{
            if(print_version==0)
                print (*dama, rows, cols);
            else
                top_print(*dama, rows, cols);
            if(turn ==0)
                printf("\nIt's white turn\n\n");
            else
                printf("\nIt's black turn\n\n");
            printf("Write the start and the destination coordinate without spaces, for example a5b4\n");
            a.j = convert(dama->cols);
            a.i = check_number(dama->cols);
            (a.i) --;
            code_error = legal_choice(dama, turn, a);
            b.j = convert(dama->rows);
            b.i = check_number(dama->rows);
            (b.i) --;
            if (code_error!=7&&code_error!=10&&code_error!=11)
                code_error= (illegal_move (dama, turn, a, b, legal_choice(dama, turn, a)));
            if(code_error){
                printf("Laska-Bot Says:\n");
                if (code_error ==1)
                    printf("FORCING CAPTURE - Pieces must capture if in a position to do so.\n");
                else if(code_error ==2)
                    printf("The Dama (promoted pawn) may capture only in the 4 diagonals if the adjacet is a foe's pawn and the next on the diagonal is free.\n");
                else if(code_error ==3)
                    printf("The pawn may capture only in the 2 diagonals forward if the adjacet is a foe's pawn and the next on the diagonal is free.\n");
                else if(code_error ==4)
                    printf("The Dama (promoted pawn) may move only in the 4 diagonals if it's free.\n");
                else if(code_error ==5)
                    printf("The pawn may move only in the 2 diagonals forward if it's free.\n");
                else if(code_error ==6)
                    printf("You can move only into free white empty bowes\n");
                else if(code_error == 7)
                    printf("The selected box have to contain your pawn\n");
                else if(code_error == 10)
                    printf("The pawn you choosed can not be moved\n");
                else if(code_error == 11)
                    printf("Unfortunately, you can't choose this pawn because you care forced to capture foe's pawns, so you have to choose an other pawn.\n");
            }
        } while (code_error);  

        move(dama, a, b);
        moves++;
        promotion(dama, turn);
        if(victory(dama, turn)){
            endgame=1;                                          
            if(print_version==0)
                print (*dama, rows, cols);
            else
                top_print(*dama, rows, cols);
            printf("total moves = %d\n", moves);
            return turn;
        }
        turn = enemy(turn);
    }
    return 10;
}

//Menu

int main_menu(){
    int input = -1;
    int cond= 1;
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
    printf("You can Quit or Give Up at any time by typing 'x', unless two PCs are playing.\n");
    printf("Yeah, you do not want to see them angry... They really love the game\n");
    printf("\n");
    printf("Let's hear it then, have you made up your mind? Type the code of the game to play");
    printf("\n");
    printf("\n");

    do{
        scanf("%d", &input);
        if(input >= 0 && input <= 3){
            cond = 0;
        } else{
            printf("Yoda says: Bugs here, you won't find. Again you must try.\n");
            printf("\n");
        }
    }while(cond);

    switch (input) {
        case 0:
            printf("You chose: Single Player");
            printf("\n");
            printf("Man, if I were you, I'd make some new friends...");
            printf("\n");
            printf("\n");
            return input;
        case 1:
            printf("You chose: Player vs Player");
            printf("\n");
            printf("Finally, you got some friends to play with!");
            printf("\n");
            printf("\n");
            return input;
        case 2:
            printf("You chose: Player vs Pc");
            printf("\n");
            printf("I'm impressed you managed to lose your friends that fast, you really are a disaster at social life");
            printf("\n");
            printf("\n");
            return input;
        case 3:
            printf("You chose: Pc vs Pc");
            printf("\n");
            printf("I know you might not care, but watching two computers play against each other... is pretty lame");
            printf("\n");
            printf("\n");
            return input;
        default:
            printf("You chose to be a funny guy, but I can't take a joke, sorry");
            printf("Error in main_menu");
            EXIT_FAILURE;
    }
}

int decision_menu() {
    int winner = 0, cond = 1;
    char decision;

    printf("Are you ready to play?(Y/N)\n");

    while (cond){
        scanf("%c", &decision);

        if (decision == 'Y' || decision == 'y') {
            printf("Very Well, let's go on\n");
            printf("\n");
            return 1;

        } else if (decision == 'N' || decision == 'n') {
            printf("I guess you might not be ready to play this wonderful game\n");
            printf("Farewell!\n");
            return 0;

        }
    }
}

void result_menu(int winner){
    if(winner == 0){
        printf("\n");
        printf("White gamer is the winner!");
        printf("\n");
    }else if (winner == 1) {
        printf("\n");
        printf("Black player is the winner!");
        printf("\n");
    } else{
        printf("No Pain, No Gain.");
        printf("\n");
    }
}



//Messages

void hello(){
    int answer = 1;
    char decision = 'a';

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
           " \\$$$$$$$$ \\$$$$$$$ \\$$$$$$$  \\$$   \\$$ \\$$$$$$$       \\$$$$$$$$  \\$$$$$$  \\$$       \\$$         \n"
           "                                                                                                 ");
    printf("\n");
    printf("\n");
    printf("Hi there, welcome to Laska 2077!\n");
    printf("Check out the official site of the game here: http://www.lasca.org/ \n");
    printf("\n");
    printf("Now, let's welcome Lask-Bot from the year 2077. It will give you a brief insight of the game.");
    printf("\n");
    printf("\n");
    printf("Laska-Bot says: Here I am fellow player, would you like me to explain the game to you?(Y/N)\n");
    printf("\n");

    while (answer){
        scanf("%c", &decision);
        if (decision == 'Y' || decision == 'y') {
            printf("Awesome\n");
            printf("\n");
            printf(" - - - - - The Equipment - - - - -\n");
            printf(" - Why is it 7x7?\n");
            printf(" - - - - - The Pawns - - - - -\n");
            printf(" - Who moves first?\n");
            printf(" - - - - - The Moves - - - - -\n");
            printf(" - How to move a pawn\n");
            printf(" - The Capture\n");
            printf(" - Forcing Capture\n");
            printf(" - - - - - The Promotion - - - - -\n");
            printf(" - - - - - Extra Rules for THIS GAME ONLY - - - - -\n");
            printf(" - - - - - The End of the Game - - - - -\n");

            printf("\n");
            answer = 0;

        } else if (decision == 'N' || decision == 'n') {
            printf("You sure are an expert then. I'll keep an eye on you, anyway.\n");
            printf("Don't make any silly mistake!\n");
            printf("\n");
            answer = 0;
        } else {
            printf("Bro, can you even read? You can only type either 'Y' or 'N'\n");
        }
    }
}

void goodbye(){
    printf("\n");
    printf("The game ends here...for now");
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
    printf("Keanu says goodbye!");
    printf("\n");
    printf("\n");

}

void credits(){
    printf("\n");
    printf("Credits to: Gianmaria & Aleskandra");
    printf("\n");
}

