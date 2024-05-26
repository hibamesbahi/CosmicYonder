#include <stdio.h>                //y->largeur   x->longueur
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include "modeCombat.h"
#define NB_SALLE_MAX 8 
#define LONG_MAX 20
#define LARG_MAX 7
#define VIOLET 10

// ********************** DECLARATION VARIABLES ************************
  WINDOW *boite;
//caractères
const char mur='#';
const char porte='/';
const char vide= ' ';
int nb_salle=0;
int compteur_porte=5;
int relative_X=0;
int relative_Y=0;



//structure salle
/*typedef struct Position{
  int x;
  int y;

} Position;*/

//structure Salle
typedef struct Salle {
  int nb_porte;
  Position pos_porte[4];
  int longueur;
  int largeur; 
  Position position;

}Salle;

typedef struct monstre {
Position position;
bool existe;



} Monstre;


  //generation aleatoire de: POSITION, SURFACE, NB PORTE, CONTENANT

bool **decouverte;
Monstre monstre;

//rand

//********************** DECLARATION FONCTION ************************
void contour(void);
//creation de la salle de spawn
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
  
  int graine = rand(); //graine temporaire
  *nb_salle= 4+(graine%NB_SALLE_MAX);
  p_map=malloc(sizeof(Salle)*(*nb_salle));  //free a la fin
    if(p_map==NULL)exit(1);
  p_map[0]=salleSpawn(p_map);
  return p_map;
}

void verifSuperpo(Salle *map, int nb_salle, Salle* nouv_salle,char cote) {
if(map==NULL)exit  (1); 
  int superpo1=0;
  int superpo2=0;

//depassement hors du cadre
  if(nouv_salle->position.y<=0){
    superpo2=1-nouv_salle->position.y;
    nouv_salle->position.y+=superpo2;
    nouv_salle->largeur-=superpo2;
  }
  if(nouv_salle->position.y+nouv_salle->largeur>=LINES){
    superpo2=nouv_salle->position.y+1+nouv_salle->largeur-(LINES-1) ;
    nouv_salle->largeur-=superpo2;
  }
  if(nouv_salle->position.x+nouv_salle->longueur<=0){
    superpo1=1-nouv_salle->position.x;
    nouv_salle->position.x+=superpo1;
    nouv_salle->longueur-=superpo1;
  }
  if(nouv_salle->position.x>=COLS-1){
    superpo1=COLS-1-1-nouv_salle->position.x;
    nouv_salle->position.x-=superpo1;
  }



    for (int i = 0; i < nb_salle; i++) {
        Salle s = map[i];
        
  bool gauche =(nouv_salle->position.x + nouv_salle->longueur) >= s.position.x && (nouv_salle->position.x+nouv_salle->longueur<=s.position.x+s.longueur);//left
  bool droite= nouv_salle->position.x <= (s.position.x + s.longueur)&& (nouv_salle->position.x >= s.position.x) ; //right
  bool haut=(nouv_salle->position.y + nouv_salle->largeur) >= s.position.y && nouv_salle->position.y+nouv_salle->largeur <= s.position.y +s.largeur  ;// top
  bool bas = nouv_salle->position.y <= (s.position.y + s.largeur) && (nouv_salle->position.y)>= s.position.y; //bas
 
    //left and top

  //g nouv_salle.position.x + nouv_salle.longueur - s.position.x;
  //d s.position.x + s.longueur - nouv_salle.position.x;
  //h nouv_salle.position.y + nouv_salle.largeur - s->position.y
  //b s.position.y + s.largeur - nouv_salle.position.y



  if(gauche && haut) {
     superpo1= 1+nouv_salle->position.x + nouv_salle->longueur - s.position.x;
     superpo2= 1+nouv_salle->position.y + nouv_salle->largeur - s.position.y;
     
     if(cote=='h'||cote=='b'){nouv_salle->longueur -= superpo1;}
     else {nouv_salle->largeur -= superpo2;}
  }
  //right and top
  else if(droite && haut) {
      superpo1= 1+s.position.x + s.longueur - nouv_salle->position.x;
      superpo2= 1+nouv_salle->position.y + nouv_salle->largeur - s.position.y;
     if(cote=='h'||cote=='b'){
      nouv_salle->position.x += superpo1;
      nouv_salle->longueur-=superpo1;
      }
      else {nouv_salle->largeur -= superpo2;}
      }     


      //left and bottom    
  else if(gauche && bas) {
      superpo1= 1+nouv_salle->position.x + nouv_salle->longueur - s.position.x;
      superpo2= 1+s.position.y + s.largeur - nouv_salle->position.y;
     if(cote=='h'||cote=='b'){
      nouv_salle->longueur -= superpo1;}
     else {
      nouv_salle->position.y += superpo2;
      nouv_salle->largeur -= superpo2;
          }
    }    

  //right and bottom    
  else if(droite && bas) {
      superpo1= 1+s.position.x + s.longueur - nouv_salle->position.x;
      superpo2= 1+s.position.y + s.largeur - nouv_salle->position.y;
     if(cote=='h'||cote=='b'){
      nouv_salle->longueur -= superpo1;
      nouv_salle->position.x += superpo1;
      }
     else {
      nouv_salle->position.y += superpo2;
      nouv_salle->largeur-=superpo2;
      }
    }
        
  }
}


