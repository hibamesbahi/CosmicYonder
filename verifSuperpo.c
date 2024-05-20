#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

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
      return 0; // Pas de collision
        }
}
}


//segmentation fault probleme réglé
