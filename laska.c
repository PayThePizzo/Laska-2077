#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
/*
leggenda id
0-> cella bianca
1-> cella nera
2-> pedina bianca
3-> pedina nera
4-> pedina bianca promossa
5-> pedina nera promossa
*/
enum ide {white_empty_box, black_box, white_pawn, black_pawn, w_dama_pawn, b_dama_pawn};
typedef enum ide t_ide;

typedef struct point{                   /*coordinate scacchiera */
    int x, y;
} point;

typedef struct boxpawn {                /*se la cella è vuota rappresenta il colore, sennè rappresenta la pedina (ovviamente la cella è bianca)*/
    int id;
    struct boxpawn *next;
} boxpawn;

typedef struct dama{                    /*scacchiera*/
    int cols;
    int rows;
    boxpawn ***mat;
} tgame;

tgame* create(int cols,int rows);
void official_print(tgame result, int rows , int cols);
void private_print(tgame result, int rows , int cols);
void freegame(tgame *result, int rows, int cols);
int convert();
void add(tgame *dama, t_ide pedina, int r, int c);
int remove_pawn(tgame *dama, int r, int c);
point findmiddle(point a, point b);
void move (tgame *dama, point a, point b);
int game(tgame *dama, int rows, int cols);
int legal_move (tgame *dama, point a, point b);

int main() {
    tgame *dama;
    point a,b;
    dama=create(7,7);
    int winner;
    winner = game (dama, dama->rows, dama->cols);

    if(winner==0){
        printf("White gamer is the winner!!!");
    }else {
        printf("Black player is the winner!!!");
    }
    printf("\n");
    
    freegame(dama,dama->rows,dama->cols);
    return 0;
}

int game(tgame *dama, int rows, int cols){
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
            a.x=convert();
            if(a.x == -1)
                return (turn == 0 ? 1 : 0);
            else{
                printf("Number:");
                scanf("%d",&a.y);
                --(a.y);
                /* è una mia pedina?*/
                if(dama->mat[a.y][a.x]->id== turn+2 || dama->mat[a.y][a.x]->id== turn+4){
                    do
                    {
                    printf("Write the destination coordinate\n");
                    printf("Letter:");
                    b.x=convert();
                    printf("Number:");
                    scanf("%d",&b.y);
                    --(b.y);
                    } while (!legal_move (dama, a, b));

                    move(dama, a, b);
                    /*private_print (*dama,dama->rows,dama->cols);  magari solo all'ultima mossa */
                    /* if vittoria (...) return 0/1 */
        
                    if(turn == 0)
                        turn = 1;
                    else
                        turn = 0;;
            }
            else {
                printf("Please select your pawn\n");
            }
        }
        }
}

int legal_move (tgame *dama, point a, point b){
    return 1;                                                 /* da implementare */
}
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