void createurPorte(Salle *p_map, int num, int ind_porte){

//une porte aleatoire deja 
//nb porte = rand ()
  Salle *salle= (&p_map[num]);

int indice1;
int indice2;
int indice3;
int posX_ind_porte = p_map[num].pos_porte[ind_porte].x; //on va perdre ces coordonnées dans...
int posY_ind_porte = p_map[num].pos_porte[ind_porte].y; // ...le prosesus donc on les copie
    
      
switch (salle->nb_porte) {
case 1:
  //ne rien faire
    //autre porte coord -1000,-1000
    

    p_map[num].pos_porte[(ind_porte+1)%4].x=-1000;
    p_map[num].pos_porte[(ind_porte+1)%4].y=-1000;

    p_map[num].pos_porte[(ind_porte+2)%4].x=-1000;
    p_map[num].pos_porte[(ind_porte+2)%4].y=-1000;

    p_map[num].pos_porte[(ind_porte+3)%4].x=-1000;
    p_map[num].pos_porte[(ind_porte+3)%4].y=-1000;
  break;

case 2: //si la salle possede 2 porte
// placer une porte aléatoirement
  indice1= (ind_porte+1+rand()%3)%4 ;  //indice de la porte de passage plus une valeure entre 1 et 3 
                                      //la porte crée sera soit 1 porte plus loin soit 2 soit 3
    switch (indice1){
  case 0: //porte du haut

    //calculer position porte x et y 
    //definire variable a nom cours pour x et y
    // si pas assez d'espace apres la porte annuler la porte nb porte-- et coordoné -1000,-1000

    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;
    
    p_map[num].pos_porte[1].x=-1000;
    p_map[num].pos_porte[1].y=-1000;

    p_map[num].pos_porte[2].x=-1000;
    p_map[num].pos_porte[2].y=-1000;

    p_map[num].pos_porte[3].x=-1000;
    p_map[num].pos_porte[3].y=-1000;

    int y10=p_map[num].pos_porte[0].y;
    int x10=p_map[num].pos_porte[0].x;
    //verification placement de porte incopatible avec architechture de la carte
    if(mvinch(y10-1,x10)=='#'||mvinch(y10-2,x10)=='#'||mvinch(y10-3,x10)=='#'||mvinch(y10-4,x10)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[0].x=-1000;
        p_map[num].pos_porte[0].y=-1000;
    }

    break;
  case 1: //porte du bas
    
    p_map[num].pos_porte[0].x=-1000;
    p_map[num].pos_porte[0].y=-1000;

    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;

    p_map[num].pos_porte[2].x=-1000;
    p_map[num].pos_porte[2].y=-1000;

    p_map[num].pos_porte[3].x=-1000;
    p_map[num].pos_porte[3].y=-1000;

    int y11=p_map[num].pos_porte[1].y;
    int x11=p_map[num].pos_porte[1].x;
    //verification placement de porte incopatible avec architechture de la carte
    if(mvinch(y11+1,x11)=='#'||mvinch(y11+2,x11)=='#'||mvinch(y11+3,x11)=='#'||mvinch(y11+4,x11)=='#'){
        salle->nb_porte--; // si les conditions ne sont pas remplies, on efface la porte
        p_map[num].pos_porte[1].x=-1000;
        p_map[num].pos_porte[1].y=-1000;
    }

    break;
   
  case 2: //porte de gauche
    p_map[num].pos_porte[0].x=-1000;
    p_map[num].pos_porte[0].y=-1000;

    p_map[num].pos_porte[1].x=-1000;
    p_map[num].pos_porte[1].y=-1000;

    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;

    p_map[num].pos_porte[3].x=-1000;
    p_map[num].pos_porte[3].y=-1000;

    int x12=p_map[num].pos_porte[2].x;
    int y12=p_map[num].pos_porte[2].y;

    if(mvinch(y12,x12-1)=='#'||mvinch(y12,x12-2)=='#'||mvinch(y12,x12-3)=='#'||mvinch(y12,x12-4)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[2].x=-1000;
        p_map[num].pos_porte[2].y=-1000;
    }

    break;

  case 3: //porte de droite
    p_map[num].pos_porte[0].x=-1000;
    p_map[num].pos_porte[0].y=-1000;

    p_map[num].pos_porte[1].x=-1000;
    p_map[num].pos_porte[1].y=-1000;

    p_map[num].pos_porte[2].x=-1000;
    p_map[num].pos_porte[2].y=-1000;

    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;

    int x13=p_map[num].pos_porte[3].x;
    int y13=p_map[num].pos_porte[3].y;

    if(mvinch(y13,x13+1)=='#'||mvinch(y13,x13+2)=='#'||mvinch(y13,x13+3)=='#'||mvinch(y13,x13+4)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[3].x=-1000;
        p_map[num].pos_porte[3].y=-1000;
    }
   
    break;
   } 
  
  break; //fin du switch si la salle possede 2 porte



case 3: // switch cas ou la salle posède 3 portes
  //faire 2 porte de plus
  indice1= (ind_porte+1+rand()%2)%4 ;  //indice de la porte de passage plus une valeure entre 1 et 2 ;
  // indice2= indice1+1;

    switch (indice1){
  case 0: //porte du haut
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;

    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;

    p_map[num].pos_porte[2].x=-1000;
    p_map[num].pos_porte[2].y=-1000;

    p_map[num].pos_porte[3].x=-1000;
    p_map[num].pos_porte[3].y=-1000;

    int y20=p_map[num].pos_porte[0].y;
    int x20=p_map[num].pos_porte[0].x;
    int yy20=p_map[num].pos_porte[1].y;
    int xx20=p_map[num].pos_porte[1].x;

    if(mvinch(y20-1,x20)=='#'||mvinch(y20-2,x20)=='#'||mvinch(y20-3,x20)=='#'||mvinch(y20-4,x20)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[0].x=-1000;
        p_map[num].pos_porte[0].y=-1000;
        break;
    }
    if(mvinch(yy20+1,xx20)=='#'||mvinch(yy20+2,xx20)=='#'||mvinch(yy20+3,xx20)=='#'||mvinch(yy20+4,xx20)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[1].x=-1000;
        p_map[num].pos_porte[1].y=-1000;
        break;
    }

    
    break;
  case 1: //porte du bas et gauche
    p_map[num].pos_porte[0].x=-1000;
    p_map[num].pos_porte[0].y=-1000;

    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;

    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;

    p_map[num].pos_porte[3].x=-1000;
    p_map[num].pos_porte[3].y=-1000;

    int y21=p_map[num].pos_porte[1].y;
    int x21=p_map[num].pos_porte[1].x;
    int yy21=p_map[num].pos_porte[2].y;
    int xx21=p_map[num].pos_porte[2].x;
    
    if(mvinch(y21+1,x21)=='#'||mvinch(y21+2,x21)=='#'||mvinch(y21+3,x21)=='#'||mvinch(y21+4,x21)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[1].x=-1000;
        p_map[num].pos_porte[1].y=-1000;
        break;
    }
    if(mvinch(yy21,xx21-1)=='#'||mvinch(yy21,xx21-2)=='#'||mvinch(yy21,xx21-3)=='#'||mvinch(yy21,xx21-4)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[2].x=-1000;
        p_map[num].pos_porte[2].y=-1000;
        break;
    }

    break;
  case 2: //porte de gauche
    p_map[num].pos_porte[0].x=-1000;
    p_map[num].pos_porte[0].y=-1000;

    p_map[num].pos_porte[1].x=-1000;
    p_map[num].pos_porte[1].y=-1000;

    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;

    int x22=p_map[num].pos_porte[2].x;
    int y22=p_map[num].pos_porte[2].y;
    int xx22=p_map[num].pos_porte[3].x;
    int yy22 =p_map[num].pos_porte[3].y;

    if(mvinch(y22,x22-1)=='#'||mvinch(y22,x22-2)=='#'||mvinch(y22,x22-3)=='#'||mvinch(y22,x22-4)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[2].x=-1000;
        p_map[num].pos_porte[2].y=-1000;
        break;
    }
    if(mvinch(yy22 ,xx22+1)=='#'||mvinch(yy22,xx22+2)=='#'||mvinch(yy22,xx22+3)=='#'||mvinch(yy22,xx22+4)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[3].x=-1000;
        p_map[num].pos_porte[3].y=-1000;
        break;
    }
    
    break;

  case 3: //porte de droite
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;

    p_map[num].pos_porte[1].x=-1000;
    p_map[num].pos_porte[1].y=-1000;

    p_map[num].pos_porte[2].x=-1000;
    p_map[num].pos_porte[2].y=-1000;

    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;

    int y23=p_map[num].pos_porte[0].y;
    int xx23=p_map[num].pos_porte[0].x;
    int x23=p_map[num].pos_porte[3].x;
    int yy23=p_map[num].pos_porte[3].y;
   
    if(mvinch(y23-1,x23)=='#'||mvinch(y23-2,x23)=='#'||mvinch(y23-3,x23)=='#'||mvinch(y23-4,x23)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[0].x=-1000;
        p_map[num].pos_porte[0].y=-1000;
        break;
    }
    if(mvinch(yy23,xx23+1)=='#'||mvinch(yy23,xx23+2)=='#'||mvinch(yy23,xx23+3)=='#'||mvinch(yy23,xx23+4)=='#'){
        salle->nb_porte--;
        p_map[num].pos_porte[3].x=-1000;
        p_map[num].pos_porte[3].y=-1000;
        break;
    }
    break;
  }

  break; // fin du switch cas ou la salle possède 3 portes





case 4 : // cas ou la salle possède 4 porte
indice1=(ind_porte + 1)%4;
indice2=(ind_porte + 2)%4;
indice3=(ind_porte + 3)%4;

  switch (indice1){
  case 0: //porte du haut
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;
    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;
    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;

    int y30=p_map[num].pos_porte[0].y;
    int yy30=p_map[num].pos_porte[1].y;
    int xxx30=p_map[num].pos_porte[2].x;
    int x30=p_map[num].pos_porte[0].x;
    int xx30=p_map[num].pos_porte[1].x;
    int yyy30=p_map[num].pos_porte[2].y;

    if(mvinch(y30-1,x30)=='#'||mvinch(y30-2,x30)=='#'||mvinch(y30-3,x30)=='#'||mvinch(y30-4,x30)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[0].x=-1000;
        p_map[num].pos_porte[0].y=-1000;
        break;
    }
    if(mvinch(yy30+1,xx30)=='#'||mvinch(yy30+2,xx30)=='#'||mvinch(yy30+3,xx30)=='#'||mvinch(yy30+4,xx30)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[1].x=-1000;
        p_map[num].pos_porte[1].y=-1000;
        break;
    }
    if(mvinch(yyy30,xxx30-1)=='#'||mvinch(yyy30,xxx30-2)=='#'||mvinch(yyy30,xxx30-3)=='#'||mvinch(yyy30,xxx30-4)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[2].x=-1000;
        p_map[num].pos_porte[2].y=-1000;
        break;
    }

    break;
  case 1: //porte du bas
    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;
    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;

    int y31=p_map[num].pos_porte[1].y;
    int xx31=p_map[num].pos_porte[2].x;
    int xxx31=p_map[num].pos_porte[3].x;
    int x31=p_map[num].pos_porte[1].x;
    int yy31=p_map[num].pos_porte[2].y;
    int yyy31=p_map[num].pos_porte[3].y;

    if(mvinch(y31+1,x31)=='#'||mvinch(y31+2,x31)=='#'||mvinch(y31+3,x31)=='#'||mvinch(y31+4,x31)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[1].x=-1000;
        p_map[num].pos_porte[1].y=-1000;
        break;
    }
    if(mvinch(yy31,xx31-1)=='#'||mvinch(yy31,xx31-2)=='#'||mvinch(yy31,xx31-3)=='#'||mvinch(yy31,xx31-4)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[2].x=-1000;
        p_map[num].pos_porte[2].y=-1000;
        break;
    }
    if(mvinch(yyy31,xxx31+1)=='#'||mvinch(yyy31,xxx31+2)=='#'||mvinch(yyy31,xxx31+3)=='#'||mvinch(yyy31,xxx31+4)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[2].x=-1000;
        p_map[num].pos_porte[3].y=-1000;
        break;
    }

    
    break;
  case 2: //porte de gauche
    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;

    int y32=p_map[num].pos_porte[0].y;
    int xx32=p_map[num].pos_porte[2].x;
    int xxx32=p_map[num].pos_porte[3].x;

    int x32=p_map[num].pos_porte[0].x;
    int yy32=p_map[num].pos_porte[2].y;
    int yyy32=p_map[num].pos_porte[3].y;

    if(mvinch(y32-1,x32)=='#'||mvinch(y32-2,x32)=='#'||mvinch(y32-3,x32)=='#'||mvinch(y32-4,x32)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[0].x=-1000;
        p_map[num].pos_porte[0].y=-1000;
        break;
    }
    if(mvinch(yy32,xx32-1)=='#'||mvinch(yy32,xx32-2)=='#'||mvinch(yy32,xx32-3)=='#'||mvinch(yy32,xx32-4)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[2].x=-1000;
        p_map[num].pos_porte[2].y=-1000;
        break;
    }
    if(mvinch(yyy32,xxx32+1)=='#'||mvinch(yyy32,xxx32+2)=='#'||mvinch(yyy32,xxx32+3)=='#'||mvinch(yyy32,xxx32+4)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[3].x=-1000;
        p_map[num].pos_porte[3].y=-1000;
        break;
    }

    break;

  case 3: //porte de droite
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;
    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;

    int y33=p_map[num].pos_porte[0].y;
    int yy33=p_map[num].pos_porte[1].y;
    int xxx33=p_map[num].pos_porte[3].x;
    int x33=p_map[num].pos_porte[0].x;
    int xx33=p_map[num].pos_porte[1].x;
    int yyy33=p_map[num].pos_porte[3].y;

    if(mvinch(y33-1,x33)=='#'||mvinch(y33-2,x33)=='#'||mvinch(y33-3,x33)=='#'||mvinch(y33-4,x33)=='#'){
        salle->nb_porte=2;
        p_map[num].pos_porte[0].x=-1000;
        p_map[num].pos_porte[0].y=-1000;
        break;
    }
    if(mvinch(yy33+1,xx33)=='#'||mvinch(yy33+2,xx33)=='#'||mvinch(yy33+3,xx33)=='#'||mvinch(yy33+4,xx33)=='#'){
        salle->nb_porte=1;
        p_map[num].pos_porte[1].x=-1000;
        p_map[num].pos_porte[1].y=-1000;
        break;
    }
    if(mvinch(yyy33,xxx33+1)=='#'||mvinch(yyy33,xxx33+2)=='#'||mvinch(yyy33,xxx33+3)=='#'||mvinch(yyy33,xxx33+4)=='#'){
        salle->nb_porte-=1;
        p_map[num].pos_porte[3].x=-1000;
        p_map[num].pos_porte[3].y=-1000;
        break;
    }

    break;
  }
break;  
 default:
 printf("erreur\n");
 break;
}  
        p_map[num].pos_porte[ind_porte].x = posX_ind_porte;     // on recopie les cordonnées
        p_map[num].pos_porte[ind_porte].y = posY_ind_porte;     // qu'on avais perdu plus tot

        /*mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
        mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');
        mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');
        mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');*/

}

