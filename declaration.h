#ifndef DECLARATION_H
#define DECLARATION_H

#define NB_SALLE_MAX 3
#define LONG_MAX 20
#define LARG_MAX 7
#define VIOLET 10

// ********************** DECLARATION VARIABLES ************************
 
//caractères
extern const char mur;
extern const char porte;
extern const char vide;
extern int nb_salle;
extern int compteur_porte;
extern int relative_X;
extern int relative_Y;
extern int graine;
extern int posY;
extern int posX;
extern int experience;
extern clock_t temps;
extern char nom[16];
extern int indice;
extern clock_t debut;
extern clock_t fin;




   // Definir Position
typedef struct Position{
      int x;
      int y;
  } Position;

//structure Salle
typedef struct Salle {
  int nb_porte;
  int nombreItems;
  int longueur;
  int largeur; 
  Position position;
  Position pos_porte[4];
  Position items[3];

}Salle ;


typedef struct monstre {
Position position;
bool existe;

} Monstre;


extern bool **decouverte;
extern Monstre monstre;


  // Definir Monstre mode combat
typedef struct Monstre_combat{
      Position pos_monstre;
      int vie;
      int attaque;
  } Monstre_combat;

  // Definir Joueur
typedef struct Joueur{
      Position pos_joueur;
      int attaque;
  } Joueur;

  // Definir les attaques du joueur
typedef struct Attaque{
      Position pos_atq;
      int active;
  } Attaque;

typedef struct Item{
  Position position;

}Item;

//map
	Salle salleSpawn(Salle* p_map);
	Salle* createurMap(int *nb_salle);
	void contour();

//mouvement
	void mouvementPerso(Salle *map);
	void mouvementRelatif(Salle *map, int indice, int posY, int posX);
	void sauvegarde (Salle* map, int indice);


//salle
	void createurSalle(Salle* map, int y, int x, char cote, int indice);
	void verifSuperpo(Salle *map, int nb_salle, Salle* nouv_salle,char cote);
	void createurPorte(Salle *p_map, int num, int ind_porte);
	int porteBloquee(int y,int x,char cote);
	void item(void);
	void genererItems(Salle* salle);



//mode combat
  int combat();
  void init_jeu(Joueur *joueur, Monstre_combat *monstre, Attaque *attaque);
  void dessin_jeu(Joueur joueur, Monstre_combat monstre, Attaque attaque);
  void maj_attaque(Attaque *attaque);
  void maj_monstre(Monstre_combat *monstre);
  void verif_collision(Joueur joueur, Monstre_combat *monstre, Attaque *attaque);
  void barre_vie(Monstre_combat monstre);
  
//niveaux
extern int niveau;
	void niveau1(int mode);
	void niveau2(int mode);
	void niveau3(int mode);
	void niveau4(int mode);
	void niveau5(int mode);
	void intiVariable();


//lecture
	void afficherIntro();	

	void afficherDefaite();
	
	void afficherVictoire();

	void afficherRestorer();

	void afficherTexte(const char* fichier);

//Menu


void NouvellePartie();
void AnciennePartie();
void Menu();
void sauvegarde(Salle *map, int indice);
void restorer(char *nom);


#endif
