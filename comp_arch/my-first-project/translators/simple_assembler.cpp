#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

short int
get_num16 (std::string operand)
{
  if (operand.size () != 5)
    return 0;
  int cur_number = 0;
  short int number = 0;

  cur_number
      = (operand[1] - '0') * pow (16, 1) + (operand[2] - '0') * pow (16, 0);
  if (cur_number > (uint8_t) ~(1 << 7))
    return 0; // overflow
  number |= cur_number << 7;

  cur_number
      = (operand[3] - '0') * pow (16, 1) + (operand[4] - '0') * pow (16, 0);
  if (cur_number > (uint8_t) ~(1 << 7))
    return 0; // overflow
  number |= cur_number;

  if (operand[0] == '+')
    return number;
  else if (operand[0] == '-')
    return number | 1 << 14;
  else
    return 0;
}

int
main (int argc, char **argv)
{
  if (argc != 3)
    {
      std::cout << "Usage : sat prog.sa bin.o\n";
      exit (1);
    }

  std::ifstream asm_file (argv[1], std::ios::in);
  if (!asm_file.is_open ())
    {
      std::cout << "Error : no such file or directory " << argv[1]
                << std::endl;
      exit (1);
    }

  std::unordered_map<std::string, int> dict_commands
      = { { "READ", 2048 },   { "WRITE", 2176 }, { "LOAD", 4096 },
          { "STORE", 4224 },  { "ADD", 6144 },   { "SUB", 6272 },
          { "DIVIDE", 6400 }, { "MUL", 6528 },   { "JUMP", 8192 },
          { "JNEG", 8320 },   { "JZ", 8448 },    { "HALT", 8576 },
          { "JNC", 11136 } };
  std::string line, command, operand;
  int number_cell, integer_operand;
  short int *memory = new short int[100]{ 0 };

  int number_line = 0;
  while (std::getline (asm_file, line))
    {
      number_line++;
      std::stringstream iss (line);
      iss >> number_cell >> command >> operand;
      if (!command.compare ("="))
        {
          memory[number_cell] = get_num16 (operand);
          continue;
        }

      integer_operand = std::atoi (operand.c_str ());
      if (number_cell < 0 || number_cell > 99)
        {
          std::cout << "invalid cell value at " << number_line << " line!"
                    << std::endl;
          exit (1);
        }
      if (integer_operand < 0 || integer_operand > 99)
        {
          std::cout << "invalid operand value at " << number_line << " line!"
                    << std::endl;
          exit (1);
        }
      if (!dict_commands[command])
        {
          std::cout << "unknown command at " << number_line << " line!"
                    << std::endl;
          exit (1);
        }
      memory[number_cell] = dict_commands[command] + integer_operand;
    }
  asm_file.close ();

  FILE *bin_file = fopen (argv[2], "wb");
  fwrite (memory, sizeof (short int), 100, bin_file);
  fclose (bin_file);

  return 0;
}