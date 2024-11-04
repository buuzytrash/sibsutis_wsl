#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

enum MODES { NO_MODE, LINES, BYTES };

void frag(int instr, int nol, FILE* file);
void bytes_frag(int instr, size_t bytes, FILE* file);
void print_usage();
int args(int argc, char* argv[], int* mode);
