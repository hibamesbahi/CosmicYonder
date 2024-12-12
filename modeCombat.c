#include <ncurses.h>
#include <stdbool.h>
#include "declaration.h"

extern bool** decouverte;

  

  //Fonction Combat
  int combat() {
      //initscr();
      clear();
      noecho();
      cbreak();
      curs_set(0);
      nodelay(stdscr, 1);
      keypad(stdscr, 1);

      Joueur joueur;
      Monstre_combat monstre;
      Attaque attaque = {0};

      init_jeu(&joueur, &monstre, &attaque);

      int c;
      while (1) {
          c = getch();
          if (c == 'q') break;

          if (c == KEY_LEFT) {
              joueur.pos_joueur.x--;
          } else if (c == KEY_RIGHT) {
              joueur.pos_joueur.x++;
          } else if (c == ' ') {
              if (!attaque.active) {
                  attaque.active = 1;
                  attaque.pos_atq.x = joueur.pos_joueur.x;
                  attaque.pos_atq.y = joueur.pos_joueur.y - 1;
              }
          }

          maj_attaque(&attaque);
          maj_monstre(&monstre);
          verif_collision(joueur, &monstre, &attaque);
          //dessin_jeu(joueur, monstre, attaque);

          if (monstre.vie <= 0) {
              
            return 1;
              
              break;
          }

          if (monstre.pos_monstre.y >= LINES/2) {
              
              return 0;
              break;
          }

          
          dessin_jeu(joueur, monstre, attaque);
          napms(50);

      }

      //endwin();
  }

  void init_jeu(Joueur *joueur, Monstre_combat *monstre, Attaque *attaque) {
      joueur->pos_joueur.x = COLS / 2;
      joueur->pos_joueur.y = LINES/2;
      joueur->attaque = 1;

      monstre->pos_monstre.x = COLS / 2;
      monstre->pos_monstre.y = 0;
      monstre->vie = 5; //Définis la barre de vie du monstre à 5
      monstre->attaque = 1;

      attaque->active = 0;
      barre_vie(*monstre);
  }
// Fonction pour gérer les affichages du jeu

  void dessin_jeu(Joueur joueur, Monstre_combat monstre, Attaque attaque) {
      for (int a = 0; a < LINES-10; a++)
      {
        for (int b = 0; b <= COLS; b++)
        {
          mvaddch(a,b,' ');
        }
      } //a la place de clear
      mvprintw(joueur.pos_joueur.y, joueur.pos_joueur.x, "@");
      mvprintw(monstre.pos_monstre.y, monstre.pos_monstre.x, "==MONSTRE==");
      if (attaque.active) {
          mvprintw(attaque.pos_atq.y, attaque.pos_atq.x, "°");
      }
   
    //barre_vie(monstre);
   
      refresh();
  }
//Affiche la barre de vie du monstre

void barre_vie(Monstre_combat monstre){
  mvprintw(LINES-10,1, "         Barre de vie du monstre:");
  for (int i = 0; i < monstre.vie; i++){
    mvaddch(LINES-10,1+i,'*'); //Pour chaque point de vie du monstre on a un "*"
    refresh();
  }

mvprintw(LINES-8, 5 ,"    __  ___          __        ______                __          __ ");
mvprintw(LINES-7, 5 ,"   /  |/  /___  ____/ /__     / ____/___  ____ ___  / /_  ____ _/ /_");
mvprintw(LINES-6, 5 ,"  / /|_/ / __ \\/ __  / _ \\   / /   / __ \\/ __ `__ \\/ __ \\/ __ `/ __/");
mvprintw(LINES-5, 5 ," / /  / / /_/ / /_/ /  __/  / /___/ /_/ / / / / / / /_/ / /_/ / /_  ");
mvprintw(LINES-4, 5 ,"/_/  /_/\\____/\\__,_/\\___/   \\____/\\____/_/ /_/ /_/_.___/\\__,_/\\__/  ");
    refresh();  
}

//Fonction pour gérer les attaques
  void maj_attaque(Attaque *attaque) {
      if (attaque->active) {
          attaque->pos_atq.y--;
          if (attaque->pos_atq.y < 0) {
              attaque->active = 0;
          }
      }
  }

//Fonction pour gérer le monstre
  void maj_monstre(Monstre_combat *monstre) {
      static int direction = 1;
      monstre->pos_monstre.x += direction;
      if (monstre->pos_monstre.x <= 0 || monstre->pos_monstre.x >= COLS - 11) {
          direction = -direction;
          monstre->pos_monstre.y++;
      }
  }

//Fonction pour gérer la collision entre les attaques et le monstre retirer les pts de vie au monstre

  void verif_collision(Joueur joueur, Monstre_combat *monstre, Attaque *attaque) {
    bool colisionX= attaque->pos_atq.x >= monstre->pos_monstre.x && attaque->pos_atq.x <= monstre->pos_monstre.x+10;
    bool colisionY= attaque->pos_atq.y == monstre->pos_monstre.y;
      if (attaque->active && colisionY && colisionX) {
          monstre->vie--;
          attaque->active = 0;
          barre_vie(*monstre);
          refresh();

      }
  }

/*int main() {
    combat();
    return 0;
}*/
