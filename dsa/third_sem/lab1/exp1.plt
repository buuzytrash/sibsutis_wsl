#!/usr/bin/gnuplot

set termoption enhanced
set terminal png size 1400,900 font "Arial, 16"
set output "grafik.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set style line 2 lc rgb "0xADFF2F" lt 1 lw 4 pt 5 ps 1
set border lw 2
set grid
set key top left
set xlabel "Количество элементов в словаре\n\n <<Зависимость времени t поиска \
элемента в словаре от числа n ключей, добавленных в него>>
set ylabel "Время поиска элемента, с" rotate by 90
set xtics 5000
set mxtics
set format x "%6.0f"
set format y "%.6f"
set logscale y
set xrange [0:50000]
plot "data.txt" using 1:2 title "avltree" with linespoints ls 1