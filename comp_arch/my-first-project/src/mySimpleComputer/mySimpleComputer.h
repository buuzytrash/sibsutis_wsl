#ifndef mySimpleComputer_h
#define mySimpleComputer_h

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define MaxMemory 100
#define NUM_COMMANDS 13

enum mask_flags
{
  OVERFLOW_OPERATION = 1,
  DIV_BY_ZERO = OVERFLOW_OPERATION << 1,
  OVERFLOW_MEMORY = DIV_BY_ZERO << 1,
  IGNOR_CLOCK_PULSES = OVERFLOW_MEMORY << 1,
  INCORRECT_COMMAND = IGNOR_CLOCK_PULSES << 1
};

extern uint16_t *memory;
extern uint8_t reg_flags; // Регистр флагов

int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);
int sc_commandEncode (int command, int operand, int *value);
int sc_commandDecode (int value, int *command, int *operand);

#endif