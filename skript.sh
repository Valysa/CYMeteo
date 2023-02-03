#!/bin/bash
if [ -e c ] ; then
    echo "le fichier c compilé existe"
else
    echo "le fichier c compilé n'existe pas"
    gcc -o c c.c
    if [ -e c ] ; then
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

t1=0 ; t2=0 ; t3=0 ; p1=0 ; p2=0 ; p3=0 ; w=0 ; m=0 ; h=0 ; F=0 ; G=0 ; S=0 ; A=0 ; O=0 ; Q=0 ; tab=0 ; abr=0 ; avl=0 ; d=0; t=0; file=0; f=0;
var=0 ; nbExecC=0 ; nbLoca=0; nbarg=0; sday=0 ; smonth=0 ; syear=0 ; eday=0; emonth=0; eyear=0; sdate=0; edate=0; a=0; g=0; slong=0 ; slat=0; elong=0 ; elat=0 ;
nameOutpout=data.txt
for var in $(seq 1 "$#") ; do
	nbarg=$var
	case "${!var}" in
		#FICHIER D'ENTREE
		'-f') if [ "$f" -eq "0" ] ; then 
				nbarg=$((nbarg+1)) ; f=1 ;
				if [ -e ${!nbarg} ] ; then
					file=${!nbarg}
				else
					echo "the file you put in entry does not exist or isnt valid"
					exit;
				fi
			else
				if [ -e meteo_filtered_data_v1.csv ] ; then
					echo "you didn't select a file but meteo_filtered_data_v1.csv looks valid, we are using it"
					file=meteo_filtered_data_v1.csv
				else
					echo "you need to specify a valid file with -f, --help for help"
					exit 1
				fi
			fi ;;
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
		# RECUPERATION DES DONNEES GEOGRAPHIQUES
		'-F') if testArea $nbLoca ; then 
				echo "France métropolitaine" ; F=1 ;  nameOutpout=France.txt 
			  fi ;;
		'-G') if testArea $nbLoca ; then 
				echo "Guyane" ; G=1 ;  nameOutpout=Guyane.txt
			  fi ;;
		'-S') if testArea $nbLoca ; then 
				echo "Saint-Pierre et Michelin" ; S=1 ;  nbLoca=$((nbLoca+1))  ;   nameOutpout=Saint_Pierre_Et_Miquelon.txt
			  fi ;;
		'-A') if testArea $nbLoca ; then 
				echo "Antilles" ; A=1 ; nbLoca=$((nbLoca+1)) ;  nameOutpout=Antilles.txt
			  fi ;;
		'-O') if testArea $nbLoca ; then 
				echo "Ocean indien" ; O=1 ; nbLoca=$((nbLoca+1)) ;  nameOutpout=Ocean_Indien.txt
			  fi ;;
		'-Q') if testArea $nbLoca ; then 
				echo "Antarctique" ; Q=1 ;  nameOutpout=Antarctique.txt
			  fi ;;
		'-g') if [ "$g" -eq "0" ] ; then 
				nbarg=$((nbarg+1)) ; g=1 ;
				slong=${!nbarg} ; nbarg=$((nbarg+1)) ; elong=${!nbarg} ;
			  else
			  	echo can t put that many restriction for more info type --help
				exit 1
			  fi ;;
		'-a') if [ "$a" -eq "0" ] ; then 
				nbarg=$((nbarg+1)) ; a=1 ;
				slat=${!nbarg} ; nbarg=$((nbarg+1)) ; elat=${!nbarg} ;
			  else
			  	echo can t put that many restriction for more info type --help
				exit 1
			  fi ;;
		# RECUPERATION DE LA RESTRICTION TEMPORELLE
		'-d') nbarg=$((nbarg+1)) ; d=1;
			syear=${!nbarg::4} ; smonth=${!nbarg:5:2} ; sday=${!nbarg:8:2} ; sdate=${!nbarg}T00:00:00+01:00 ;
			nbarg=$((nbarg+1)) ;
			eyear=${!nbarg::4} ; emonth=${!nbarg:5:2} ; eday=${!nbarg:8:2} ; edate=${!nbarg}T23:00:00+01:00 ;;
			[0123456789][0123456789][0123456789][0123456789]-[0123456789][0123456789]-[0123456789][0123456789]) ;;
		# TYPE DE TRI DEMANDE
		'--tab') echo "Le type de tri demandé est par un tableau ou une liste chainée" ; tab=1 ;;
		'--abr') echo "Le type de tri demandé est un abr" ; abr=1 ;;
		'--avl') echo "Le type de tri demandé est un avl" ; avl=1 ;;
		# HELP
		'-help') echo "help à écrire ptdr" ; exit 1 ;;
		# CAS GENERAL
	 	#*  ) echo "l'argument ${!var} n'est pas réferencé" ; exit 0 ;;
	esac
done
if [ "$f" -eq 0 ] ; then
	echo " -f must be specified --help for more info"
	exit 1
