#https://bdesgraupes.pagesperso-orange.fr/UPX/Tutoriels/presentation_gnuplot.pdf


#plot "comp.txt" using 1:2 with lines title "Sagemath" smooth cspline lc "violet"
#replot "comp.txt" using 1:3 with lines title "Naïf" smooth cspline lc "orange"
#replot "comp.txt" using 1:4 with lines title "Horner" smooth cspline lc "blue" 
#replot "comp.txt" using 1:5 with lines title "Brent et Kung" smooth cspline lc "red"
#set xrange [0:2048]
#set xlabel "degré n" font ",11"
#set yrange [0:40]
#set ylabel "temps" font ",11"
#set key on outside right font ",12"

#plot "comp_2.txt" using 1:2 with lines title "Horner" smooth cspline lc "blue"
#replot "comp_2.txt" using 1:3 with lines title "Brent et Kung" smooth cspline lc "red"
#set xrange [0:9901]
#set xlabel "degré n" font ",11"
#set yrange [0:30]
#set ylabel "temps" font ",11"
#set key off

plot "multi.txt" using 1:2 with lines title "Sagemath" smooth cspline lc "violet"
replot "multi.txt" using 1:3 with lines title "Naïf" smooth cspline lc "orange"
replot "multi.txt" using 1:4 with lines title "Karatsuba" smooth cspline lc "blue" 
set xrange [0:1901]
set xlabel "degré n" font ",11"
set yrange [-0.02:5]
set ylabel "temps" font ",11"
set key on outside right font ",12"