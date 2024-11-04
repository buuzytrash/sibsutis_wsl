CC = gcc
CFLAGS = -O0 -g
main : main.c hash_table.c
	$(CC) $(CFLAGS) $^ -o $@
main_uni: main_uni.c hash_table_uni.c
	$(CC) $(CFLAGS) $^ -o $@
main_perf: main_perf.c hash_table_perf.c
	$(CC) $(CFLAGS) $^ -o $@
clean :
	rm main main_perf main_uni