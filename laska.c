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

typedef struct point{
    int x, y;
} point;

typedef struct pawn {
    int id;
    struct pawn *next;
} tpawn;

typedef struct dama{
    int cols;
    int rows;
    tpawn ***mat;
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

int main() {
    tgame *dama;
    point a,b;
    dama=create(7,7);
    private_print(*dama,dama->rows,dama->cols);
    add (dama, 2, 0, 0);
    remove_pawn(dama, 0, 0);
    printf("Write the start coordinate\n or Press x to give up\n");
    printf("X:");
    a.x=convert();
    if(a.y == -1)
        exit (1);
    printf("Y:");
    scanf("%d",&a.y);
    --(a.y);
    printf("Write the destination coordinate\n");
    printf("Y:");
    b.y=convert();
    printf("X:");
    scanf("%d",&b.x);
    --(b.x);
    /* if legal move .. */
    move(dama, a, b);
    private_print(*dama,dama->rows,dama->cols);
    printf("\n");
    
    freegame(dama,dama->rows,dama->cols);
    return 0;
}

tgame* create(int cols,int rows){
    tgame *result;
    int i, j;


    result=(tgame*)malloc(sizeof(tgame));
    assert(result!=NULL);

    result->rows=rows;
    result->cols=cols;

    result->mat=(tpawn***)malloc(sizeof(tpawn**)*rows);
    assert(result->mat!=NULL);

    for(i=0;i<rows;i++){
        result->mat[i]=(tpawn**)malloc(sizeof(tpawn*)*cols);
        assert(result->mat[i]!=NULL);
        for(j=0;j<cols;j++){
            result->mat[i][j]=(tpawn*)malloc(sizeof(tpawn));
            assert(result->mat[i][j]!=NULL);
            result->mat[i][j]->next=NULL;
        }
    }
    /*creazione scacchiera*/
    for(i = 0;i<rows;i++){
        for(j=0;j<cols;j++) {
            if (i % 2 == 0 && j % 2 == 0) {
                result->mat[i][j]->id = 0;
            } else if (i % 2 != 0 && j % 2 != 0) {
                result->mat[i][j]->id = 0;
            } else {
                result->mat[i][j]->id = 1;
            }
        }
    }
    /*posizionamento pedine*/
    for (i = 0; i <rows ; i++) {
        for (j = 0; j < cols; j++) {
            if (result->mat[i][j]->id == 0) {
                if (i > rows / 2 && i <= rows) {
                    result->mat[i][j]->id = 2;
                } else if (i >= 0 && i < rows / 2) {
                    result->mat[i][j]->id = 3;
                }
            }

        }
    }


    return result;
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
int convert(){
    char a;
    int i = 0;
    scanf("%c",&a);
    if(a>='A' && a<='G')
        return i=a-65;
    else if(a>='a' && a<='g')
        return i=a-97;
    else if (a=='x'||a=='X')
        return 0;
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
                printf("%c ",'W');
            }else if(result.mat[i][j]->id==3){
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
        }
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
    tpawn *n= (tpawn *) malloc(sizeof(tpawn));
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
       tpawn *element = dama->mat[r][c];
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
        tpawn * temporary = dama->mat[b.y][b.x];                    /*swap spostamento cella vuola*/
        dama->mat[b.y][b.x]= dama->mat[a.y][a.x];
        dama->mat[a.y][a.x]= temporary;
    }
    else if(abs(b.y - a.y)==2 && dama->mat[b.y][b.x]->id == 0){ /*spostamento con conquista*/
        int conquered;
        tpawn * temporary = dama->mat[b.y][b.x];  
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
