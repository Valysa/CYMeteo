set datafile separator ";"
set xlabel "ide"
set ylabel "Temperatures"
set style fill solid 1.00 border lt -1
Shadecolor = "#80E0A080"
plot "data.txt" using 1:4:3 with lines