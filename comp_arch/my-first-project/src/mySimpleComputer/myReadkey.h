#pragma once

#include <fcntl.h>
#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

enum keys
{
  KEY_l,
  KEY_s,
  KEY_r,
  KEY_t,
  KEY_i,
  KEY_q,
  KEY_f5,
  KEY_f6,
  KEY_up,
  KEY_down,
  KEY_left,
  KEY_right,
  KEY_enter,
  KEY_other
};

int rk_readkey (enum keys *key);
int rk_mytermsave ();
int rk_mytermrestore ();
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);