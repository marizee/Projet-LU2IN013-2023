plot "comp.txt" using 1:2 with lines title "Sagemath" smooth cspline
replot "comp.txt" using 1:3 with lines title "Naïf" smooth cspline
replot "comp.txt" using 1:4 with lines title "Horner" smooth cspline
replot "comp.txt" using 1:5 with lines title "Brent et Kung" smooth cspline
set xrange [0:2048]
set xlabel "degré n"
set yrange [0:40]
set ylabel "temps"
set key on outside right
