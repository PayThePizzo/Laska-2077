#include "laska.h"
#include <stdio.h>

int main() {
    /* Initialization */
    tgame *dama;
    point a,b;
    char decision = 'a';
    dama = create(7,7);
    int winner = 3;

    /*  Welcome Message */
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
    printf("\n");
    printf("Let's hear it then, have you made up your mind?(Y/N)");
    printf("\n");


    /* Play or Not */
    scanf("%c", &decision);
    if (decision == 'Y' || decision == 'y'){
        printf("Very Well, let's go on\n");
        printf("\n");
        main_menu();
        winner = game (dama, dama->rows, dama->cols);
    } else if(decision == 'N' || decision == 'n'){
        printf("I guess you might not be ready to play this wonderful game\n");
        printf("Farewell!\n");
        return 0;
    } else{
        printf("Am I a joke to you?\n");
        return 0;
    }

    /*Result Menu*/
    if(winner==0){
        printf("White gamer is the winner!!!");
    }else {
        printf("Black player is the winner!!!");
    }
    printf("\n");
    printf(" __    __            __                        __           \n"
           "|  \\  |  \\          |  \\                      |  \\          \n"
           "| $$\\ | $$  ______  | $$____    ______    ____| $$ __    __ \n"
           "| $$$\\| $$ /      \\ | $$    \\  /      \\  /      $$|  \\  |  \\\n"
           "| $$$$\\ $$|  $$$$$$\\| $$$$$$$\\|  $$$$$$\\|  $$$$$$$| $$  | $$\n"
           "| $$\\$$ $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$| $$  | $$\n"
           "| $$ \\$$$$| $$__/ $$| $$__/ $$| $$__/ $$| $$__| $$| $$__/ $$\n"
           "| $$  \\$$$ \\$$    $$| $$    $$ \\$$    $$ \\$$    $$ \\$$    $$\n"
           " \\$$   \\$$  \\$$$$$$  \\$$$$$$$   \\$$$$$$   \\$$$$$$$ _\\$$$$$$$\n"
           "                                                  |  \\__| $$\n"
           " __                                                \\$$    $$\n"
           "|  \\                                                \\$$$$$$ \n"
           "| $$  ______    ______  __     __   ______    _______       \n"
           "| $$ /      \\  |      \\|  \\   /  \\ /      \\  /       \\      \n"
           "| $$|  $$$$$$\\  \\$$$$$$\\\\$$\\ /  $$|  $$$$$$\\|  $$$$$$$      \n"
           "| $$| $$    $$ /      $$ \\$$\\  $$ | $$    $$ \\$$    \\       \n"
           "| $$| $$$$$$$$|  $$$$$$$  \\$$ $$  | $$$$$$$$ _\\$$$$$$\\      \n"
           "| $$ \\$$     \\ \\$$    $$   \\$$$    \\$$     \\|       $$      \n"
           " \\$$  \\$$$$$$$  \\$$$$$$$    \\$      \\$$$$$$$ \\$$$$$$$       \n"
           "   __      __        __                                     \n"
           "  |  \\    |  \\      |  \\                                    \n"
           " _| $$_   | $$____   \\$$  _______                           \n"
           "|   $$ \\  | $$    \\ |  \\ /       \\                          \n"
           " \\$$$$$$  | $$$$$$$\\| $$|  $$$$$$$                          \n"
           "  | $$ __ | $$  | $$| $$ \\$$    \\                           \n"
           "  | $$|  \\| $$  | $$| $$ _\\$$$$$$\\                          \n"
           "   \\$$  $$| $$  | $$| $$|       $$                          \n"
           "    \\$$$$  \\$$   \\$$ \\$$ \\$$$$$$$                           \n"
           "  ______    ______   ______ ____    ______                  \n"
           " /      \\  |      \\ |      \\    \\  /      \\                 \n"
           "|  $$$$$$\\  \\$$$$$$\\| $$$$$$\\$$$$\\|  $$$$$$\\                \n"
           "| $$  | $$ /      $$| $$ | $$ | $$| $$    $$                \n"
           "| $$__| $$|  $$$$$$$| $$ | $$ | $$| $$$$$$$$                \n"
           " \\$$    $$ \\$$    $$| $$ | $$ | $$ \\$$     \\                \n"
           " _\\$$$$$$$  \\$$$$$$$ \\$$  \\$$  \\$$  \\$$$$$$$                \n"
           "|  \\__| $$                                                  \n"
           " \\$$    $$                                                  \n"
           "  \\$$$$$$                                                   ");
    printf("\n");

    /*Free Memory*/
    freegame(dama,dama->rows,dama->cols);
    return 0;
}

/*  Menu
 *  - Scelta modalita' player singolo
 *  - Scelta modalita' player vs player
 *  - Scelta modalita' player vs pc (commenti del pc)
 *  - Scelta modalita' pc vs pc (commenti di entrambi i pc)
 *
 *  - Scelta colore casuale con una moneta
 *  - Scelta personaggio tradizionale
 *
 *  - Funzionalita' di Quit in qualsiasi momento
 *  - Funzionalita' di Give Up in qualsiasi momento
 *
 *  - Suggerimenti del computer.
 *  -
 *
 */