//************************* createur salle ***********************

//creation des salle au fur et a mesure
void createurSalle(Salle* map, int y, int x, char cote, int indice){
  //creation sur le moment
    //si memoire finie salle sans porte
      //piece ractangulaire, m*n , avec des porte
  //creation salle en memoire, pos porte
decouverte[y][x]=1;  
Salle nouv_salle; 

int ind_porte; //indice de la porte par laquelle on passe 0:haut,1;bas,2:gauche,3:droite
nouv_salle.longueur=(rand()%LONG_MAX)+3;
nouv_salle.largeur=(rand()%LARG_MAX)+3;

if (compteur_porte==(nb_salle-2)){ //place en memoire pour 2 salles de plus
  nouv_salle.nb_porte=(rand()%2)+2;  //au max 2 porte de plus,au min 1 salle de plus pour etre sur de generer au moin encore une salle
                                      //et ne pas etre coincer
}                                    //plus celle par ou on  est passé =3 au max =2 au min 

else if (compteur_porte==(nb_salle-1)){ //place en memoire pour 1 salles de plus 
                                        //elle sera deriere cette salle, les 2 dernière salle sont collée
      nouv_salle.nb_porte=2;
}
else if (compteur_porte==(nb_salle)){ //plus de place, salle possède seulement 
      nouv_salle.nb_porte=1;          // 1 porte, celle par laquelle on est arrivée
      if(indice==nb_salle-1)
        monstre.existe=1;   //c'est donc la dernière salle, y placer le monstre
} 
else { 
        nouv_salle.nb_porte=(rand()%4)+1; //entre 1 et 4 portes
}
  

    switch(cote){
  case 'h': 
      ind_porte=1;
      y--;
      /*place_perso.x=x;
      place_perso.y=y-1;*/
      break;
  case 'b': 
      ind_porte=0;
      y++;
      /*place_perso.x=x;
      place_perso.y=y+1;*/
      break;
  case 'g': 
      ind_porte=3;
      x--;
      /*place_perso.x=x-1;
      place_perso.y=y;*/
      break;
  case 'd': 
      ind_porte=2;
      x++;
      /*place_perso.x=x+1;
      place_perso.y=y;*/
      break;
  }
  nouv_salle.pos_porte[ind_porte].x=x;
  nouv_salle.pos_porte[ind_porte].y=y;
  decouverte[y][x]=1;
  
    switch(cote){
  case 'h': 
      nouv_salle.position.x=x-(rand()%(nouv_salle.longueur-2))-1 ;
      nouv_salle.position.y= y-nouv_salle.largeur;
      break;
  case 'b': 
      nouv_salle.position.x=x-(rand()%(nouv_salle.longueur-2))-1 ;
      nouv_salle.position.y= y;
      break;
  case 'g': 
      nouv_salle.position.x=x-nouv_salle.longueur ;
      nouv_salle.position.y= y-(rand()%(nouv_salle.largeur-2))-1;
      break;
  case 'd': 
      nouv_salle.position.x= x;
      nouv_salle.position.y= y-(rand()%(nouv_salle.largeur-2))-1;
      break;        
  }

map[indice]=nouv_salle;
//verif superposition
verifSuperpo(map, indice, &map[indice],cote);//passage pas adresse pour pouvoir modifier

int L=map[indice].position.x;  //position de depard du mur
int l=map[indice].position.y;
int L_fin=L+map[indice].longueur; //position de fin du mur 
int l_fin=l+map[indice].largeur;

  
  //afficher la salle
  /*for(int i=l; i<=l_fin; i++)
  {
    for(int j=L; j<=L_fin; j++)
    {
      if(i==map[indice].position.y || i==l_fin)
      {
        mvaddch(i,j,'#');
      }
      else if(j==map[indice].position.x || j==L_fin )
      {
        mvaddch(i,j,'#');
      }
      else 
      {
        mvaddch(i,j,' ');
      }
    }  
    move(i+1,L);
   
  }*/

  createurPorte(map, indice, ind_porte);
  compteur_porte+=(map[indice].nb_porte-1);//compte le nombre de nouvelle porte crée
                                          //garde un totale du nombre de salle potentiel existante

if(monstre.existe==1){
  monstre.position.y=map[indice].position.y+1+rand()%(map[indice].largeur-2);
  monstre.position.x=map[indice].position.x+1+rand()%(map[indice].longueur-2);
  //mvaddch(monstre.position.y,monstre.position.x,'!');

}
  //mvaddch(y,x,'/');
  //mvaddch(place_perso.y,place_perso.x,'@');
  //faire des porte sachant que 1 porte deja faite

  //faire avancer le personnage directe dans la salle, ' ', '/', '/', '@'
  //if superposition, modifier les coord petit a petit (do while) 

}

