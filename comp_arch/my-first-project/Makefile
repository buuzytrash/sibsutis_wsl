PACK_NAME = main
PACK_NAME2 = test_term
PACK_NAME3 = term
PACK_NAME4 = test_bc
PACK_NAME5 = test_rdkey
LIB_NAME = mySimpleComputer
LIB_NAME2 = myTerm
LIB_NAME3 = myBigChars
LIB_NAME4 = myReadkey
COMPILE_B = myBigCharsCreate


SHELL = /bin/bash

BIN_DIR = bin

OBJ_DIR = obj

SRC_DIR = src

CC = gcc
CFLAGS = -Wall -O0 -g -I ./src/mySimpleComputer
CPPFLAGS  = -MP -MMD -Wextra 

APP_PATH = $(BIN_DIR)/$(PACK_NAME) 
APP_PATH2 = $(BIN_DIR)/$(PACK_NAME2)
APP_PATH3 = $(BIN_DIR)/$(PACK_NAME3)
APP_PATH4 = $(BIN_DIR)/$(PACK_NAME4)
APP_PATH5 =  $(BIN_DIR)/$(PACK_NAME5)
APPB_PATH = $(BIN_DIR)/$(COMPILE_B)

LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME2).a $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME3).a $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME4).a


APP_SOURCES = $(shell find $(SRC_DIR)/$(PACK_NAME)/$(PACK_NAME).c) 
APP_SOURCES2 = $(shell find $(SRC_DIR)/$(PACK_NAME)/$(PACK_NAME2).c) 
APP_SOURCES3 = $(shell find $(SRC_DIR)/$(PACK_NAME)/$(PACK_NAME3).c)
APP_SOURCES4 = $(shell find $(SRC_DIR)/$(PACK_NAME)/$(PACK_NAME4).c)
APP_SOURCES5 = $(shell find $(SRC_DIR)/$(PACK_NAME)/$(PACK_NAME5).c)
APPB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME)/$(COMPILE_B).c)


APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)
APP_OBJECTS2 = $(APP_SOURCES2:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)
APP_OBJECTS3 = $(APP_SOURCES3:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)
APP_OBJECTS4 = $(APP_SOURCES4:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)
APP_OBJECTS5 = $(APP_SOURCES5:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)
APPB_OBJECTS = $(APPB_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME)  -name '*.c')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d) 

.PHONY: all clean test

all: $(APP_PATH) $(APP_PATH2) $(APP_PATH3) $(APP_PATH4) $(APP_PATH5) $(APPB_PATH) RUN_B

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH) $(LIB_PATH2)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 
$(APP_PATH2): $(APP_OBJECTS2) $(LIB_PATH) $(LIB_PATH2)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 
$(APP_PATH3): $(APP_OBJECTS3) $(LIB_PATH) $(LIB_PATH2)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 
$(APP_PATH4): $(APP_OBJECTS4) $(LIB_PATH) $(LIB_PATH2)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 
$(APP_PATH5): $(APP_OBJECTS5) $(LIB_PATH) $(LIB_PATH2)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@
$(APPB_PATH): $(APPB_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ 


./obj/src/mySimpleComputer/myBigCharsCreate.o : ./src/mySimpleComputer/myBigCharsCreate.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^ 

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ 

RUN_B :
	./$(BIN_DIR)/$(COMPILE_B)

clean:
	$(RM) $(LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
	$(RM) $(APP_PATH)
	$(RM) $(APP_PATH2)
	$(RM) $(APP_PATH3)
	$(RM) $(APP_PATH4)
	$(RM) $(APP_PATH5)
	$(RM) BigChar

run_test1 :
	./bin/main
run_test2 :
	./bin/test_term
run_term :
	./bin/term
run_bc :
	./bin/test_bc
run_rdkey :
	./bin/test_rdkey