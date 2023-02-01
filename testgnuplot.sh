#!/usr/local/bin/gnuplot -persist
# set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 600, 400 
# set output 'errorbars.2.png'
set style data lines
set title "error represented by boxxyerror" 
set xlabel "Resistance [Ohm]" 
set xrange [ * : * ] noreverse writeback
set x2range [ * : * ] noreverse writeback
set ylabel "Power [W]" 
set yrange [ * : * ] noreverse writeback
set y2range [ * : * ] noreverse writeback
set zrange [ * : * ] noreverse writeback
set cbrange [ * : * ] noreverse writeback
set rrange [ * : * ] noreverse writeback
set colorbox vertical origin screen 0.9, 0.2 size screen 0.05, 0.6 front  noinvert bdefault
n(x)=1.53**2*x/(5.67+x)**2
NO_ANIMATION = 1
## Last datafile plotted: "battery.dat"
plot [0:50] "battery.dat" t "Power" with boxxyerr, n(x) t "Theory" w lines
exit
