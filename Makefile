roguelike :	main.o map.o mouvement.o salle.o combat.o niveau.o lecture.o Menu.o
	gcc -o roguelike main.o map.o mouvement.o salle.o combat.o niveau.o lecture.o Menu.o -lncurses -Wall -Werror -Wextra -pedantic -std=gnu89


main.o : main.c
	gcc -o main.o -c main.c -lncurses
map.o : createurMap.c
	gcc -o map.o -c createurMap.c -lncurses
mouvement.o : mouvementPerso.c
	gcc -o mouvement.o -c mouvementPerso.c -lncurses
salle.o : createurSalle.c
	gcc -o salle.o -c createurSalle.c -lncurses
combat.o : modeCombat.c
	gcc -o combat.o -c modeCombat.c -lncurses
niveau.o : niveau.c
	gcc -o niveau.o -c niveau.c -lncurses	
lecture.o : lecture.c
	gcc -o lecture.o -c lecture.c -lncurses	
Menu.o : Menu.c
	gcc -o Menu.o -c Menu.c -lncurses

