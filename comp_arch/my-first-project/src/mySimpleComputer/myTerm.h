#pragma once

#include <fcntl.h>
#include <mySimpleComputer.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum colors
{
  cl_default,
  black,
  red,
  green,
  yellow,
  blue,
  violet,
  aquamarine,
  gray
};

int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum colors color);
int mt_setbgcolor (enum colors color);