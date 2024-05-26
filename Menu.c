#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "declaration.h"
extern char nom[16];
extern  clock_t debut;
extern  clock_t fin;

#define VIOLET 10


/*void Timer(int total_time, int *running) {
    int elapsed_time = 0;
    clock_t start_time = clock();

    while (*running && elapsed_time < total_time) {
        clock_t current_time = clock();
        elapsed_time = (current_time - start_time) / CLOCKS_PER_SEC;

       
        int remaining_time = total_time - elapsed_time;
        mvprintw(1, 0, "Temps écoulé: %d secondes", elapsed_time);
        mvprintw(2, 0, "Temps restant: %d secondes", remaining_time);
        refresh();

        napms(100);

        if (remaining_time <= 0) {
            *running = 0;
        }
    }
}*/

void NouvellePartie() {
  clear();
  fflush(stdin);
  printw("**************  entrez la graine *************\n");
  scanw("%d",&graine);
  fflush(stdin);
  printw("**************  entrez le nom 15 lettre max ************\n");
  scanw("%s",nom);
  noecho();  
  afficherIntro();
  
  debut = clock();
  fin=debut*CLOCKS_PER_SEC;
  niveau1(0);
  
}

void AnciennePartie() {
    clear();
    mvprintw(0, 0, "Ancienne Partie...");
    refresh();
    fflush(stdin);
    printw("**************entrez le nom de sauvegarde *********\n");
    scanw("%s",nom);
    afficherRestorer();
    /*
    noecho();
    restorer(nom);

    switch(niveau){
    case 1:
        niveau1(1);
        break;
    case 2:
        niveau2(1);
        break;
    case 3:
        niveau3(1);
        break;
    case 4:
        niveau4(1);
        break;
    case 5:
        niveau5(1);
        break;

    default:
        printw("erreur veuillez recommencer");
        

    }*/
  exit(1);
}

void Menu() {
    // Initialise ncurses
    start_color();  //activer les couleur
    init_pair(1,VIOLET,0);
    init_pair(2,6,0);
    init_color(VIOLET, 250,25,255);
    init_pair(3,7,VIOLET);
    keypad(stdscr, TRUE);

    int c;
    int menu_x = (COLS / 2 - 20); // Coordonnées du menu
    int menu_y = (LINES / 2 - 10);

    char *options[] = {"JOUER", "REPRENDRE PARTIE"}; // Les options du menu
    char element[20];
    clear();

    char *Cosmic_Yonder[] = {
        "_________                      .__         _____.___.                  .___            ",
        "\\_   ___ \\  ____  ______ _____ |__| ____   \\__  |   | ____   ____    __| _/___________ ",
        "/    \\  \\/ /  _ \\/  ___//     \\|  |/ ___\\   /   |   |/  _ \\ /    \\  / __ |/ __ \\_  __ \\",
        "\\     \\___(  <_> )___ \\|  Y Y  \\  \\  \\___   \\____   (  <_> )   |  \\/ /_/ \\  ___/|  | \\/",
        " \\______  /\\____/____  >__|_|  /__|\\___  >  / ______|\\____/|___|  /\\____ |\\___  >__|   ",
        "        \\/           \\/      \\/        \\/   \\/                  \\/      \\/    \\/       ",
        "",
        "q pour quitter",
        "entrée pour valider"
    };

    for (int i = 0; i < 9; i++) {
        mvprintw( i + 10, 2, "%s", Cosmic_Yonder[i]);
    }

    int surligne = 0;


    while (1) {

        c = getch();

        switch (c) {
            case KEY_UP:
                for (int i = 0; i < 6; i++) {
            mvprintw( i + 10, 2, "%s", Cosmic_Yonder[i]);
    }

                surligne=0;
                attron( A_STANDOUT);
                mvprintw(  8, 2, "%s", options[0]);
                attroff( A_STANDOUT);
                mvprintw(  9, 2, "%s", options[1]);
                refresh();
                break;

            case KEY_DOWN:

                for (int i = 0; i < 6; i++) {
            mvprintw( i + 10, 2, "%s", Cosmic_Yonder[i]);
    }

                surligne=1;
                attron( A_STANDOUT);
                mvprintw(  9, 2, "%s", options[1]);
                attroff( A_STANDOUT);
                mvprintw(  8, 2, "%s", options[0]);                
                refresh();
                break;

            case '\n':
                if (surligne == 0) { 

                    NouvellePartie();

                } else if (surligne == 1) {

                    AnciennePartie();
                }
                break;
            case 'q':
                clear();
                endwin();
                return;
        }
    }
}


