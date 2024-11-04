gcc -Wall serial.c -o serial -lm
gcc -fopenmp -Wall ver_1.c -o ver_1 -lm
gcc -fopenmp -Wall ver_2.c -o ver_2 -lm
gcc -fopenmp -Wall ver_3.c -o ver_3 -lm
gcc -fopenmp -Wall ver_4.c -o ver_4 -lm
gcc -fopenmp -Wall -g -O0 ver_5.c -o ver_5 -lm 