PACK_NAME = frag
LIB_NAME = libfrag

SHELL = /bin/bash

BIN_DIR = bin

OBJ_DIR = obj

SRC_DIR = src

TEST_NAME = test

TEST_DIR = test

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O0 -g
CPPFLAGS  =  -I src -MP -MMD
CPPFLAGS2 = -I ctest -MP -MMD

APP_PATH = $(BIN_DIR)/$(PACK_NAME)

LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a


APP_SOURCES = $(shell find $(SRC_DIR)/$(PACK_NAME) -name '*.c')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.c')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) 

.PHONY: all clean test

all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


clean:
	$(RM) $(LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;


test : ./obj/test/main.o ./obj/test/fragtest.o ./obj/src/libfrag/libfrag.a
	$(CC) $(CFLAGS) -o bin/test $^ 
	
./obj/test/main.o : ./test/main.c
	$(CC) -c $(CPPFLAGS2) $(CFLAGS) -o $@ $^ 

./obj/test/fragtest.o : ./test/fragtest.c
	$(CC) -c $(CPPFLAGS) $(CPPFLAGS2) $(CFLAGS) -o $@ $^ 

run_test : test
	./bin/test

gi
