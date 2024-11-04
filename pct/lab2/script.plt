#!/usr/bin/gnuplot

set termoption enhanced
set terminal png size 1400,900 font "Arial, 24"
set output "grath.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set style line 3 lc rgb "0xADFF2F" lt 1 lw 4 pt 5 ps 1
set style line 4 lc rgb "0xADFFDF" lt 1 lw 4 pt 5 ps 1
set style line 5 lc rgb "0xAD1F2F" lt 1 lw 4 pt 5 ps 1
set border lw 2
set grid
set key top left
set xlabel "Число потоков процессора\n\n <<Зависимость коэффициента S ускорения\
параллельной программы от числа P потоков>>
set ylabel "Коэффициент ускорения" rotate by 90
set xtics 1
set ytics 1
set format x "%6.0f"
set format y "%1.0f"
set yrange [0:7]
set xrange [2:6]
plot "speedup.txt" using 1:2 title "m=n=15000" with linespoints ls 2, \
"speedup.txt" using 1:3 title "m=n=20000" with linespoints ls 3, \
"speedup.txt" using 1:4 title "m=n=25000" with linespoints ls 4, \
"speedup.txt" using 1:5 title "Linear speedup" with linespoints ls 1