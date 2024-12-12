#include <stdio.h>

#include <stdlib.h>

#include <ncurses.h>

#include <unistd.h>  // pour usleep

#include "declaration.h"



void afficherTexte(const char* fichier) {

    FILE *file = fopen(fichier, "r");

    if (file == NULL) {

        perror("Erreur lors de l'ouverture du fichier");
        exit(3);

        return;

    }



    char ch;

    while ((ch = fgetc(file)) != EOF) {

        printw("%c", ch);

        refresh();

        usleep(50000);  // 50 milliseconds j ai verifie les calcules

    }



    fclose(file);

    printw("\n"); //ne pas revenir a la ligne revenir (LINES-4,1)

    refresh();

}



void afficherIntro() {

    clear();

    afficherTexte("intro.txt");
    fflush(stdin);
    printw("Appuyez sur une touche pour commencer...\n");

    refresh();

    getch();

}



void afficherVictoire() {

    clear();

    afficherTexte("victoire.txt");
    fflush(stdin);
    printw("Appuyez sur une touche pour quitter...\n");
    fflush(stdin);
    refresh();

    getch();

}



void afficherDefaite() {

    clear();

    afficherTexte("defaite.txt");
    fflush(stdin);
    printw("Appuyez sur une touche pour quitter...\n");

    refresh();

    getch();

}

void afficherRestorer() {

    clear();

    afficherTexte("restorer.txt");
    fflush(stdin);
    printw("Appuyez sur une touche pour quitter...\n");
    fflush(stdin);
    refresh();

    getch();

}
