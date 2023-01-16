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

test (){
	if [ $1 -eq 1 ] ; then
		echo "l'argument n'a pas lieu d'être passé plusieurs fois en paramètre"
		return 1
	fi
	return 0
}

testArea (){
	if [ $1 -eq 1 ] ; then
		echo "WOOOOOOO SALE FOU T'A PAS LE DROIT DE DEMANDER PLUSIEURS LOCA DIFFERENTES"
		return 1
	fi
	return 0
}

t1=0 ; t2=0 ; t3=0 ; p1=0 ; p2=0 ; p3=0 ; w=0 ; m=0 ; h=0 ; F=0 ; G=0 ; S=0 ; A=0 ; O=0 ; Q=0 ; tab=0 ; abr=0 ; avl=0 ;
var=0 ; nbExecC=0 ; nbLoca=0;
nameOutpout=data.txt
for var in $(seq 1 "$#") ; do
	case "${!var}" in
		# TYPE DE DONNE A ENVOYER AU C
		'-t1') if test $t1 ; then 
					echo "on veut la température" ; t1=1 ; nbExecC=$((nbExecC+1))
			   fi ;;
		'-t2') if test $t2 ; then 
					echo "on veut la température" ; t2=1 ; nbExecC=$((nbExecC+1)) 
				fi ;;
		'-t3') if test $t3 ; then 
					echo "on veut la température" ; t3=1 ; nbExecC=$((nbExecC+1))
				fi ;;
		'-p1') if test $p1 ; then 
					echo "on veut la pression" ; p1=1 ; nbExecC=$((nbExecC+1)) 
				fi ;;
		'-p2') if test $p2 ; then 
					echo "on veut la pression" ; p2=1 ; nbExecC=$((nbExecC+1)) 
				fi ;;
		'-p3') if test $p3 ; then 
					echo "on veut la pression" ; p3=1 ; nbExecC=$((nbExecC+1)) 
				fi ;;
		'-w') if test $w ; then 
					echo "on veut le vent" ; w=1 ; nbExecC=$((nbExecC+1)) 
				fi ;;
		'-m') if test $m ; then 
					echo "on veut l'humidité" ; m=1 ; nbExecC=$((nbExecC+1)) 
				fi ;;
		'-h') if test $h ; then 
					echo "on veut l'altitude" ; h=1 ; nbExecC=$((nbExecC+1)) 
				fi ;;
		# GEOGRAPHIE DES DONNES A FILTRER AVANT D'ENVOYER AU C
		'-F') if testArea $nbLoca ; then 
				echo "France métropolitaine" ; F=1
			  fi ;;
		'-G') if testArea $nbLoca ; then 
				echo "Guyane" ; G=1 ; grep -E '81408|81401|81405|81415' meteo_filtered_data_v1.csv > area.csv ; nbLoca=$((nbLoca+1)) ; nameOutpout=Guyane.txt
			  fi ;;
		'-S') if testArea $nbLoca ; then 
				echo "Saint-Pierre et Michelin" ; S=1 ; grep "71805" meteo_filtered_data_v1.csv > area.csv ; nbLoca=$((nbLoca+1))  ; nameOutpout=Saint_Pierre_Et_Miquelon.txt
			  fi ;;
		'-A') if testArea $nbLoca ; then 
				echo "Antilles" ; A=1 ; grep -E '78894|78890|78897|78925|78922' meteo_filtered_data_v1.csv > area.csv ; nbLoca=$((nbLoca+1)) ; nameOutpout=Antilles.txt
			  fi ;;
		'-O') if testArea $nbLoca ; then 
				echo "Ocean indien" ; O=1 ; grep -E '61997|61996|61972|61980|61976|67005|61968' meteo_filtered_data_v1.csv > area.csv ; nbLoca=$((nbLoca+1)) ; nameOutpout=Ocean_Indien.txt
			  fi ;;
		'-Q') if testArea $nbLoca ; then 
				echo "Antarctique" ; Q=1 ; grep -E '89642|61998' meteo_filtered_data_v1.csv > area.csv ; nbLoca=$((nbLoca+1)) ; nameOutpout=Antarctique.txt
			  fi ;;
		# TYPE DE TRI DEMANDE
		'--tab') echo "Le type de tri demandé est par un tableau ou une liste chainée" ; tab=1 ;;
		'--abr') echo "Le type de tri demandé est un abr" ; abr=1 ;;
		'--avl') echo "Le type de tri demandé est un avl" ; avl=1 ;;
		# HELP
		'-help') echo "help à écrire ptdr" ; exit 1 ;;
		# CAS GENERAL
		*  ) echo "l'argument ${!var} n'est pas réferencé" ; exit 0 ;;
	esac
done
if [ "$nbExecC" -eq 0 ] ; then
	echo "vous devez spécifier au moins un type de donnée a traiter, si vous ne savez pas de quoi il s'agit, tapez l'argument -help"
	exit 1
fi
var=$(($tab+$abr+$avl))
echo $var
echo $nbExecC
echo $t1
if [ "$var" -ge 2 ]; then
	echo "vous ne pouvez pas demander plus d'une restriction géographique"
	exit 1
fi
if [ "$var" -eq 0 ]; then
	echo "il n'y a pas de manière de trier demandé, le choix par défaut est donc l'avl"
	avl=1
fi
mode=0
if [ "$tab" -eq 1 ] ; then
	mode=tab
fi
if [ "$abr" -eq 1 ] ; then
	mode=abr
fi
if [ "$avl" -eq 1 ] ; then
	mode=avl
fi
echo $mode
echo $nameOutpout
for var in nbExecC ; do
	if [ "$t1" -eq 1 ] ; then
		cut -d ';' -f 1,11 --output-delimiter=';' area.csv > $nameOutpout ;
		echo "test"
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -t --$mode
	fi
	if [ "$t2" -eq 1 ]; then
		cut -d ';' -f 1,11 --output-delimiter=';' area.csv > $nameOutpout ;
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -t2 --$mode
	fi
	if [ "$t3" -eq 1 ]; then
		cut -d ';' -f 1,11 --output-delimiter=';' area.csv > $nameOutpout ;
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -t3 --$mode
	fi
	if [ "$p1" -eq 1 ]; then
		cut -d ';' -f 1,7 --output-delimiter=';' area.csv > $nameOutpout ;
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -p1 --$mode
	fi
	if [ "$p2" -eq 1 ]; then
		cut -d ';' -f 1,3,7,8 --output-delimiter=';' area.csv > $nameOutpout ;
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -p2 --$mode
	fi
	if [ "$t3" -eq 1 ]; then
		cut -d ';' -f 1,3,7,8 --output-delimiter=';' area.csv > $nameOutpout ;
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -p3 --$mode
	fi
	if [ "$w" -eq 1 ]; then
		cut -d ';' -f 1,4,5 --output-delimiter=';' area.csv > $nameOutpout ;
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -w --$mode
	fi
	if [ "$m" -eq 1 ]; then
		cut -d ';' -f 1,6 --output-delimiter=';' area.csv > $nameOutpout ;
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -m --$mode
	fi
	if [ "$h" -eq 1 ]; then
		cut -d ';' -f 1,14 --output-delimiter=';' area.csv > $nameOutpout ;
		./c.o -f<$nameOutpout> -o<tutedebrouille.txt> -h --$mode
	fi
done
