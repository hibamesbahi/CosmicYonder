#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#define NB_SALLE_MAX 8
//********************** DECLARATION VARIABLES ************************

//caractères
char mur='#';
char porte='/';
char vide= ' ';


//structure salle
typedef struct Position{
  int x;
  int y;

} Position;

//structure Salle
typedef struct Salle {
  int nb_porte;
  Position pos_porte[4];
  int longueur;
  int largeur; 
  Position position;

}Salle;  //generation aleatoire de: POSITION, SURFACE, NB PORTE, CONTENANT


//********************** DECLARATION FONCTION ************************

//creation de la salle de spawn
Salle salleSpawn(Salle* p_map)
{
  int y;  int x;

  p_map[0].position.y= rand()%10+5;
  p_map[0].position.x= rand()%10+5;
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
        mvaddch( y+i,  x+j, mur);
      }
      else if(j==0 || j==p_map[0].longueur)
      {
        mvaddch( y+i,  x+j, mur);

      }
      else{
        mvaddch( y+i,  x+j, vide);}
    }
    printw("\n");

  }
  return p_map[0];

}


Salle* createurMap(){
  Salle* p_map=NULL;

  //generation procedurale
  //nombre de salle en memoire
    //arrengement des salle depend de la graine et de l'ordre.
  int graine = rand(); //graine temporaire
  int nb_salle= 4+(graine%NB_SALLE_MAX);
  p_map=malloc(sizeof(Salle)*nb_salle);
  p_map[0].nb_porte=4;
  p_map[0]=salleSpawn(p_map);
  return p_map;
}
(p_map+indice)
//creation des salle au fur et a mesure
void createurSalle(, int indice){

//creation sur le moment
  //si memoire finie salle sans porte
    //piece ractangulaire, m*n , avec des porte
//creation salle en memoire, pos porte
//verif superposition
//afficher la salle

//if superposition, modifier les coord petit a petit (do while) 



}

void createurPorte(Salle *p_map, int num){

  Salle *salle= (&p_map[num]);
  //haut
  p_map[num].pos_porte[0].x=(rand()%salle->longueur-2)+salle->position.x+1;
  p_map[num].pos_porte[0].y=salle->position.y;

  //bas
  p_map[num].pos_porte[1].x=(rand()%salle->longueur-2)+salle->position.x+1;
  p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;

  //gauche
  p_map[num].pos_porte[2].x=salle->position.x;
  p_map[num].pos_porte[2].y=(rand()%salle->largeur-2)+salle->position.y+1;

  //droite
  p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
  p_map[num].pos_porte[3].y=(rand()%salle->largeur-2)+salle->position.y+1;
//dessiner les porte
          mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
          mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');
          mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');
          mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');
}

void mouvementPerso(Salle *map){

  int c;
  int posX=map[0].position.x + map[0].longueur/2;
  int posY=map[0].position.y+map[0].largeur/2; //initialisation pos
  keypad(stdscr, TRUE);
  refresh();
 mvaddch(posY, posX, '@');
     while(1)
      {c=getch();
        switch (c) {
        case KEY_DOWN:
          if(mvinch(posY+1,posX)!='#'){
          //creation salle if(porte )
          mvaddch(posY, posX, ' ');
          mvaddch(++posY, posX, '@');}
          refresh();

          break;

        case KEY_UP:
          if(mvinch(posY-1,posX)!='#'){
          mvaddch(posY, posX, ' ');
          mvaddch(--posY, posX, '@');}
          refresh();

          break;
          
        case KEY_LEFT:
          if(mvinch(posY,posX-1)!='#'){
          mvaddch(posY, posX, ' ');
          mvaddch(posY, --posX, '@');}
          refresh();

          break;

        case KEY_RIGHT:
          if(mvinch(posY,posX+1)!='#'){        
          mvaddch(posY, posX, ' ');
          mvaddch(posY, ++posX, '@');}
          refresh();

          break;    

        default:
          break; }
           if (c== 'q') break; 

      }

}


//********************** FONCTION MAIN ************************

int main(){
  initscr();
  Salle* map;
  map =createurMap();
  refresh();
  noecho();
  curs_set(0);
  createurPorte(map,0);
  mouvementPerso(map);
  getch();
  endwin();

  return 0;
}
