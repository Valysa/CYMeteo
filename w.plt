set autoscale
set xlabel "Longitude"
set ylabel "Latitude"
set size square
set datafile separator ";"
plot "data.txt" using 4:5:($3*cos(2*pi*$2/360)):($3*sin(2*pi*$2/360)) w vectors title "Wind"
#it sends the orientation and the formulas take it to calculate the coordinates of x2,y2
