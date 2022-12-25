#!/bin/bash
if [ -e c.o ] ; then
    echo "le fichier c compilé existe"
else
    echo "le fichier c compilé n'existe pas"
    gcc -o c.o c.c
    if [ -e c.o ] ; then
		echo "l'élément a bien été compiled"
	else
		echo "ba carrément la compilation elle marche pas il se passe des bails sombres avec le gcc"
	fi
fi
./c.o #launch the .c file 
t1=0 ; t2=0 ; t3=0 ; p1=0 ; p2=0 ; p3=0 ; w=0 ; m=0 ; h=0 ; F=0 ; G=0 ; S=0 ; A=0 ; O=0 ; Q=0 ; tab=0 ; abr=0 ; avl=0 ;
var=0
for var in $(seq 1 "$#") ; do
	case "${!var}" in
		# TYPE DE DONNE A ENVOYER AU C
		'-t1') echo "on veut la température" ; t1=1 ;;
		'-t2') echo "on veut la température" ; t2=1 ;;
		'-t3') echo "on veut la température" ; t3=1 ;;
		'-p1') echo "on veut la pression" ; p1=1 ;;
		'-p2') echo "on veut la pression" ; p2=1 ;;
		'-p3') echo "on veut la pression" ; p3=1 ;;
		'-w') echo "on veut le vent" ; w=1 ;;
		'-m') echo "on veut l'humidité" ; m=1 ;;
		'-h') echo "on veut l'altitude" ; h=1 ;;
		# GEOGRAPHIE DES DONNES A FILTRER AVANT D'ENVOYER AU C
		'-F') echo "France métropolitaine" ; F=1 ;;
		'-G') echo "Guyane" ; G=1 ; grep -E '81408|81401|81405|81415'  meteo_filtered_data_v1.csv > guyane.csv ;;
		'-S') echo "Saint-Pierre et Michelin" ; S=1 ; grep 71805 meteo_filtered_data_v1 > saint_pierre.csv ;;
		'-A') echo "Antilles" ; A=1 ; grep -E '78894|78890|78897|78925|78922' meteo_filtered_data_v1 > antilles.csv ;;
		'-O') echo "Ocean indien" ; O=1 ; grep -E '61997|61996|61972|61980|61976|67005|61968' meteo_filtered_data_v1 > ocean_indien.csv ;;
		'-Q') echo "Antarctique" ; Q=1 ; grep -E '89642|61998' meteo_filtered_data_v1 > antarctique.csv ;;
		# TYPE DE TRI DEMANDE 
		'--tab') echo "Le type de tri demandé est par un tableau ou une liste chainée" ; tab=1 ;;
		'--abr') echo "Le type de tri demandé est un abr" ; abr=1 ;;
		'--avl') echo "Le type de tri demandé est un avl" ; avl=1 ;;
		 *  ) echo "l'argument ${!var} n'est pas réferencé" ; exit 0 ;;
	esac
done
