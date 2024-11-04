#!/usr/bin/gnuplot

set termoption enhanced
set terminal png size 1400,900 font "Arial, 24"
set output "r.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set border lw 2
set grid
set key top left
set xlabel "Дни\n\n <<Статистика вылеченных>>
set ylabel "Количество людей" rotate by 90
set xtics 20
set ytics 3000
set format x "%6.0f"
set format y "%1.0f"
set yrange [0:43000]
set xrange [0:90]
plot "recovered.txt" using 1:2 title "Вылеченные" with linespoints ls 2, 