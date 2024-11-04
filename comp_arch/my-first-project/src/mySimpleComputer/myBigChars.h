#pragma once

#include <mySimpleComputer.h>
#include <myTerm.h>

#define CAGE "a"
#define LOW_R_CORN "j"
#define UP_R_CORN "k"
#define UP_L_CORN "l"
#define LOW_L_CORN "m"
#define VERT "x"
#define HOR "q"

extern unsigned int *big_chars;

int bc_init ();
int bc_printA (char *str);
int bc_box (int x1, int y1, int x2, int y2);

int bc_printbigchar (unsigned int arr[2], int x, int y, enum colors color_fg,
                     enum colors color_bg);
int bc_setbigcharpos (unsigned int *big, int x, int y, int value);
int bc_getbigcharpos (unsigned int *big, int x, int y, int *value);
int bc_bigcharwrite (int fd, unsigned int *big, int count);
int bc_bigcharread (int fd, unsigned int *big, int need_count, int *count);
int *getbigcharvalue (uint16_t var);