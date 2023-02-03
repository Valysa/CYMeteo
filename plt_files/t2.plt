set datafile separator ";"
set timefmt "%Y/%m/%d"
set xlabel "Dates"
set format x "%Y/%m/%d"
set xdata time
set ylabel "Temperatures"
set style fill solid 1.00 border lt -1
Shadecolor = "#80E0A080"
plot "special.txt" using 1:2 with lines