#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

int main(void)
{
  initscr();   //initialise ecran standard
  noecho();  //enleve l'echo
  curs_set(0);  //rend le curser transpartant 

int c;
int posX=10, posY=20;  //initialise les position
keypad(stdscr, TRUE);   //active les touches fleche



  while(1)
  {c=getch();  //enregistre la touche qu'on a pressé
    switch (c) {   // switch case pour chaque cas, chaque fleche
    case KEY_DOWN:
      mvaddch(posY, posX, ' ');    //renplace la position acctuel par du vide
      mvaddch(++posY, posX, '@');  // deplace le caractere d'une case dans la direction voulue
      refresh();

      break;
//   ON RECOMMENCE POUR CHAQUE DIRECTION
    case KEY_UP:
      mvaddch(posY, posX, ' ');
      mvaddch(--posY, posX, '@');
      refresh();

      break;
      
    case KEY_LEFT:
      mvaddch(posY, posX, ' ');
      mvaddch(posY, --posX, '@');
      refresh();

      break;

    case KEY_RIGHT:
      mvaddch(posY, posX, ' ');
      mvaddch(posY, ++posX, '@');
      refresh();

      break;    

    default: // cas par default ou on ne presse aucune fleche on fait rien 
      break; }
       if (c== 'q') break;  //on quitte le programme 

  }

  endwin();

  return 0;
}
