#include <stdio.h>                //y->largeur   x->longueur
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include "declaration.h"
extern bool** decouverte;




Salle salleSpawn(Salle* p_map)
{
  int y;  int x;

  p_map[0].position.y= rand()%10+15;
  p_map[0].position.x= rand()%20+40;
  p_map[0].largeur=(rand()%12)+3;
  p_map[0].longueur=(rand()%20)+3;
  y = p_map[0].position.y;
  x = p_map[0].position.x;

  for (int i = 0; i <= p_map[0].largeur; i++)
  {
    for (int j = 0; j <= p_map[0].longueur; j++)
    {
      if (i==0 || i==p_map[0].largeur)
      {
        mvaddch( y+i,  x+j, '#');
      }
      else if(j==0 || j==p_map[0].longueur)
      {
        mvaddch( y+i,  x+j, '#');

      }
      else{
        mvaddch( y+i,  x+j, ' ');}
    }
    //printw("\n");

  }

  Salle *salle= (&p_map[0]);

  salle->nb_porte=4;
  //haut
  salle->pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
  salle->pos_porte[0].y=salle->position.y;

  //bas
  salle->pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
  salle->pos_porte[1].y=salle->position.y+salle->largeur;

  //gauche
  salle->pos_porte[2].x=salle->position.x;
  salle->pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;

  //droite
  salle->pos_porte[3].x=salle->position.x+salle->longueur;
  salle->pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
//dessiner les porte
          mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
          mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');
          mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');
          mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');

  return p_map[0];

}


Salle* createurMap(int *nb_salle){
  Salle* p_map=NULL;

  //generation procedurale
  //nombre de salle en memoire
    //arrengement des salle depend de la graine et de l'ordre.
  
  //graine = rand(); //graine temporaire
  *nb_salle= 4+(graine%NB_SALLE_MAX);
  p_map=malloc(sizeof(Salle)*(*nb_salle));  //free a la fin
    if(p_map==NULL){printw("erreur allocation memeoire");exit(1);}
  p_map[0]=salleSpawn(p_map);
  return p_map;
}




void contour(){
  for(int i=0; i<=LINES; i++)
  {
    for(int j=0; j<=COLS;j++)
    {
     if (i==0 || i== LINES-10){
      attron(COLOR_PAIR(1+j%2));
      mvaddch(i,j,'#');
      attroff(COLOR_PAIR(1+j%2));
     } 
     else if (j==0||j==COLS-30||j==COLS-1)
     {
       attron(COLOR_PAIR(1+i%2));
       mvaddch(i,j,'#');
       attroff(COLOR_PAIR(1+i%2));
     }
     else if(i>LINES-10)
     {
       mvaddch(i,j,' ');      
     }
    }
  }

}
