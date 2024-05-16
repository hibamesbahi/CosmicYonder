void createurSalle(Salle* map, int y, int x,int ind_porte, int indice){//*************************createur salle***********************

	//creation sur le moment
	  //si memoire finie salle sans porte
	    //piece ractangulaire, m*n , avec des porte
	//creation salle en memoire, pos porte
	
Salle nouv_salle;	
pos_porte
int ind_porte;
/*membre de salle: 
  nb_porte; rand ()%3+1
  Position pos_porte[4];
  
  Position position;*/
  
  nouv_salle.longueur=(rand()%LONG_MAX)+3;
  nouv_salle.largeur=(rand()%LARG_MAX)+3;
  nouv_salle.position.x= ;
  nouv_salle.position.y= ;
  	switch(cote){
  	case 'h':	
	  	ind_porte=0;
	  	y--;
	  	break;
 	case 'b':	
	  	ind_porte=1;
	  	y++;
	  	break;
  	case 'g':	
	  	ind_porte=2;
	  	x--;
	  	break;
	case 'd':	
  		ind_porte=3;
  		x++;
  		break;
  }
  pos_porte[ind_porte].x=x;
  pos_porte[ind_porte].y=y;
  nouv_salle.position.x= ;
  nouv_salle.position.y= ;
  
  
	//verif superposition
	//afficher la salle

	//if superposition, modifier les coord petit a petit (do while) 
	



}
