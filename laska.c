#include "laska.h"
#define ROWS (7)
#define COLS (7)
#define PAWN (11)

// Create, Free & Print - Dama
/*  1) Create
 *  2) Free
 *  3) Print
 */

dama_t* dama_create(int rows, int cols){
    int r = 0, c = 0;

    //allocation of Lasca Board
    dama_t* damap = (dama_t *) malloc (sizeof (dama_t) * rows * cols);
    assert (damap != NULL);
    dama_t *mem = damap;

    //initialization
    for(r = 0; r<rows; r++){
        for(c = 0; c<cols; c++) {
            if ((r==0 && c%2 ==0)||(r==1 && c%2 != 0)|| r==2 && c%2==0){
                mem[r * cols + c].type = black_pawn;
                mem[r * cols + c].height = 1;
                mem[r * cols + c].loc.i = r;
                mem[r * cols + c].loc.j = c;
            }else if(((r==4 && c%2 ==0)||(r==5 && c%2 != 0)|| r==6 && c%2==0)){
                mem[r * cols + c].type = white_pawn;
                mem[r * cols + c].height = 1;
                mem[r * cols + c].loc.i = r;
                mem[r * cols + c].loc.j = c;
            }else if(r==3 && c%2 !=0){
                mem[r * cols + c].type = empty;
                mem[r * cols + c].height = 0;
                mem[r * cols + c].loc.i = r;
                mem[r * cols + c].loc.j = c;
            }else{
                mem[r * cols + c].type = excluded;
                mem[r * cols + c].height = 0;
                mem[r * cols + c].loc.i = r;
                mem[r * cols + c].loc.j = c;
            }
        }
    }
    return damap;
}

void dama_free (dama_t *damap){
    free(damap);
}

void print(dama_t *dama, int rows, int cols){
    int r = 0, c = 0;
    printf("\t");
    printf(" ");
    for (int r = 0; r < rows; r++){
        printf("%c\t",65+r);

    }
    printf("\n");
    for (r = 0; r < rows; r++){
        printf("\n");
        printf("%d",r+1);
        printf("\t ");
        for (c = 0; c <cols; c++){
            if(dama[r * cols + c].type == white_pawn) {
                printf("%c\t", 'W');
            }
            if(dama[r * cols + c].type == black_pawn){
                printf("%c\t",'B');
            }
            if(dama[r * cols + c].type == empty) {
                printf("%c\t ", 223);
            }
            if(dama[r * cols + c].type == excluded) {
                printf("%c\t", ' ');
            }

        }
        printf("\n");
        printf("___________________________________________________________");
        printf("\n");

    }
}



//Vectors for Pawns
/* 1) Crea Vettore generico
 * 2) Libera Vettore
 * 3) Printa Vettore
 */


vet_t * create_vet(dama_t * dama, int rows, int cols, elem_t type, int dim){
    vet_t * newvet = (vet_t *) malloc (sizeof(vet_t)* dim);
    assert (newvet != NULL);
    vet_t * sup = newvet;

    int i = 0, j = 0, k = 0;
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            if(dama[i*cols+j].type == type){
                sup[k].vet = (dama_t *)malloc(sizeof(dama_t));
                assert(sup[k].vet);
                sup[k].vet->loc = dama[i*cols+j].loc;
                sup[k].vet->type = dama[i*cols+j].type;
                sup[k].vet->height = dama[i*cols+j].height;

                sup[k].status = free_to_move;
                sup[k].vet_dim = dim;
                sup[k].top = 1;
                k++;
            }
        }
    }
    return newvet;
}

void free_vet(vet_t * newvet, int dim, int pos){

    while(pos < dim){
        free(newvet[dim].vet);
        free_vet(newvet, dim, (pos+1));
    }
    free(newvet);
}

void print_vet(vet_t * newvet, int dim, int pos){
    while (pos < dim){
        vet_t * sup = newvet;
        printf("%d,", sup[pos].vet->loc.i);
        printf("%d", sup[pos].vet->loc.j);
        printf("\t");
        pos++;
    }
}



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

    scanf("%c",&a);

    if(a>='A' && a<='G') {
        return (a - 65);
    }else if(a>='a' && a<='g'){
        return (a-97);
    }else if (a=='x'||a=='X'){
        return -1;
    }else{
        convert();
    }
}

/*
point findmiddle(point a, point b){
    point middle;
    if(a.y>b.y){
        if(a.x>b.x){
            middle.x = a.x-1;
            middle.y = a.y-1;
        }
        else{
            middle.x = a.x+1;
            middle.y = a.y-1;
        }
    }
    else{
        if(a.x>b.x){
            middle.x = a.x-1;
            middle.y = a.y+1;
        }
        else{
            middle.x = a.x+1;
            middle.y = a.y+1;
        }
    }
    return middle;
}
*/



// Menu & Auxiliary Game Functions
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
            printf("You chose to be a funny guy, but I can't take a joke, sorry");
            printf("Error in main_menu");
            EXIT_FAILURE;
    }
}

int decision_menu(){
    int winner = 0;
    char decision = 'a';

    scanf("%c", &decision);
    if (decision == 'Y' || decision == 'y'){
        printf("Very Well, let's go on\n");
        printf("\n");

        switch(main_menu()){
            case 0:
                return (winner = 1); //SOSTITUISCI CON winner = game();
            case 1:
                return (winner = 0);
            case 2:
                return (winner = 2);
            case 3:
                return (winner = 3);
            default:
                printf("Error in Play or Not section of Main");
                EXIT_FAILURE;
        }
    } else if(decision == 'N' || decision == 'n'){
        printf("I guess you might not be ready to play this wonderful game\n");
        printf("Farewell!\n");
        return 0;
    } else{
        printf("Am I a joke to you?\n");
        EXIT_FAILURE;
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
        printf("Error in result_menu");
        EXIT_FAILURE;
    }
}



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
 *
 * Features
 * - Give Up
 * - Quit
 * - Reset the game
 * - Undo move
 * - Pass turn
 *
 */



// Messages

void hello(){
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
    printf("You can Quit or Give Up at any time, unless two PCs are playing.\n");
    printf("Yeah, you do not want to see them angry... They really love the game\n");
    printf("\n");
    printf("Let's hear it then, have you made up your mind?(Y/N)");
    printf("\n");
    printf("\n");
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



// Debug Dama

void debug_dama(){
    int dimvet = 11;

    dama_t * dama = dama_create(ROWS,COLS);

    print(dama, ROWS, COLS);
    printf("\n");

    vet_t * blackv = create_vet(dama, ROWS, COLS, black_pawn, dimvet);
    print_vet(blackv, dimvet, 0);
    free_vet(blackv,dimvet, 0);

    vet_t * whitev = create_vet(dama, ROWS, COLS, white_pawn, dimvet);
    print_vet(whitev, dimvet, 0);
    free_vet(whitev, dimvet, 0);

    dama_free(dama);
}