/*void combat(void){
  //a remplir

}*/
void item(void){
  //a remplir

}
void dessinerSalle(Salle* map){
//dessiner la salle
Salle nouv_salle=(*map);
int L=nouv_salle.position.x;  //position de depard du mur
int l=nouv_salle.position.y;
int L_fin=L+nouv_salle.longueur; //position de fin du mur 
int l_fin=l+nouv_salle.largeur;

  
  //afficher la salle
  for(int i=l; i<=l_fin; i++)
  {
    for(int j=L; j<=L_fin; j++)
    {
      if(i==nouv_salle.position.y || i==l_fin)
      {
        mvaddch(i,j,'#');
      }
      else if(j==nouv_salle.position.x || j==L_fin )
      {
        mvaddch(i,j,'#');
      }
      else 
      {
        mvaddch(i,j,' ');
      }
    }  
    move(i+1,L);
   
  }



//ajjouter les portes
        mvaddch(nouv_salle.pos_porte[0].y, nouv_salle.pos_porte[0].x, '/');
        mvaddch(nouv_salle.pos_porte[1].y, nouv_salle.pos_porte[1].x, '/');
        mvaddch(nouv_salle.pos_porte[2].y, nouv_salle.pos_porte[2].x, '/');
        mvaddch(nouv_salle.pos_porte[3].y, nouv_salle.pos_porte[3].x, '/');



}
int porteBloquee(int y,int x,char cote){
  switch (cote){
  case 'h':
    if((y-1<=0)||mvinch(y-1, x)== '#'|| mvinch(y-2, x)== '#'|| mvinch(y-3, x)== '#'|| mvinch(y-1, x-1)== '#'||mvinch(y-1, x+1)== '#'||mvinch(y-4, x)== '#' )
    {
      mvprintw( LINES-4, 1,"cette porte est bloquee par des debris intergalactique");
      mvprintw(LINES-3,1,"impossible de passer");
      if(compteur_porte==nb_salle){
        monstre.existe=1;
        monstre.position.y=y+2-relative_Y;
        monstre.position.x=x-relative_X ;        
      }
      compteur_porte--;
      getch();
      return 1;
    }
    break;
  case 'b' :
    if((y+1>=LINES-2)||(mvinch(y+1, x)== '#')|| (mvinch(y+2, x)== '#')||( mvinch(y+3, x)== '#')|| (mvinch(y+1, x-1)== '#')||(mvinch(y+1, x+1)== '#')||(mvinch(y+4, x)== '#' ))
    {
      mvprintw( LINES-4, 1,"cette porte est bloquee par des debris intergalactique");
      mvprintw(LINES-3,1,"impossible de passer");
      if(compteur_porte==nb_salle){
        monstre.existe=1;
        monstre.position.y=y-2-relative_Y;
        monstre.position.x=x-relative_X;        
      }
      compteur_porte--;
      getch();
      return 1;
    }
    break;
  case 'g' :
    if((x-1<=0)||mvinch(y, x-1)== '#'|| mvinch(y, x-2)== '#'|| mvinch(y, x-3)== '#'|| mvinch(y-1, x-1)== '#'||mvinch(y+1, x-1)== '#'||mvinch(y, x-4)== '#' )
    {
      mvprintw( LINES-4, 1,"cette porte est bloquee par des debris intergalactique");
      mvprintw(LINES-3,1,"impossible de passer");
      if(compteur_porte==nb_salle){
        monstre.existe=1;
        monstre.position.y=y-relative_Y;
        monstre.position.x=x+2-relative_X;        
      }
      compteur_porte--;
      getch();
      return 1;
    }
    break;
  case 'd':
    if((x-1>=COLS-2)||mvinch(y, x+1)== '#'|| mvinch(y, x+2)== '#'|| mvinch(y, x+3)== '#'|| mvinch(y-1, x+1)== '#'||mvinch(y+1, x+1)== '#'||mvinch(y, x+4)== '#' )
    {
      mvprintw( LINES-4, 1,"cette porte est bloquee par des debris intergalactique");
      mvprintw(LINES-3,1,"impossible de passer");
      if(compteur_porte==nb_salle){
        monstre.existe=1;
        monstre.position.y=y-relative_Y;
        monstre.position.x=x-2-relative_X;        
      }
      compteur_porte--;
      getch();
      return 1;
    }
    break;
  default :
    break;

} return 0;

}

