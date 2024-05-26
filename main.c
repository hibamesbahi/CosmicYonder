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

bool **decouverte;
Monstre monstre;





int main(){
  srand(50); 
  initscr();
  //menu();//-demande la graine
  //timer
  start_color();  //activer les couleur
  init_pair(1,VIOLET,0);
  init_pair(2,6,0);
  init_color(VIOLET, 250,25,255);
  init_pair(3,7,VIOLET);
  printw("**************entrez la graine\n");
  scanw("%d",&graine);
  
  Salle* map=NULL;
  map =createurMap(&nb_salle);


  decouverte = (bool**)malloc(sizeof(bool*)*LINES);
  for(int i=0; i<LINES; i++)
  {
    decouverte[i]= (bool*)malloc(sizeof(bool)*COLS);
    for (int j=0; j<= COLS; j++) 
      decouverte[i][j]=0;
  }
  
  contour();
  refresh();
  noecho();
  curs_set(0);
  
  mouvementPerso(map);
  // afficher defaite victoire
  getch();
  free(decouverte);
  free(map);
  endwin();

  return 0;
}
