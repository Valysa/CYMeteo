all : myexec

main.o: main.c fonctions.h
	gcc -c $< -o $@ -lcurses
affichage.o: affichage.c fonctions.h
	gcc -c $< -o $@
scores.o: scores.c fonctions.h
	gcc -c $< -o $@
jeu.o: jeu.c fonctions.h
	gcc -c $< -o $@
plateau.o: plateau.c fonctions.h
	gcc -c $< -o $@
pieces.o: pieces.c fonctions.h
	gcc -c $< -o $@
myexec: main.o affichage.o scores.o jeu.o plateau.o pieces.o
	gcc $^ -o $@ -lcurses

