#!/bin/bash
if [ -e c ] ; then
   # echo "le fichier c compilé existe"
   echo Starting Program
else
   # echo "le fichier c compilé n'existe pas"
    gcc -o c c.c
    if [ -e c ] ; then
	#	echo "l'élément a bien été compiled"
	echo Starting Program
	else
	#	echo "ba carrément la compilation elle marche pas il se passe des bails sombres avec le gcc"
	exit 1
	fi
fi

test (){
	if [ $1 -eq 1 ] ; then
		echo "Why would you ask for $1 many times ? Type --help for more info"
		exit 1
	fi
	return 0
}

testArea (){
	if [ $1 -eq 1 ] ; then
		echo "Unfortunatly, you can't ask for many geographics restrictions at once. Type --help for more info"
		exit 1
	fi
	return 0
}

help (){
	echo "To make the programm works you will need to specify somme arguments
You do not need to write them in a very specific order they just need to 
be put in the command after the ./skript.sh
Here is a list of the argument

  Geographic restriction :
    -F : for metropolitain France
    -G : for Guyane
    -S : for Saint-Pierre et Miquelon
    -A : for Antilles
    -O : for Indian Ocean
    -Q : for Antarctique
  If you have data coming from another country it should work
  unless the station IDE are not in the 71000 format.
  If you want all of your data or if you have data from another country, don't specify
  this argument
  Note that you can't many Geographic at once 
  (for example you can't ask for data in Antarctique and in Guyane simultaneously)
  
  Time restriction :
    -d <YYYY-DD-MM> <YYYY-DD-MM>
   Note that there is actually no '<>'
   The data will be restricted to only data between thoose two dates
   It will send an error if The first one is greater than the second one
   
   Sort mode :
    --avl : to sort in an avl
    --abr : to sort in an abr
    --tab : to sort in a tab
   This refere to the sort in the C programm
   
   Your data
    -f <fileName.csv> : to specify the data you want to use
   Note that it can be a .txt or basically everything you want
   Just make sure that you have the rights on tis file, because if not it may send an error
   
   Help 
     --help : to display this section
   
   Type of data :
    -t : for temperatures
    -p : for pression
    -w : for wind
    -m : for moisture
    -h : for heigt
   For temperature you will need to specify the mode, modes are :
    1 : min max and average per station
    2 : average per day
    3 : average per day per station
   So for example if you want the temperature in mode one, enter the argument -t1"
} 
t1=0 ; t2=0 ; t3=0 ; p1=0 ; p2=0 ; p3=0 ; w=0 ; m=0 ; h=0 ; F=0 ; G=0 ; S=0 ; A=0 ; O=0 ; Q=0 ; tab=0 ; abr=0 ; avl=0 ; d=0; t=0; file=0; f=0; skip=0;
var=0 ; nbExecC=0 ; nbLoca=0; nbarg=0; sday=0 ; smonth=0 ; syear=0 ; eday=0; emonth=0; eyear=0; sdate=0; edate=0; a=0; g=0; slong=0 ; slat=0; elong=0 ; elat=0 ;
nameOutpout=data.txt
for var in $(seq 1 "$#") ; do
	nbarg=$var
	if [ "$skip" -gt 0 ] ; then
		skip=$((skip-1))
	else  
		case "${!var}" in
			#FICHIER D'ENTREE
			'-f') if [ "$f" -eq "0" ] ; then 
					skip=$((skip+1)) ;
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
					#	echo "on veut la température" ;
						 t1=1 ; nbExecC=$((nbExecC+1))
				fi ;;
			'-t2') if test $t2 ; then 
					#	echo "on veut la température" ; 
						t2=1 ; nbExecC=$((nbExecC+1)) 
					fi ;;
			'-t3') if test $t3 ; then 
					#	echo "on veut la température" ; 
						t3=1 ; nbExecC=$((nbExecC+1))
					fi ;;
			'-p1') if test $p1 ; then 
					#	echo "on veut la pression" ; 
						p1=1 ; nbExecC=$((nbExecC+1)) 
					fi ;;
			'-p2') if test $p2 ; then 
					#	echo "on veut la pression" ; 
						p2=1 ; nbExecC=$((nbExecC+1)) 
					fi ;;
			'-p3') if test $p3 ; then 
					#	echo "on veut la pression" ; 
						p3=1 ; nbExecC=$((nbExecC+1)) 
					fi ;;
			'-w') if test $w ; then 
					#	echo "on veut le vent" ; 
						w=1 ; nbExecC=$((nbExecC+1)) 
					fi ;;
			'-m') if test $m ; then 
					#	echo "on veut l'humidité" ; 
						m=1 ; nbExecC=$((nbExecC+1)) 
					fi ;;
			'-h') if test $h ; then 
					#	echo "on veut l'altitude" ; 
						h=1 ; nbExecC=$((nbExecC+1)) 
					fi ;;
			# RECUPERATION DES DONNEES GEOGRAPHIQUES
			'-F') if testArea $nbLoca ; then 
				#	echo "France métropolitaine" ; 
					F=1 ;  nbLoca=$((nbLoca+1)) ; nameOutpout=France.txt 
				fi ;;
			'-G') if testArea $nbLoca ; then 
				#	echo "Guyane" ; 
					G=1 ;  nbLoca=$((nbLoca+1)) ;nameOutpout=Guyane.txt
				fi ;;
			'-S') if testArea $nbLoca ; then 
				#	echo "Saint-Pierre et Michelin" ; 
					S=1 ;  nbLoca=$((nbLoca+1))  ;   nameOutpout=Saint_Pierre_Et_Miquelon.txt
				fi ;;
			'-A') if testArea $nbLoca ; then 
				#	echo "Antilles" ; 
					A=1 ; nbLoca=$((nbLoca+1)) ;  nameOutpout=Antilles.txt
				fi ;;
			'-O') if testArea $nbLoca ; then 
				#	echo "Ocean indien" ; 
					O=1 ; nbLoca=$((nbLoca+1)) ;  nameOutpout=Ocean_Indien.txt
				fi ;;
			'-Q') if testArea $nbLoca ; then 
				#	echo "Antarctique" ; 
					Q=1 ;  nbLoca=$((nbLoca+1)) ; nameOutpout=Antarctique.txt
				fi ;;
			'-g') if [ "$g" -eq "0" ] ; then 
					skip=$((skip+1))
					nbarg=$((nbarg+1)) ; g=1 ;
					slong=${!nbarg} ; nbarg=$((nbarg+1)) ; skip=$((skip+1)) ; elong=${!nbarg} ;
				else
					echo can t put that many restriction for more info type --help
					exit 1
				fi ;;
			'-a') if [ "$a" -eq "0" ] ; then 
				skip=$((skip+1)) ;
					nbarg=$((nbarg+1)) ; a=1 ;
					slat=${!nbarg} ; nbarg=$((nbarg+1)) ; skip=$((skip+1)) ; elat=${!nbarg} ;
				else
					echo "can t put that many restriction for more info type --help"
					exit 1
				fi ;;
			# RECUPERATION DE LA RESTRICTION TEMPORELLE
			'-d') nbarg=$((nbarg+1)) ; d=1;
				skip=$((skip+1))
				syear=${!nbarg::4} ; smonth=${!nbarg:5:2} ; sday=${!nbarg:8:2} ; sdate=${!nbarg}T00:00:00+01:00 ;
				nbarg=$((nbarg+1)) ;
				skip=$((skip+1))
				eyear=${!nbarg::4} ; emonth=${!nbarg:5:2} ; eday=${!nbarg:8:2} ; edate=${!nbarg}T23:00:00+01:00 ;;
			# TYPE DE TRI DEMANDE
			'--tab') if [ "$tab" -eq 0 ] || [ "$abr" -eq 0 ] || [ "$avl" -eq 0 ] ; then 
						 tab=1 
					else	
						echo "You can't ask for many type of sorting simulteanously, type --help for more info"
					fi ;;
			'--abr') if [ "$tab" -eq 0 ] || [ "$abr" -eq 0 ] || [ "$avl" -eq 0 ] ; then 
						 abr=1 
					else	
						echo "You can't ask for many type of sorting simulteanously, type --help for more info"
					fi ;;
			'--avl') if [ "$tab" -eq 0 ] || [ "$abr" -eq 0 ] || [ "$avl" -eq 0 ] ; then 
						 avl=1 
					else	
						echo "You can't ask for many type of sorting simulteanously, type --help for more info"
					fi ;;
			# HELP
			'--help') help ; exit 1 ;;
		    # DID YOU MEANT
			'-'[zeZExX]) echo "you typed '${!var}' did you meant -S ?"; exit 1 ;;
			'-'[rRcCvV]) echo "you typed '${!var}' did you meant -f ?"; exit 1 ;; 
			'-'[iIkKlL]) echo "you typed '${!var}' did you meant -O ?"; exit 1 ;; 
 			# CAS GENERAL
			*  ) echo "the  ${!var}  argument does not exist, type --help for mor info" ; exit 0 ;;
		esac
	fi
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
if [ "$nbExecC" -eq 0 ] ; then
	echo "You need to specify at least one type of data, type --help for more info"
	exit 1
