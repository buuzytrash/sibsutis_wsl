#include <myBigChars.h>
#include <myReadkey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <signal.h>
#include <sys/time.h>

#define DEFAULT_X 0
#define DEFAULT_Y 0

int ALU (int command, int operand);
int CU ();

char space[] = "                                              ";
int cur_x = 0, cur_y = 0;
int accumulator = 0;
int instructionCounter = 0;

#define TIME 0
struct itimerval tval = { { TIME, 50000 }, { TIME, 50000 } }, last_tval;

void
print_frames ()
{
  bc_box (65, 1, 88, 3);
  bc_box (65, 4, 88, 6);
  bc_box (65, 7, 88, 9);
  bc_box (65, 10, 88, 12);
  bc_box (50, 13, 96, 22);
  bc_box (1, 1, 62, 12);
  bc_box (1, 13, 47, 22);
}

void
print_bigchar (int address)
{
  char bigchar[8];
  int value;
  int command, operand;

  sc_memoryGet (address, &value);
  sc_commandDecode (value & 0x3FFF, &command, &operand);

  snprintf (bigchar, 8, "%c%02X%02X", (value & 0x4000) ? '-' : '+', command,
            operand);

  if (bigchar[0] == '+')
    {
      bc_printbigchar (big_chars + 32, 2, 14, blue, blue);
    }
  else
    {
      bc_printbigchar (big_chars + 34, 2, 14, blue, blue);
    }
  for (int i = 0; i < 5; i++)
    {
      switch (bigchar[i + 1])
        {
        case '0':
          {
            bc_printbigchar (big_chars, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '1':
          {
            bc_printbigchar (big_chars + 2, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '2':
          {
            bc_printbigchar (big_chars + 4, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '3':
          {
            bc_printbigchar (big_chars + 6, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '4':
          {
            bc_printbigchar (big_chars + 8, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '5':
          {
            bc_printbigchar (big_chars + 10, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '6':
          {
            bc_printbigchar (big_chars + 12, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '7':
          {
            bc_printbigchar (big_chars + 14, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '8':
          {
            bc_printbigchar (big_chars + 16, (11 + i * 9), 14, blue, blue);
            break;
          }
        case '9':
          {
            bc_printbigchar (big_chars + 18, (11 + i * 9), 14, blue, blue);
            break;
          }
        case 'A':
          {
            bc_printbigchar (big_chars + 20, (11 + i * 9), 14, blue, blue);
            break;
          }
        case 'B':
          {
            bc_printbigchar (big_chars + 22, (11 + i * 9), 14, blue, blue);
            break;
          }
        case 'C':
          {
            bc_printbigchar (big_chars + 24, (11 + i * 9), 14, blue, blue);
            break;
          }
        case 'D':
          {
            bc_printbigchar (big_chars + 26, (11 + i * 9), 14, blue, blue);
            break;
          }
        case 'E':
          {
            bc_printbigchar (big_chars + 28, (11 + i * 9), 14, blue, blue);
            break;
          }
        case 'F':
          {
            bc_printbigchar (big_chars + 30, (11 + i * 9), 14, blue, blue);
            break;
          }
        }
    }
}

void
print_accumulator ()
{
  mt_gotoXY (74, 2);

  char *str_accum = malloc (20);
  if (accumulator >= 0)
    {
      sprintf (str_accum, "+%04x", accumulator);
    }
  else
    {
      sprintf (str_accum, "-%04x", ~accumulator + 1);
    }
  write (1, str_accum, strlen (str_accum));

  free (str_accum);
  mt_gotoXY (0, 25);
}

void
print_instructionCounter ()
{
  mt_gotoXY (73, 5);
  char *instrCounter = malloc (20);
  sprintf (instrCounter, "+%04x", instructionCounter);
  write (1, instrCounter, strlen (instrCounter));

  free (instrCounter);
  mt_gotoXY (0, 25);
}

void
print_operation ()
{
  int value, command, operand;
  mt_gotoXY (71, 8);
  // sc_commandEncode (0x42, 0x56, &value);
  sc_memoryGet (instructionCounter, &value);
  sc_commandDecode (value & 0x3fff, &command, &operand);

  char *operation = malloc (20);
  sprintf (operation, "%c%02x : %02x", (value & 0x4000) ? '-' : '+', command,
           operand);
  write (1, operation, strlen (operation));

  free (operation);
  mt_gotoXY (0, 25);
}

void
print_flags ()
{
  mt_gotoXY (73, 10);
  write (1, " Flags ", strlen (" Flags "));
  mt_gotoXY (73, 11);
  char flags[] = "POMTE";
  int value = 0;
  for (int i = 0; i < 5; i++)
    {
      sc_regGet (i + 1, &value);
      if (value)
        {
          mt_setbgcolor (red);
          write (1, &flags[i], 1);
          mt_setbgcolor (cl_default);
        }
      else
        {
          write (1, &flags[i], 1);
        }
    }
}

void
print_keys ()
{
  mt_setfgcolor (cl_default);
  mt_gotoXY (54, 13);
  write (1, " Keys: ", strlen (" Keys: "));
  mt_gotoXY (51, 14);
  write (1, "l  - load", strlen ("l  - load"));
  mt_gotoXY (51, 15);
  write (1, "s  - save", strlen ("s  - save"));
  mt_gotoXY (51, 16);
  write (1, "r  - run", strlen ("r  - run"));
  mt_gotoXY (51, 17);
  write (1, "t  - step", strlen ("t  - step"));
  mt_gotoXY (51, 18);
  write (1, "i  - reset", strlen ("i  - reset"));
  mt_gotoXY (51, 19);
  write (1, "F5  - accumulator", strlen ("F5  - accumulator"));
  mt_gotoXY (51, 20);
  write (1, "F6  - instructionCounter", strlen ("F6  - instructionCounter"));
  mt_gotoXY (51, 21);
  write (1, "q  - exit", strlen ("q  - exit"));
}

void
print_memory (int address, enum colors fg, enum colors bg)
{
  mt_setbgcolor (bg);
  mt_setfgcolor (fg);

  int value, row, col, command, operand;
  char buf[6];
  if (sc_memoryGet (address, &value) < 0
      || sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    return;

  row = address / 10;
  col = address % 10;

  sprintf (buf, "%c%02X%02X", (value & 0x4000) ? '-' : '+', command, operand);

  mt_gotoXY (3 + col * 6, 2 + row);
  write (1, buf, 5);
  write (1, "\E[m", 3);
}

void
print_terminal ()
{
  mt_clrscr ();
  int cols, rows;
  mt_getscreensize (&rows, &cols);
  if (rows < 27)
    {
      write (1, "can't print terminal", strlen ("can't print terminal"));
      return;
    }
  print_frames ();

  mt_gotoXY (25, 1);
  write (1, " memory ", strlen (" memory "));
  for (int l = 0; l < 100; l++)
    {
      print_memory (l, cl_default, cl_default);
    }

  mt_gotoXY (70, 1);
  write (1, " accumulator ", strlen (" accumulator "));
  print_accumulator ();

  mt_gotoXY (67, 4);
  write (1, " instructionCounter ", strlen (" instructionCounter "));
  print_instructionCounter ();

  mt_gotoXY (71, 7);
  write (1, " operation ", strlen (" operation "));
  print_operation ();

  print_flags ();
  print_bigchar (0);
  print_keys ();

  mt_gotoXY (0, 24);
  write (1, "Input\\Output", strlen ("Input\\Output"));

  mt_gotoXY (0, 25);
}

void
save_file ()
{
  char *f = malloc (20);
  int size;
  rk_mytermsave ();
  rk_mytermregime (0, 0, 0, 1, 1);
  rk_mytermregime (1, 0, 0, 0, 0);
  mt_gotoXY (0, 25);
  write (1, "file name : ", strlen ("file name : "));
  size = read (1, f, 20);
  f[size - 1] = '\0';
  mt_gotoXY (0, 25);
  write (1, space, strlen (space));
  int flag = sc_memorySave (f);
  if (flag)
    {
      mt_gotoXY (0, 25);
      write (1, "error", 5);
      sleep (3);
      mt_gotoXY (0, 25);
      write (1, space, strlen (space));
    }
  rk_mytermrestore ();
  system ("rm termsettings");
}

void
load_file ()
{
  char *f = malloc (20);
  int size;
  rk_mytermsave ();
  rk_mytermregime (0, 0, 0, 1, 1);
  rk_mytermregime (1, 0, 0, 0, 0);
  mt_gotoXY (0, 25);
  write (1, "file name : ", strlen ("file name : "));
  size = read (1, f, 20);
  f[size - 1] = '\0';
  mt_gotoXY (0, 25);
  write (1, space, strlen (space));
  int flag = sc_memoryLoad (f);
  if (flag)
    {
      mt_gotoXY (0, 25);
      write (1, "error", 5);
      sleep (3);
      mt_gotoXY (0, 25);
      write (1, space, strlen (space));
    }
  rk_mytermrestore ();
  system ("rm termsettings");

  for (int i = 0; i < 100; i++)
    {
      print_memory (i, cl_default, cl_default);
    }
  print_operation ();
}

void
change_value (int x, int y)
{
  char *str_number = malloc (20);
  int size, number;
  rk_mytermsave ();
  rk_mytermregime (0, 0, 0, 1, 1);
  rk_mytermregime (1, 0, 0, 0, 0);
  mt_gotoXY (0, 25);
  write (0, "enter number : ", strlen ("enter number : "));
  size = read (1, str_number, 20);
  str_number[size] = '\0';
  number = atoi (str_number);
  mt_gotoXY (0, 25);
  write (1, space, strlen (space));

  if (number > 0x3fff)
    {
      mt_gotoXY (0, 25);
      write (1, "Error! ", strlen ("Error! "));
      sleep (3);
      mt_gotoXY (0, 25);
      write (1, space, strlen (space));
      return;
    }
  if (number < 0)
    {
      number *= -1;
      if (number > 0x3fff)
        {
          mt_gotoXY (0, 25);
          mt_gotoXY (0, 25);
          write (1, "Error! ", strlen ("Error! "));
          sleep (3);
          mt_gotoXY (0, 25);
          write (1, space, strlen (space));
          return;
        }
      number |= 1 << 14;
      mt_gotoXY (0, 25);
    }
  sc_memorySet (y * 10 + x, number);
  rk_mytermrestore ();
  system ("rm termsettings");
}

void
reset ()
{
  free (memory);
  sc_memoryInit ();
  sc_regInit ();
  print_flags ();
  for (int i = 0; i < 100; i++)
    {
      print_memory (i, cl_default, cl_default);
    }
  print_operation ();
  cur_x = 0, cur_y = 0;
  print_bigchar (cur_y * 10 + cur_x);
}

void
set_accumulator ()
{
  char *str_number = malloc (20);
  int size, number;
  rk_mytermsave ();
  rk_mytermregime (0, 0, 0, 1, 1);
  rk_mytermregime (1, 0, 0, 0, 0);
  mt_gotoXY (0, 25);
  write (1, "enter acumulator : ", strlen ("enter acumulator : "));
  size = read (1, str_number, 20);
  str_number[size] = '\0';
  number = atoi (str_number);
  mt_gotoXY (0, 25);
  write (1, space, strlen (space));

  if (number > 0x3fff)
    {
      mt_gotoXY (0, 25);
      write (1, "Error! ", strlen ("Error! "));
      sleep (3);
      mt_gotoXY (0, 25);
      write (1, space, strlen (space));
      return;
    }
  if (number < 0)
    {
      number *= -1;
      if (number > 0x3fff)
        {
          mt_gotoXY (0, 25);
          write (1, "Error! ", strlen ("Error! "));
          sleep (3);
          mt_gotoXY (0, 25);
          write (1, space, strlen (space));
          return;
        }
      number |= 1 << 14;
      mt_gotoXY (0, 25);
    }
  accumulator = number;
  print_accumulator (number);
  rk_mytermrestore ();
  system ("rm termsettings");
}

void
set_instructionCounter ()
{
  char *str_number = malloc (20);
  int size, number;
  rk_mytermsave ();
  rk_mytermregime (0, 0, 0, 1, 1);
  rk_mytermregime (1, 0, 0, 0, 0);
  mt_gotoXY (0, 25);
  write (1, "enter instructionCounter : ",
         strlen ("enter instructionCounter : "));
  size = read (1, str_number, 20);
  str_number[size] = '\0';
  number = atoi (str_number);
  mt_gotoXY (0, 25);
  write (1, space, strlen (space));

  if (number > 99 || number < 0)
    return;
  instructionCounter = number;
  print_operation ();
  print_instructionCounter ();
  rk_mytermrestore ();
  system ("rm termsettings");
}

void
print_command (enum keys key)
{
  switch (key)
    {
    case KEY_l:
      load_file ();
      break;

    case KEY_s:
      save_file ();
      break;

    case KEY_r:
      print_operation ();
      setitimer (ITIMER_REAL, &tval, &last_tval);
      sc_regSet (4, 0);
      print_flags ();
      break;

    case KEY_t:
      CU ();
      break;

    case KEY_i:
      reset ();
      break;

    case KEY_f5:
      set_accumulator ();
      break;

    case KEY_f6:
      set_instructionCounter ();
      break;

    case KEY_up:
      if (cur_y > 0)
        {
          print_memory (10 * cur_y + cur_x, cl_default, cl_default);
          cur_y--;
          print_memory (10 * cur_y + cur_x, black, cl_default);
          print_bigchar (cur_y * 10 + cur_x);
        }
      else
        {
          print_memory (10 * cur_y + cur_x, cl_default, cl_default);
          cur_y = 9;
          print_memory (10 * cur_y + cur_x, black, cl_default);
          print_bigchar (cur_y * 10 + cur_x);
        }
      break;

    case KEY_down:
      if (cur_y < 9)
        {
          print_memory (10 * cur_y + cur_x, cl_default, cl_default);
          cur_y++;
          print_memory (10 * cur_y + cur_x, black, cl_default);
          print_bigchar (cur_y * 10 + cur_x);
        }
      else
        {
          print_memory (10 * cur_y + cur_x, cl_default, cl_default);
          cur_y = 0;
          print_memory (10 * cur_y + cur_x, black, cl_default);
          print_bigchar (cur_y * 10 + cur_x);
        }
      break;

    case KEY_right:
      if (cur_x < 9)
        {
          print_memory (10 * cur_y + cur_x, cl_default, cl_default);
          cur_x++;
          print_memory (10 * cur_y + cur_x, black, cl_default);
          print_bigchar (cur_y * 10 + cur_x);
        }
      else
        {
          print_memory (10 * cur_y + cur_x, cl_default, cl_default);
          cur_x = 0;
          print_memory (10 * cur_y + cur_x, black, cl_default);
          print_bigchar (cur_y * 10 + cur_x);
        }
      break;

    case KEY_left:
      if (cur_x > 0)
        {
          print_memory (10 * cur_y + cur_x, cl_default, cl_default);
          cur_x--;
          print_memory (10 * cur_y + cur_x, black, cl_default);
          print_bigchar (cur_y * 10 + cur_x);
        }
      else
        {
          print_memory (10 * cur_y + cur_x, cl_default, cl_default);
          cur_x = 9;
          print_memory (10 * cur_y + cur_x, black, cl_default);
          print_bigchar (cur_y * 10 + cur_x);
        }
      break;

    case KEY_enter:
      change_value (cur_x, cur_y);
      print_memory (cur_y * 10 + cur_x, black, cl_default);
      print_bigchar (cur_y * 10 + cur_x);
      break;

    case KEY_q:
      rk_mytermregime (0, 0, 0, 1, 1);
      rk_mytermregime (1, 0, 0, 0, 0);
      mt_gotoXY (0, 26);
      write (1, "\E[?25h\E[?8c", strlen ("\E[?25h\E[?8c"));
      exit (0);
      break;

    case KEY_other:
      break;
    }
}

int
ALU (int command, int operand)
{
  int value = 0;
  switch (command)
    {

    case 0x30: // ADD  Выполняет сложение слова в аккумуляторе и слова из
               // указанной ячейки памяти
      sc_memoryGet (operand, &value);
      value &= 0x3fff;
      if (accumulator + value > 0x3fff)
        {
          sc_regSet (1, 1);
          print_flags ();
          return -1;
        }
      accumulator += value;
      print_accumulator ();
      break;

    case 0x31: // SUB Вычитает из слова в аккумуляторе слово из указанной
               // ячейки памяти
      sc_memoryGet (operand, &value);
      value &= 0x3fff;
      if (accumulator - value < -0x3fff)
        {
          sc_regSet (1, 1);
          print_flags ();
          return -1;
        }
      accumulator -= value;
      print_accumulator ();
      break;

    case 0x32: // DIVIDE Выполняет деление слова в аккумуляторе на слово из
               // указанной ячейки памяти
      sc_memoryGet (operand, &value);
      value &= 0x3fff;
      if (value == 0)
        {
          sc_regSet (2, 1);
          print_flags ();
          return -1;
        }
      accumulator /= value;
      print_accumulator ();
      break;

    case 0x33: // MUL Вычисляет произведение слова в аккумуляторе на слово из
               // указанной ячейки памяти
      sc_memoryGet (operand, &value);
      value &= 0x3fff;
      if (accumulator * value > 0x3fff || accumulator * value < -0x3fff)
        {
          sc_regSet (1, 1);
          print_flags ();
          return -1;
        }
      accumulator *= value;
      print_accumulator ();
      break;
    }

  return 0;
}
int
CU ()
{
  int value, command, operand;

  if (instructionCounter > 98)
    {
      alarm (0);
      sc_regSet (4, 1);
      print_flags ();
      print_memory (instructionCounter, black, cl_default);
      print_memory (cur_y * 10 + cur_x, cl_default, black);
      return -1;
    }

  print_memory (instructionCounter, black, cl_default);
  sc_memoryGet (instructionCounter++, &value);
  print_memory (instructionCounter, cl_default, black);

  if (sc_commandDecode (value, &command, &operand) == -1)
    {
      alarm (0);
      sc_regSet (4, 1);
      sc_regSet (5, 1);
      print_flags ();
      return -1;
    }

  if (command >= 0x30 && command <= 0x33)
    {
      ALU (command, operand);
    }
  else
    {
      switch (command)
        {
        case 0x10: // READ Ввод с терминала в указанную ячейку памяти с
                   // контролем переполнения
          change_value (operand % 10, operand / 10);
          break;

        case 0x11: // WRITE Загрузка в аккумулятор значения из указанного
                   // адреса памяти
          print_bigchar (operand);
          break;

        case 0x20: // LOAD Загрузка в аккумулятор значения из указанного адреса
                   // памяти
          if (!sc_memoryGet (operand, &value))
            {
              accumulator = value;
              print_accumulator ();
              return 0;
            }
          break;

        case 0x21: // STORE Выгружает значение из аккумулятора по указанному
                   // адресу памяти
          if (!sc_memorySet (operand, accumulator))
            print_memory (operand, black, cl_default);
          return 0;

          break;

        case 0x40: // JUMP Переход к указанному адресу памяти
          if (operand >= 0 || operand <= 99)
            {
              print_memory (instructionCounter, black, cl_default);
              instructionCounter = operand;
              print_memory (instructionCounter, cl_default, black);
              return 0;
            }
          break;

        case 0x41: // JNEG Переход к указанному адресу памяти, если в
                   // аккумуляторе находится отрицательное число
          if (accumulator < 0)
            {
              if (operand >= 0 || operand <= 99)
                {
                  print_memory (instructionCounter, black, cl_default);
                  instructionCounter = operand;
                  print_memory (instructionCounter, cl_default, black);
                  return 0;
                }
              return -1;
            }
          break;

        case 0x42: // JZ Переход к указанному адресу памяти, если в
                   // аккумуляторе находится ноль
          if (accumulator == 0)
            {
              if (operand >= 0 || operand <= 99)
                {
                  print_memory (instructionCounter, black, cl_default);
                  instructionCounter = operand;
                  print_memory (instructionCounter, cl_default, black);
                  return 0;
                }
              return -1;
            }
          break;

        case 0x43: // HALT Останов, выполняется при завершении работы программы
          alarm (0);
          sc_regSet (4, 1);
          print_flags ();
          print_memory (instructionCounter, black, cl_default);
          print_memory (cur_y * 10 + cur_x, cl_default, black);
          break;

        case 0x57: // JNC  Переход к указанному адресу памяти, если при
                   // сложении не произошло переполнение
          sc_regGet (1, &value);
          if (!value)
            {
              print_memory (instructionCounter, black, cl_default);
              instructionCounter = operand;
              print_memory (instructionCounter, cl_default, black);
              return 0;
            }
          break;
        }
    }
  print_operation ();
  print_instructionCounter ();
  return 0;
}

void
timeout (int signal)
{
  CU ();
}
int
main ()
{
  write (1, "\E[?25l\E[?1c", strlen ("\E[?25l\E[?1c"));
  mt_clrscr ();
  sc_memoryInit ();
  sc_regInit ();
  bc_init ();

  print_terminal ();

  enum keys key;

  signal (SIGALRM, timeout);
  signal (SIGUSR1, reset);

  int value = 0;
  print_flags ();
  while (1)
    {
      sc_regGet (4, &value);
      if (value)
        {
          rk_readkey (&key);
          print_command (key);
        }
    }

  return 0;
}