fi
dayTest (){ # month day year
	if [ $1 -eq "2" ] ; then #fevrier cas
		if [ $3 -eq "2012" ] || [ $3 -eq "2016" ] || [ $3 -eq "2020" ] ; then # bissextiles years
			if [ $2 -gt "29" ] ; then
				echo "Year entered is not valid --help for more informations"
				exit 1
			fi
		else # non bissextile year
			if [ $2 -gt "28" ] ; then
				echo "Date entered is not valid --help for more informations"
				exit 1
			fi
		fi
	fi
	if [ $1 -eq "1" ] || [ $1 -eq "3" ] || [ $1 -eq "3" ] || [ $1 -eq "5" ] || [ $1 -eq "7" ] || [ $1 -eq "8" ] || [ $1 -eq "10" ] || [ $1 -eq "12" ] ; then #31 days months
		if [ $2 -gt "31" ] ; then
			echo "Date entered is not valid --help for more informations"
			exit 1
		fi
	else # month with 30 days
		if [ $2 -gt "30" ] ; then
			echo "Date entered is not valid --help for more informations"
			exit 1
		fi
	fi
	return 0;
}
dateTest (){ #year month day
	if [ "$1" -ge "2010" ] && [ "$1" -le "2022" ] ; then
		# echo valid year
		if [ "$2" -ge "0" ] && [ "$2" -le "12" ] ; then
			# echo valid month
			if dayTest $2 $3 $1 && [ "$3" -ge "0" ] ; then
				# echo valid day
				return 0
			fi
		fi
	fi
return 1
}
if [ "$d" -eq "1" ] ; then
	if dateTest $syear $smonth $sday && dateTest $eyear $emonth $eday ; then
		if [ $(date -d "$sdate" +%s) -lt $(date -d "$edate" +%s) ]; then
			awk -F ";" -v start="$sdate" -v end="$edate" '$2 >= start && $2 <= end {print $0}' $file > area.csv
		else 
			echo date one is greater than date two
			exit 1
		fi
	else
		echo "invalid dates, see --help for help"
		exit 1
	fi
else
	cat $file > area.csv
fi
if [ "$F" -eq 1 ] ; then
	grep -E '81408|81401|81405|81415|71805|78894|78890|78897|78925|78922|61997|61996|61972|61980|61976|67005|61968|89642|61998|61970' -v  area.csv > area_time.csv ; nbLoa=$((nbLoca+1)) ;
fi
if [ "$G" -eq 1 ] ; then
	grep -E '81408|81401|81405|81415' area.csv > area_time.csv ; nbLoca=$((nbLoca+1)) ;
fi
if [ "$S" -eq 1 ] ; then
	grep "71805" area.csv > area_time.csv ;
fi
if [ "$A" -eq 1 ] ; then
	grep -E '78894|78890|78897|78925|78922' area.csv > area_time.csv ;
fi
if [ "$O" -eq 1 ] ; then
	grep -E '61998|61997|61996|61972|61980|61976|67005|61968|61970' area.csv > area_time.csv ;
fi
if [ "$Q" -eq 1 ] ; then
	grep -E "89642" area.csv > area_time.csv ; nbLoca=$((nbLoca+1)) ;
fi
if [ "$nbExecC" -eq 0 ] ; then
	echo "vous devez spécifier au moins un type de donnée a traiter, si vous ne savez pas de quoi il s'agit, tapez l'argument -help"
	exit 1
fi
if [ "$a" -eq "1" ] && [ "$g" -eq "1" ] ; then
awk -F ';' '$10 >= slat && $10 <= elat && $11 >= slong && $11 <= elong { print }' slat="$slat" elat="$elat" slong="$slong" elong="$elong" area_time.csv > finale.txt
else
	cat area_time.csv > finale.txt
fi
rm area.csv
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
# echo $nameOutpout
for var in nbExecC ; do
	if [ "$t1" -eq 1 ] ; then
		cut -d ';' -f 1,11 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -t1 --$mode
		gnuplot -persist t1.plt
	fi
	if [ "$t2" -eq 1 ]; then
		cut -d ';' -f 11,2 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr -d '-' |  tr -d '+' | sed 's/\([0-9]\{8\}\)T.*;/\1;/g' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -t2 --$mode
		gnuplot -persist t2.plt
	fi
	if [ "$t3" -eq 1 ]; then
		cut -d ';' -f 1,11 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -t3 --$mode
	fi
	if [ "$p1" -eq 1 ]; then
		cut -d ';' -f 1,7 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -p1 --$mode
		gnuplot -persist t1.plt
	fi
	if [ "$p2" -eq 1 ]; then
		cut -d ';' -f 7,2 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr -d '-' |  tr -d '+' | sed 's/\([0-9]\{8\}\)T.*;/\1;/g' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -p2 --$mode
		gnuplot -persist t2.plt
	fi
	if [ "$p3" -eq 1 ]; then
		cut -d ';' -f 1,7 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -p3 --$mode
	fi
	if [ "$w" -eq 1 ]; then
		cut -d ';' -f 1,4,5,10 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr ',' ';' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -w --$mode
		gnuplot -persist w.plt
	fi
	if [ "$m" -eq 1 ]; then
		cut -d ';' -f 1,6,10 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr ',' ';' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -m --$mode
		gnuplot -persist h.plt
	fi
	if [ "$h" -eq 1 ]; then
		cut -d ';' -f 1,14,10 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr ',' ';' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -h --$mode
		gnuplot -persist h.plt
	fi
done