fi  
if [ "$F" -eq 1 ] ; then
	grep -E '81408|81401|81405|81415|71805|78894|78890|78897|78925|78922|61997|61996|61972|61980|61976|67005|61968|89642|61998|61970' -v  area.csv > area_time.csv ; nbLoa=$((nbLoca+1)) ;
fi
if [ "$G" -eq 1 ] ; then
	grep -E '81408|81401|81405|81415' area.csv > area_time.csv ; 
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
	grep -E "89642" area.csv > area_time.csv ; 
fi
if [ "$nbLoca" -eq 0 ] ; then
	cat area.csv > area_time.csv
	nameOutpout=allData.txt ;
fi
if [ "$a" -eq "1" ] && [ "$g" -eq "1" ] ; then
awk -F ';' '$10 >= slat && $10 <= elat && $11 >= slong && $11 <= elong { print }' slat="$slat" elat="$elat" slong="$slong" elong="$elong" area_time.csv > finale.txt
else
	cat area_time.csv > finale.txt
fi
rm area.csv
if [ "$var" -eq 0 ]; then
	echo "no sort method asked, the default one is gonna be avl"
	avl=1
fi
mode=avl #so that the default mode is avl  
if [ "$tab" -eq 1 ] ; then
	mode=tab
fi
if [ "$abr" -eq 1 ] ; then
	mode=abr
