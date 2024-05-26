#include <stdio.h>                //y->largeur   x->longueur
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include "declaration.h"

extern int graine;
extern int nb_salle;
bool** decouverte;
int niveau=1;



extern int compteur_porte;
extern int relative_X;
extern int relative_Y;
extern Monstre monstre;
extern Salle *map;
/*menu(){
//intro
//sauvgarde -
  //nouvelle partie
	//nom=
  //graine=;
}*/


void niveau5(int mode){
	printw("NIVEAU 5");
  napms(1000);

if (mode ==0){
  	graine++; niveau++; 
    srand(graine);
    intiVariable();
  	map = createurMap(&nb_salle);


    decouverte = (bool**)malloc(sizeof(bool*)*LINES);
    if(decouverte==NULL){
      endwin();
      exit(1);

    }

    for(int i=0; i<LINES; i++)
    {
      decouverte[i]= (bool*)malloc(sizeof(bool)*COLS);
      if(decouverte[i]==NULL){
        for(int f=0; f<i; f++){
          
          free(decouverte[f]);
          endwin();
          exit(1);

      }
      for (int j=0; j< COLS; j++) 
        decouverte[i][j]=0;
    }

  }

}
  mouvementPerso(map);

  
   for (int i = 0; i < LINES; i++) {
        free(decouverte[i]);
      }
    free(decouverte);
    afficherVictoire();


  //victoire- quitter nouvelle partie*********************************



}

void niveau4(int mode){
	printw("NIVEAU 4" );
if (mode ==0){
  	graine++; niveau++;
    srand(graine);
    intiVariable();
  	map =createurMap(&nb_salle);

  decouverte = (bool**)malloc(sizeof(bool*)*LINES);
    if(decouverte==NULL){
      endwin();
      exit(1);

    }

    for(int i=0; i<LINES; i++)
    {
      decouverte[i]= (bool*)malloc(sizeof(bool)*COLS);
      if(decouverte[i]==NULL){
        for(int f=0; f<i; f++){
          
          free(decouverte[f]);
          endwin();
          exit(1);

      }
      for (int j=0; j< COLS; j++) 
        decouverte[i][j]=0;
    }

  }
}
  mouvementPerso(map);

  
   for (int i = 0; i < LINES; i++) {
        free(decouverte[i]);
      }
    free(decouverte);


  niveau5(0);


}

void niveau3(int mode){
		printw("NIVEAU 3" );
if (mode ==0){
  	graine++; niveau++;
    srand(graine);
    intiVariable();
  	map =createurMap(&nb_salle);

  decouverte = (bool**)malloc(sizeof(bool*)*LINES);
    if(decouverte==NULL){
      endwin();
      exit(1);

    }

    for(int i=0; i<LINES; i++)
    {
      decouverte[i]= (bool*)malloc(sizeof(bool)*COLS);
      if(decouverte[i]==NULL){
        for(int f=0; f<i; f++){
          
          free(decouverte[f]);
          endwin();
          exit(1);

      }
      for (int j=0; j< COLS; j++) 
        decouverte[i][j]=0;
    }

  }
}
  mouvementPerso(map);

  
   for (int i = 0; i < LINES; i++) {
        free(decouverte[i]);
      }
    free(decouverte);


  niveau4(0);


}

void niveau2(int mode){
		printw("NIVEAU 2" );
		napms(1000);
if (mode ==0){
  	graine++; niveau++;
    srand(graine);
    intiVariable();
  	map =createurMap(&nb_salle);

  decouverte = (bool**)malloc(sizeof(bool*)*LINES);
    if(decouverte==NULL){
      endwin();
      exit(1);

    }

    for(int i=0; i<LINES; i++)
    {
      decouverte[i]= (bool*)malloc(sizeof(bool)*COLS);
      if(decouverte[i]==NULL){
        for(int f=0; f<i; f++){
          
          free(decouverte[f]);
          endwin();
          exit(1);

      }
      for (int j=0; j< COLS; j++) 
        decouverte[i][j]=0;
    }
  }
}
  mouvementPerso(map);

  
   for (int i = 0; i < LINES; i++) {
        free(decouverte[i]);
      }
    free(decouverte);

  niveau3(0);


}

void niveau1(int mode){
	printw("NIVEAU 1" );
  niveau=1;	
	napms(1000);    
  srand(graine);

  if (mode ==0){
    intiVariable();
    map =createurMap(&nb_salle);


    decouverte = (bool**)malloc(sizeof(bool*)*LINES);
    if(decouverte==NULL){
      endwin();
      exit(1);

    }

    for(int i=0; i<LINES; i++)
    {
      decouverte[i]= (bool*)malloc(sizeof(bool)*COLS);
      if(decouverte[i]==NULL){
        for(int f=0; f<i; f++){
          
          free(decouverte[f]);
          endwin();
          exit(1);

      }
      for (int j=0; j< COLS; j++) 
        decouverte[i][j]=0;
    }
   } 
}

  mouvementPerso(map);

  
   for (int i = 0; i < LINES; i++) {
        free(decouverte[i]);
      }
    free(decouverte);

  
  niveau2(0);
}


void intiVariable(){

nb_salle=0;
compteur_porte=5;
relative_X=0;
relative_Y=0;
monstre.existe=0;
map==NULL;
}