void mouvementRelatif(Salle *map, int indice, int posY, int posX){

for (int a = 1; a < LINES-10; a++)
      {
        for (int b = 1; b < COLS-31; b++)
        {
          mvaddch(a,b,' ');
        }
      } 
Salle nouv_salle;
  for(int ind=0; ind<=indice; ind++) 
  {
    nouv_salle=(map[ind]);
    int L=nouv_salle.position.x;  //position de depard du mur
    int l=nouv_salle.position.y;
    int L_fin=L+nouv_salle.longueur; //position de fin du mur 
    int l_fin=l+nouv_salle.largeur;
     
      //afficher la salle
      for(int i=l; i<=l_fin; i++)
      {
        for(int j=L; j<=L_fin; j++)
        {
          if(i==nouv_salle.position.y || i==l_fin)
          {
            mvaddch(i+relative_Y,j+relative_X,'#');
          }
          else if(j==nouv_salle.position.x || j==L_fin )
          {
            mvaddch(i+relative_Y,j+relative_X,'#');
          }
          else 
          {
            mvaddch(i+relative_Y,j+relative_X,' ');
          }
        }  
        //move(i+1,L);
       
      }


    //ajouter les portes
            mvaddch(nouv_salle.pos_porte[0].y+relative_Y, nouv_salle.pos_porte[0].x+relative_X, '/');
            mvaddch(nouv_salle.pos_porte[1].y+relative_Y, nouv_salle.pos_porte[1].x+relative_X, '/');
            mvaddch(nouv_salle.pos_porte[2].y+relative_Y, nouv_salle.pos_porte[2].x+relative_X, '/');
            mvaddch(nouv_salle.pos_porte[3].y+relative_Y, nouv_salle.pos_porte[3].x+relative_X, '/');

            if(monstre.existe==1){

              mvaddch(monstre.position.y+relative_Y,monstre.position.x+relative_X,'!');
            }
            mvaddch(posY+relative_Y,posX+relative_X,'@');
            contour();
            mvprintw(LINES-4, COLS-25,"posY: %d   LINES=%d",posY, LINES);
            mvprintw(LINES-3, COLS-25,"posX: %d   COLS=%d",posX, COLS);
  }
//puis ne laisser apparaitre qu'un champs reduit de vison
  for (int i=1; i<LINES-10; i++){
            for (int j=1; j<=COLS-31;j++){
              if(((j>relative_X+posX+6||j<relative_X+posX-6)|| (i>relative_Y+posY+5||i<relative_Y+posY-5))){
                mvaddch(i, j, ' ');
              }
            }
          }

//nom du jeu  
    attron(COLOR_PAIR(3));
      mvprintw(LINES-8, 23 , "_________                      .__         _____.___.                  .___            ");
      mvprintw(LINES-7, 23 , "\\_   ___ \\  ____  ______ _____ |__| ____   \\__  |   | ____   ____    __| _/___________ ");
      mvprintw(LINES-6, 23 , "/    \\  \\/ /  _ \\/  ___//     \\|  |/ ___\\   /   |   |/  _ \\ /    \\  / __ |/ __ \\_  __ \\");
      mvprintw(LINES-5, 23 , "\\     \\___(  <_> )___ \\|  Y Y  \\  \\  \\___   \\____   (  <_> )   |  \\/ /_/ \\  ___/|  | \\/");
      mvprintw(LINES-4, 23 , " \\______  /\\____/____  >__|_|  /__|\\___  >  / ______|\\____/|___|  /\\____ |\\___  >__|   ");
      mvprintw(LINES-3, 23 , "        \\/           \\/      \\/        \\/   \\/                  \\/      \\/    \\/       ");
    attroff(COLOR_PAIR(3));


}

