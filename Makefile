roguelike :	main.o map.o mouvement.o salle.o combat.o
	gcc -o roguelike main.o map.o mouvement.o salle.o combat.o -lncurses -Wall -Werror -Wextra -pedantic -std=gnu89


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
