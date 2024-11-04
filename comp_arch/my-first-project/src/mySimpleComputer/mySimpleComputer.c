#include "mySimpleComputer.h"

const uint8_t correct_ops[NUM_COMMANDS]
    = { 0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32,
        0x33, 0x40, 0x41, 0x42, 0x43, 0x57 };
uint16_t *memory;
uint8_t reg_flags;

int
sc_memoryInit ()
{
  memory = calloc (MaxMemory, sizeof (uint16_t));
  if (!memory)
    {
      return 1;
    }
  else
    return 0;
}

int
sc_memorySet (int address, int value)
{
  if (address >= MaxMemory || address < 0)
    {
      reg_flags = reg_flags | OVERFLOW_MEMORY;
      return -1;
    }
  else
    {
      memory[address] = value;
      return 0;
    }
}

int
sc_memoryGet (int address, int *value)
{
  if (!value)
    {
      return -1;
    }

  if (address >= MaxMemory)
    {
      reg_flags = reg_flags | OVERFLOW_MEMORY;
      return -1;
    }
  else
    {
      *value = memory[address];
      return 0;
    }
}

int
sc_memorySave (char *filename)
{
  FILE *file = fopen (filename, "wb");
  int flag = 0;
  if (file == NULL)
    return -1;
  flag = fwrite (memory, sizeof (*memory) * MaxMemory, 1, file);
  fclose (file);
  if (flag != 1)
    return -1;
  else
    return 0;
}

int
sc_memoryLoad (char *filename)
{
  FILE *file = fopen (filename, "rb");
  int flag;
  if (file == NULL)
    return -1;
  flag = fread (memory, sizeof (*memory) * MaxMemory, 1, file);
  fclose (file);
  if (flag != 1)
    return -1;
  else
    return 0;
}

int
sc_regInit ()
{
  reg_flags = 1 << 3;
  return 0;
}

int
sc_regSet (int reg, int value)
{
  if ((reg >= 0) && (reg <= 5))
    {
      if (value == 1)
        reg_flags = reg_flags | (1 << (reg - 1));
      else if (value == 0)
        reg_flags = reg_flags & ~(1 << (reg - 1));
      else
        return -1;
      return 0;
    }
  else
    return -1;
}

int
sc_regGet (int reg, int *value)
{
  if ((reg >= 0) && (reg <= 5))
    {
      *value = reg_flags >> (reg - 1) & 1;
    }
  else
    return -1;
  return 0;
}

int
sc_commandEncode (int command, int operand, int *value)
{
  if (command > 0x7f || operand > 0x7f)
    return -1;

  *value = (command << 7) | operand;
  return 0;
}

int
sc_commandDecode (int value, int *command, int *operand)
{
  if (value >> 14)
    {
      return -1;
    }

  *command = value >> 7;
  *operand = value & 0x7F;

  return 0;
}