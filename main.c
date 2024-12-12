#include <stdio.h>                //y->largeur   x->longueur
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include "declaration.h"

const char mur='#';
const char porte='/';
const char vide= ' ';
int nb_salle=0;
int compteur_porte=5;
int relative_X=0;
int relative_Y=0;
int graine;
char nom[16];
int experience=0;
clock_t temps=0;
int indice;
clock_t debut;
clock_t fin;

Salle *map=NULL;

//bool **decouverte;
Monstre monstre;





int main(){ 
  initscr();
  //timer
  start_color();  //activer les couleur
  init_pair(1,VIOLET,0);
  init_pair(2,6,0);
  init_color(VIOLET, 250,25,255);
  init_pair(3,7,VIOLET);
  curs_set(0);
  Menu();
  refresh();

  endwin();

  return 0;
}
