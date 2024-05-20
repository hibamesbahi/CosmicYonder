#include <stdio.h>                //y->largeur   x->longueur
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#define NB_SALLE_MAX 10
#define LONG_MAX 20
#define LARG_MAX 10

// ********************** DECLARATION VARIABLES ************************

//caractères
char mur='#';
char porte='/';
char vide= ' ';
int nb_salle=0;

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

  p_map[0].position.y= rand()%20+5;
  p_map[0].position.x= rand()%20+30;
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


Salle* createurMap(int nb_salle){
  Salle* p_map=NULL;

  //generation procedurale
  //nombre de salle en memoire
    //arrengement des salle depend de la graine et de l'ordre.
  int graine = rand(); //graine temporaire
  nb_salle= 4+(graine%NB_SALLE_MAX);
  p_map=malloc(sizeof(Salle)*nb_salle);  //free a la fin
    if(p_map==NULL)exit(1);
  p_map[0].nb_porte=4;
  p_map[0]=salleSpawn(p_map);
  return p_map;
}

int verifSuperpo(Salle *map, int nb_salle, Salle nouv_salle) {
if(map==NULL)exit  (1); 
    for (int i = 0; i < nb_salle; i++) {
        Salle s = map[i];
        
  bool gauche =(nouv_salle.position.x + nouv_salle.longueur) > s.position.x && (nouv_salle.position.x<s.position.x);//left
  bool droite= nouv_salle.position.x < (s.position.x + s.longueur)&& (nouv_salle.position.x > s.position.x) ; //right
  bool haut=(nouv_salle.position.y + nouv_salle.largeur) > s.position.y && nouv_salle.position.y < s.position.y   ;// top
  bool bas = nouv_salle.position.y < (s.position.y + s.largeur) && (nouv_salle.position.y+nouv_salle.largeur)> s.position.y; //bas
  int superpo1=0;
  int superpo2=0;
    //left and top

  //g nouv_salle.position.x + nouv_salle.longueur - s.position.x;
  //d s.position.x + s.longueur - nouv_salle.position.x;
  //h nouv_salle.position.y + nouv_salle.largeur - s->position.y
  //b s.position.y + s.largeur - nouv_salle.position.y



  if(gauche && haut) {
     superpo1= 1+nouv_salle.position.x + nouv_salle.longueur - s.position.x;
     superpo2= 1+nouv_salle.position.y + nouv_salle.largeur - s.position.y;
     if(superpo1<superpo2){nouv_salle.longueur -= superpo1;}
     else {nouv_salle.largeur -= superpo2;}
  }
  //right and top
  else if(droite && haut) {
      superpo1= 1+s.position.x + s.longueur - nouv_salle.position.x;
      superpo2= 1+nouv_salle.position.y + nouv_salle.largeur - s.position.y;
     if(superpo1<superpo2){
      nouv_salle.position.x += superpo1;
      nouv_salle.longueur-=superpo1;
      }
      else {nouv_salle.largeur -= superpo2;}
      }     


      //left and bottom    
  if(gauche && bas) {
      superpo1= 1+nouv_salle.position.x + nouv_salle.longueur - s.position.x;
      superpo2= 1+s.position.y + s.largeur - nouv_salle.position.y;
     if(superpo1<superpo2){
      nouv_salle.longueur -= superpo1;}
     else {
      nouv_salle.position.y += superpo2;
      nouv_salle.largeur -= superpo2;
          }
    }    

  //right and bottom    
  if(droite && bas) {
      superpo1= 1+s.position.x + s.longueur - nouv_salle.position.x;
      superpo2= 1+s.position.y + s.largeur - nouv_salle.position.y;
     if(superpo1<superpo2){
      nouv_salle.longueur -= superpo1;
      nouv_salle.position.x += superpo1;
      }
     else {
      nouv_salle.position.y += superpo2;
      nouv_salle.largeur-=superpo2;
      }
    }

  else {
      return 0;
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
mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
          mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');
          mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');
          mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');
switch (salle->nb_porte) {
case 1:
  //ne rien faire
  break;

case 2: 
// placer une porte aléatoirement
  indice1= (ind_porte+1+rand()%2)%4 ;  //indice de la porte de passage plus une valeure entre 1 et 3 ;
    switch (indice1){
  case 0: //porte du haut
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;
    mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');

    break;
  case 1: //porte du bas
    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;
    mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');

    break;
  case 2: //porte de gauche
    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');

    break;

  case 3: //porte de droite
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');

    break;
  }
  break;

case 3:
  //faire 2 porte de plus
  indice1= ind_porte +1+rand()%1;
  indice2= indice1+1;
  indice1= (ind_porte+1+rand()%2)%4 ;  //indice de la porte de passage plus une valeure entre 1 et 3 ;
    switch (indice1){
  case 0: //porte du haut
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;

    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;
    mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
    mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');


    break;
  case 1: //porte du bas
    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;
    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');
    mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');


    break;
  case 2: //porte de gauche
    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');
    mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');


    break;

  case 3: //porte de droite
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;
    mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
    mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');



    break;
  }
  break;
case 4 :
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
    mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
    mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');
    mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');



    break;
  case 1: //porte du bas
    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;
    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');
    mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');
    mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');



    break;
  case 2: //porte de gauche
    p_map[num].pos_porte[2].x=salle->position.x;
    p_map[num].pos_porte[2].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;
    mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
    mvaddch(salle->pos_porte[2].y, salle->pos_porte[2].x, '/');
    mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');



    break;

  case 3: //porte de droite
    p_map[num].pos_porte[3].x=salle->position.x+salle->longueur;
    p_map[num].pos_porte[3].y=(rand()%(salle->largeur-2))+salle->position.y+1;
    p_map[num].pos_porte[0].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[0].y=salle->position.y;
    p_map[num].pos_porte[1].x=(rand()%(salle->longueur-2))+salle->position.x+1;
    p_map[num].pos_porte[1].y=salle->position.y+salle->largeur;
    mvaddch(salle->pos_porte[0].y, salle->pos_porte[0].x, '/');
    mvaddch(salle->pos_porte[1].y, salle->pos_porte[1].x, '/');
    mvaddch(salle->pos_porte[3].y, salle->pos_porte[3].x, '/');

    break;
  }
break;  
 default:
 printf("erreur\n");
 break;
}  


}


//************************* createur salle ***********************

//creation des salle au fur et a mesure
void createurSalle(Salle* map, int y, int x, char cote, int indice){
  //creation sur le moment
    //si memoire finie salle sans porte
      //piece ractangulaire, m*n , avec des porte
  //creation salle en memoire, pos porte
  
Salle nouv_salle; 
int ind_porte; 
nouv_salle.nb_porte=(rand()%3)+1;
  
  nouv_salle.longueur=(rand()%LONG_MAX)+3;
  nouv_salle.largeur=(rand()%LARG_MAX)+3;
  Position place_perso;

    switch(cote){
  case 'h': 
      ind_porte=1;
      y--;
      place_perso.x=x;
      place_perso.y=y-1;
      break;
  case 'b': 
      ind_porte=0;
      y++;
      place_perso.x=x;
      place_perso.y=y+1;
      break;
  case 'g': 
      ind_porte=3;
      x--;
      place_perso.x=x-1;
      place_perso.y=y;
      break;
  case 'd': 
      ind_porte=2;
      x++;
      place_perso.x=x+1;
      place_perso.y=y;
      break;
  }
  nouv_salle.pos_porte[ind_porte].x=x;
  nouv_salle.pos_porte[ind_porte].y=y;
  
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


int L=nouv_salle.position.x;  //position de depard du mur
int l=nouv_salle.position.y;
int L_fin=L+nouv_salle.longueur; //position de fin du mur 
int l_fin=l+nouv_salle.largeur;
  //verif superposition

map[indice]=nouv_salle;

verifSuperpo(map, indice, nouv_salle);
  
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

  createurPorte(map, indice, ind_porte);

  mvaddch(y,x,'/');
  mvaddch(place_perso.y,place_perso.x,'@');
  //faire des porte sachant que 1 porte deja faite

  //faire avancer le personnage directe dans la salle, ' ', '/', '/', '@'
  //if superposition, modifier les coord petit a petit (do while) 

}

void checkEmplacement (){


}


void mouvementPerso(Salle *map){

  int c;char ver; int indice=0;
  int posX=map[0].position.x + map[0].longueur/2;
  int posY=map[0].position.y+map[0].largeur/2; //initialisation pos
  keypad(stdscr, TRUE);
  mvaddch(posY, posX, '@');
  refresh();

     while(1)
      {
        c=getch();
        switch (c) {
        
        case KEY_UP:

          if(ver = mvinch(posY-1,posX)=='/'){
            mvaddch(posY, posX, ' ');
            createurSalle( map, posY-1, posX, 'h', indice++); 
            posY-=3;
          }
          else if(mvinch(posY-1,posX)!='#'){
          mvaddch(posY, posX, ' ');
          mvaddch(--posY, posX, '@');}
          refresh();

          break;

        case KEY_DOWN:

          if(ver = mvinch(posY+1,posX)=='/'){
            mvaddch(posY, posX, ' ');
            createurSalle( map, posY+1, posX, 'b', indice++);
            posY+=3; 
          }
          
          else if(ver = mvinch(posY+1,posX)!='#'){
      
          mvaddch(posY, posX, ' ');
          mvaddch(++posY, posX, '@');}
          refresh();

          break;

          
        case KEY_LEFT:

          if(ver = mvinch(posY,posX-1)=='/'){
            mvaddch(posY, posX, ' ');
            createurSalle( map, posY, posX-1, 'g', indice++); 
            posX-=3;
                    }
          else if(mvinch(posY,posX-1)!='#'){
          mvaddch(posY, posX, ' ');
          mvaddch(posY, --posX, '@');}
          refresh();

          break;

        case KEY_RIGHT:

          if(ver = mvinch(posY,posX+1)=='/'){
            mvaddch(posY, posX, ' ');
            createurSalle( map, posY, posX+1, 'd', indice++); 
            posX+=3;
          }
          else if(mvinch(posY,posX+1)!='#'){

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
  srand(time(NULL));
  initscr();
  Salle* map;
  map =createurMap(nb_salle);
  refresh();
  noecho();
  curs_set(0);
  mouvementPerso(map);
  getch();
  endwin();

  return 0;
}
