set datafile separator ";"
set xlabel "Stations ID"
set ylabel "Temperatures"
set style fill solid 1.00 border lt -1
Shadecolor = "#80E0A080"
plot "data.txt" using 1:4:3 w filledcurve fc rgb Shadecolor title "Max Min range",     '' using 1:2 smooth mcspline lw 2   title "Average"
