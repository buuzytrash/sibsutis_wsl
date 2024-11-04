#!/usr/bin/gnuplot

set termoption enhanced
set terminal png size 1400,900 font "Arial, 24"
set output "i.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set border lw 2
set grid
set key top left
set xlabel "Дни\n\n <<Статистика инфицированных с симптомами>>
set ylabel "Количество людей" rotate by 90
set xtics 20
set ytics 5
set format x "%6.0f"
set format y "%1.0f"
set yrange [0:50]
set xrange [0:90]
plot "infected.txt" using 1:2 title "Инфицированные с симптомами" with linespoints ls 2, 