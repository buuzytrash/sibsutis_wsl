
set terminal png size 1400,900 font "Arial, 24"
set output "grath.png"

set style line 1 lc rgb "0xDC143C" lt 1 lw 4 pt 9 ps 1
set style line 2 lc rgb "0x6495ED" lt 1 lw 4 pt 7 ps 1
set style line 3 lc rgb "0xA4e421" lt 1 lw 4 pt 7 ps 1
set style line 4 lc rgb "0x0128af" lt 1 lw 4 pt 7 ps 1
set style line 5 lc rgb "0x909182" lt 1 lw 4 pt 7 ps 1
set style line 6 lc rgb "0x35f6af" lt 1 lw 4 pt 7 ps 1
set border lw 2

set grid
set key top left

set xlabel "Количество процессов"
set ylabel "Ускорение" rotate by 90
set xtics 1
set ytics 1
set format x "%6.0f"
set format y "%1.0f"
set yrange [0:9]
set xrange [0:10]

plot 'data.dat' using 1:1 title "Линейное ускорение" with linespoints ls 1, \
'data.dat' using 1:2 title "n = 1000" with linespoints ls 2, \
'data.dat' using 1:3 title "n = 2000" with linespoints ls 3, \
'data.dat' using 1:4 title "n = 3000" with linespoints ls 4, \
'data.dat' using 1:5 title "n = 4000" with linespoints ls 5, \
'data.dat' using 1:6 title "n = 5000" with linespoints ls 6, \
