#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>



int verifSuperpo(Salle *p_map, int nb_salle, Salle nouv_salle, Salle **salle_en_collision1, Salle **salle_en_collision2) {
    for (int i = 0; i < nb_salle; i++) {
        Salle s = p_map[i];
        if (!(nouv_salle.position.x + nouv_salle.longueur < s.position.x ||
              nouv_salle.position.x > s.position.x + s.longueur ||
              nouv_salle.position.y + nouv_salle.largeur < s.position.y ||
              nouv_salle.position.y > s.position.y + s.largeur)) {
                       *salle_en_collision1 = &s;   //s=p_map[i]=*(p_map+i)
                       *salle_en_collision2 = &new_salle;
                       return 1; // Collision détectée
        }
    }
    *salle_en_collision1= NULL;
    *salle_en_collision2=NULL;
    return 0; // Pas de collision
