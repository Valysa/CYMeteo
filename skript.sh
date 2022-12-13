#!/bin/bash
if [ -e c.o ] ; then
    echo "c'est good"
else
    echo "c'est pas good"
    gcc -o c.o c.c
    if [ -e c.o ] ; then
		echo "l'élément a bien été compiled"
	else
		echo "ba carrément la compilation elle marche pas il se passe des bails sombres avec le gcc"
	fi
fi
./c.o #launch the .c file 
var=0
for var in $(seq 1 "$#") ; do
	case "${!var}" in
		# TYPE DE DONNE A ENVOYER AU C
		'-t') echo "on veut la température" ;;
		'-p') echo "on veut la pression" ;;
		'-w') echo "on veut le vent" ;;
		'-m') echo "on veut l'humidité";;
		'-h') echo "on veut l'altitude";;
		# GEOGRAPHIE DES DONNES A FILTRER AVANT D'ENVOYER AU C
		'-F') echo "France métropolitaine";;
		'-G') echo "Guyane" ;; 
		'-S') echo "Saint-Pierre et Michelin" ;;
		'-A') echo "Antilles" ;;
		'-O') echo "Ocean indien" ;;
		'-Q') echo "Antartique" ;;
	  *   ) echo "aller vasy ça marche pas" ; exit 0 ;;
	esac
done

