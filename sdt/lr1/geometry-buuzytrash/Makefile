TARGET = bin/main
CC = gcc
CFLAGS = -I src/ -I thirdparty/ -Wall -Wextra -Werror -O0 -g
CPPFLAGS = -MMD
.PHONY : clean
.PHONY : test

$(TARGET) : ./obj/src/geom/geom.o ./obj/src/libgeom/libgeom.a
	$(CC) $(CFLAGS) -o $@ $^ -lm

./obj/src/geom/geom.o : ./src/geom/main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

./obj/src/libgeom/libgeom.a : ./obj/src/libgeom/libgeom.o 
	ar rcs $@ $^

./obj/src/libgeom/libgeom.o : ./src/libgeom/geom.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

run :
	bin/main

clean :
	rm ./obj/src/geom/geom.d ./obj/src/geom/geom.o ./obj/src/libgeom/libgeom.d ./obj/src/libgeom/libgeom.a ./obj/src/libgeom/libgeom.o ./obj/test/geom_test.o ./obj/test/main_test.o ./obj/test/geom_test.d ./obj/test/main_test.d ./bin/test $(TARGET)

test : ./obj/test/geom_test.o ./obj/test/main_test.o ./obj/src/libgeom/libgeom.a
	$(CC) $(CFLAGS) -o ./bin/test $^ -lm

run_test : 
	bin/test

./obj/test/geom_test.o : ./test/geom_test.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

./obj/test/main_test.o : ./test/main.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<


-include main.d geom.d