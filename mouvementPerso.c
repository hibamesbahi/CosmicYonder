#include <stdio.h>                //y->largeur   x->longueur
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include <stdbool.h>
#include "declaration.h"

/*extern bool** decouverte;

extern Monstre monstre;
extern int relative_X;
extern int relative_Y;
extern Salle* map;*/


//mouvement Personnage ********************


void mouvementPerso(Salle *map){
  int resultat=0;
  int c;char ver; int indice=0;
  int posX=map[0].position.x + map[0].longueur/2;
  int posY=map[0].position.y-2+map[0].largeur/2; //initialisation position de depart
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
              resultat=combat();
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
              relative_Y++;getch();
              break;
        }
          refresh();

        break;

        case KEY_DOWN:

          switch (ver = mvinch(posY+1+relative_Y,posX+relative_X)){
          case '!':
            resultat=combat();
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
            resultat=combat();
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
            resultat=combat();
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
          mouvementRelatif(map, indice,posY,posX); // le segmentation viens de cette fonction !
          if (c== 'q') break; 

      } if (resultat==1)
        {
          return ; //retour 

        }

}

//dessiner Salle **************************
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
      mvprintw(LINES, 23 , "_________                      .__         _____.___.                  .___            ");
      mvprintw(LINES-7, 23 , "\\_   ___ \\  ____  ______ _____ |__| ____   \\__  |   | ____   ____    __| _/___________ ");
      mvprintw(LINES-6, 23 , "/    \\  \\/ /  _ \\/  ___//     \\|  |/ ___\\   /   |   |/  _ \\ /    \\  / __ |/ __ \\_  __ \\");
      mvprintw(LINES-5, 23 , "\\     \\___(  <_> )___ \\|  Y Y  \\  \\  \\___   \\____   (  <_> )   |  \\/ /_/ \\  ___/|  | \\/");
      mvprintw(LINES-4, 23 , " \\______  /\\____/____  >__|_|  /__|\\___  >  / ______|\\____/|___|  /\\____ |\\___  >__|   ");
      mvprintw(LINES-3, 23 , "        \\/           \\/      \\/        \\/   \\/                  \\/      \\/    \\/       ");
   attroff(COLOR_PAIR(3));


}
