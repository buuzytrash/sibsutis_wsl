#!/usr/bin/gnuplot

set termoption enhanced
set terminal png size 1400,900 font "Arial, 16"
set output "plot.png"
set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set style line 2 lc rgb "0xADFF2F" lt 1 lw 4 pt 5 ps 1
set border lw 2
set grid
set key top left
set xlabel "Количество элементов в массиве\n\n <<Зависимость времени выполнения \
алгоритмов Merge sort, Counting sort и Bubble sort от размера массива>>
set ylabel "Время выполнения, с" rotate by 90
set xtics 100000
set mxtics
set format x "%6.0f"
set format y "%.2f"
set logscale y
set xrange [0:1000000]
plot "data.txt" using 1:2 title "Merge" with linespoints ls 1, "data.txt" using 1:3 title "Counting sort" with linespoints ls 2,\
"data.txt" using 1:4 title "Bubble sort" with linespoints ls 4