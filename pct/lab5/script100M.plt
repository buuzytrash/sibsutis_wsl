#!/usr/bin/gnuplot

set termoption enhanced
set terminal png size 1400,900 font "Arial, 24"
set output "grath3.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set style line 3 lc rgb "0x43321F" lt 1 lw 4 pt 7 ps 1
set style line 4 lc rgb "0xDFE471" lt 1 lw 4 pt 7 ps 1
set style line 5 lc rgb "0x663DAC" lt 1 lw 4 pt 7 ps 1
set border lw 2
set grid
set key top left
set xlabel "Число потоков\n\n <<Зависимость коэффициента S ускорения\
\nпараллельной программы от числа P потоков при N = 10^8>>
set ylabel "Коэффициент ускорения" rotate by 90
set xtics 1
set ytics 1
set format x "%6.0f"
set format y "%1.0f"
set yrange [1:4]
set xrange [2:4]
plot "speedup100M.txt" using 1:2 title "tasks" with linespoints ls 2, \
"speedup100M.txt" using 1:3 title "untied tasks" with linespoints ls 3, \
"speedup100M.txt" using 1:1 title "Linear speedup" with linespoints ls 1