void mouvementPerso(Salle *map){

  int c;char ver; int indice=0;
  int posX=map[0].position.x + map[0].longueur/2;
  int posY=map[0].position.y+map[0].largeur/2; //initialisation position de depart
  keypad(stdscr, TRUE);
  mvaddch(posY, posX, '@');
  refresh();

     while(1)
      {
        c=getch();
        switch (c) {
        
        case KEY_UP:

            switch( ver=mvinch(posY-1+relative_Y,posX+relative_X)){
            case '!':
              combat();
              break;
            case '?':
              item();
              break;
            case '/':
              //mvaddch(posY, posX, ' ');
              if(!decouverte[posY-1][posX])
              {
                if (porteBloquee(posY-1+relative_Y, posX+relative_X,'h'))
                {
                  posY+=3; relative_Y-=3;
                }

                else createurSalle( map, posY-1, posX, 'h', ++indice); 
              }
              posY-=3; relative_Y+=3;
              //mvaddch(posY, posX, '@');
              break;
            case '#':
              break;


            default: 
              //mvaddch(posY, posX, ' ');
              posY--;
              //mvaddch(--posY, posX, '@');
              relative_Y++;
              break;
        }
          refresh();

        break;

        case KEY_DOWN:

          switch (ver = mvinch(posY+1+relative_Y,posX+relative_X)){
          case '!':
            combat();
            break;
          case '?':
            item();
            break;
          case '/':
            //mvaddch(posY, posX, ' ');
            if(!decouverte[posY+1][posX])
            {
              if (porteBloquee(posY+1+relative_Y, posX+relative_X,'b'))
              {
                posY-=3; relative_Y+=3;
              }

              else createurSalle( map, posY+1, posX, 'b', ++indice);
            }
            posY+=3; relative_Y-=3; 
            //mvaddch(posY, posX, '@');
            break;
          case '#':
            break;
          default :
            //mvaddch(posY, posX, ' ');
            //mvaddch(++posY, posX, '@');
            relative_Y--;
            posY++;
            break;
          }
          refresh();

          break;

          
        case KEY_LEFT:

          switch (ver = mvinch(posY+relative_Y,posX-1+relative_X)){
          case '!':
            combat();
            break;
          case '?':
            item();
            break;
          case '/':
            //mvaddch(posY, posX, ' ');
            if(!decouverte[posY][posX-1])
            {
              if (porteBloquee(posY+relative_Y, posX-1+relative_X,'g'))
              {
                posX+=3;relative_X-=3;
              }

              else createurSalle( map, posY, posX-1, 'g', ++indice); 
            }
            posX-=3; relative_X+=3;
            //mvaddch(posY, posX, '@'); 
            break;
          case '#':
            break;
          default :
            //mvaddch(posY, posX, ' ');
            //mvaddch(posY, --posX, '@');
            relative_X++;
            posX--;
            break;
          }
          refresh();

          break;

        case KEY_RIGHT:
          switch (ver = mvinch(posY+relative_Y,posX+1+relative_X)){
          case '!':
            combat();
            break;
          case '?':
            item();
            break;
          case '/': 
            //mvaddch(posY, posX, ' ');
            if(!decouverte[posY][posX+1])
            {
              if (porteBloquee(posY+relative_Y, posX+1+relative_X,'d'))
              {
                posX-=3; relative_X+=3;
              }
              else createurSalle( map, posY, posX+1, 'd', ++indice); 
            }
            posX+=3; relative_X-=3;
            //mvaddch(posY, posX, '@');
          
            break;
          case '#':
            break;
          default :
            //mvaddch(posY, posX, ' ');
            //mvaddch(posY, ++posX, '@');
            relative_X--;
            posX++;
            break;
          }
         refresh();

          break;    

        default:
          break; }
          mouvementRelatif(map, indice,posY,posX);
           if (c== 'q') break; 

      }

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


//********************** FONCTION MAIN ************************

int main(){
  srand(50); 
  initscr();
  Salle* map=NULL;
  map =createurMap(&nb_salle);


  decouverte = (bool**)malloc(sizeof(bool)*LINES);
  for(int i=0; i<LINES; i++)
  {
    decouverte[i]= (bool*)malloc(sizeof(bool)*COLS);
    for (int j=0; j<= COLS; j++) 
      decouverte[i][j]=0;
  }
  start_color();
  init_pair(1,VIOLET,0);
  init_pair(2,6,0);
  init_color(VIOLET, 250,25,255);
  init_pair(3,7,VIOLET);

  contour();
  //refresh();
  noecho();
  curs_set(0);
  mouvementPerso(map);
  getch();
  free(decouverte);
  free(map);
  endwin();

  return 0;
}
