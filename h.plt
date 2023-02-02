set dgrid3d
set colorbox user
set datafile separator ";"
set pm3d map interpolate 64,64
splot "data.txt" using 4:3:1 w pm3d
