<strong> CYMeteo </strong> by two anonymos super strong devs from preing 2 (one is gonna fail his year please help him)

SUMMARY

    1 Description
    2 Arguments
    3 Features
    4 C Particularities
    
1 Description

    This is a programm wich allows you to visualise meteorologics data
    You will be able to make graphics and maps from data files.
    To run the program, simply make sure you have the data file you want to use,
    then simply type ./skript.sh --help to discover features
    A first script shell will be cut the data you want based on the restrictions
    then it will call a C programm to sort them
    The script shell will then display some grpahs or maps depending on what arguments
    have been put
    
2 Arguments
    
    To make the programm works you will need to specify somme arguments
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
       Note that there is actually no "<>"
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
         --help : to display the help message wich is basically a section of this makefile
       
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
       So for example if you want the temperature in mode one, enter the argument -t1
       
3 Features
      
4 C Particularities
      
      Has the program calls a C programm you can run it individually
      for this one the order of argument is important, the arguments are as follow :
      1 : -f<filename.txt> : to specify the name of your datafile (note that there is no space between -f and filename)
      2 : -o<filename.txt> : to specify the name of the file  you want the data to be put in (it doesn't have to already exist)
      3 : -typeofdata : exacly the same as in the script shell
      4 : --mode : to specify the sort mode (optionnal)
      5 : -r : if you want the data in an other order
     
