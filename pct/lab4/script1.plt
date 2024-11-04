#!/usr/bin/gnuplot

set termoption enhanced
set terminal png size 1400,900 font "Arial, 24"
set output "grath1.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x1415ED" lt 1 lw 4 pt 7 ps 1
set style line 3 lc rgb "0xFAAFFF" lt 1 lw 4 pt 7 ps 1
set style line 4 lc rgb "0x43321F" lt 1 lw 4 pt 7 ps 1
set style line 5 lc rgb "0xDFE471" lt 1 lw 4 pt 7 ps 1
set style line 6 lc rgb "0x663DAC" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "Threads"
set ylabel "Speedup" rotate by 90
set xtics 1
set ytics 1
set format x "%6.0f"
set format y "%.12g"
set yrange [0:4]
set xrange [2:4]
plot "speedup.txt" using 1:1 title "Linear speedup" with linespoints ls 1, \
"speedup.txt" using 1:2 title "Ver.1 (n=100)" with linespoints ls 2, \
"speedup.txt" using 1:3 title "Ver.2 (n=100)" with linespoints ls 3, \
"speedup.txt" using 1:4 title "Ver.3 (n=100)" with linespoints ls 4, \
"speedup.txt" using 1:5 title "Ver.4 (n=100)" with linespoints ls 5, \
"speedup.txt" using 1:6 title "Ver.5 (n=100)" with linespoints ls 6 \