fi
exitc () {
	if [ "$1" -eq 1 ]; then
		echo "There is an error with options sent to the c program"
		exit 1
	fi
	if [ "$1" -eq 2 ]; then
		echo "There is an error with the entry file for the c program"
		exit 1
	fi
	if [ "$1" -eq 3 ]; then
		echo "There is an error with the output file for the c program"
		exit 1
	fi
	if [ "$1" -eq 4 ]; then
		echo "There is an internal error in the c program"
		exit 1
	fi
	return 0
}

for var in $nbExecC ; do
	if [ "$t1" -eq 1 ] ; then
		cut -d ';' -f 1,11 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -t1 --$mode
		if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/t1.plt
		else 
			echo $?
			exitc $?
		fi
	fi
	if [ "$t2" -eq 1 ]; then
		cut -d ';' -f 11,2 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr -d '-' |  tr -d '+' | sed 's/\([0-9]\{8\}\)T.*;/\1;/g' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -t2 --$mode
		sed 's/\([0-9]\{4\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)/\1\/\2\/\3/g' data.txt > special.txt
		if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/t2.plt
		else 
			exitc $?
		fi
	fi
	if [ "$t3" -eq 1 ]; then
		cut -d ';' -f 1,11,2 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr -d '-' |  tr -d '+' | sed 's/\([0-9]\{8\}\)T.*;/\1;/g' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -t3 --$mode
		sed 's/\([0-9]\{4\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)/\1\/\2\/\3/g' data.txt > special.txt
		if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/t3.plt
		else 
			exitc $?
		fi
	fi
	if [ "$p1" -eq 1 ]; then
		cut -d ';' -f 1,7 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -p1 --$mode
		if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/p1.plt
		else 
			exitc $?
		fi
	fi
	if [ "$p2" -eq 1 ]; then
		cut -d ';' -f 7,2 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr -d '-' |  tr -d '+' | sed 's/\([0-9]\{8\}\)T.*;/\1;/g' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -p2 --$mode
		sed 's/\([0-9]\{4\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)/\1\/\2\/\3/g' data.txt > special.txt
		if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/p2.plt
		else 
			exitc $?
		fi
	fi
	if [ "$p3" -eq 1 ]; then
		cut -d ';' -f 1,7 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr -d '-' |  tr -d '+' | sed 's/\([0-9]\{8\}\)T.*;/\1;/g' > $nameOutpout ;
		sed 's/\([0-9]\{4\}\)\([0-9]\{2\}\)\([0-9]\{2\}\)/\1\/\2\/\3/g' data.txt > special.txt
		./c -f$nameOutpout -odata.txt -p3 --$mode
		if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/p3.plt
		else 
			exitc $?
		fi
	fi
	if [ "$w" -eq 1 ]; then
		cut -d ';' -f 1,4,5,10 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr ',' ';' > $nameOutpout ;
		./c -f$nameOutpout -odata.txt -w --$mode
		if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/w.plt
		else 
			exitc $?
		fi
	fi
	if [ "$m" -eq 1 ]; then
    	cut -d ';' -f 1,6,10 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr ',' ';' > $nameOutpout ;
    	./c -f$nameOutpout -odata.txt -m --$mode
    	if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/m.plt
		else 
			exitc $?
		fi
	fi
	if [ "$h" -eq 1 ]; then
    	cut -d ';' -f 1,14,10 --output-delimiter=';' finale.txt | grep -E ';$|;;' -v |  tr ',' ';' > $nameOutpout ;
    	./c -f$nameOutpout -odata.txt -h --$mode
    	if [ "$?" -eq 0 ] ; then 
			gnuplot -persist plt_files/h.plt
		else 
			exitc $?
		fi
	fi
done
rm special.txt 
rm data.txt
rm $nameOutpout
rm area_time.csv
rm finale.txt
exit 0