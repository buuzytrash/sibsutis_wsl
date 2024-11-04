#include <myBigChars.h>

unsigned int *big_chars;

int
bc_init ()
{
  big_chars = malloc (150);
  int fd = open ("/home/ayusha/second-year/comp_arch/my-first-project/BigChar",
                 O_RDONLY),
      count = 0;
  bc_bigcharread (fd, big_chars, 18, &count);

  return 0;
}

int
bc_printA (char *str)
{
  char *esc = malloc (20);
  int bytes = 0;

  sprintf (esc, "\E(0%s\E(B", str);
  bytes = write (1, esc, strlen (esc));

  if (bytes == 0)
    return 0;
  return -1;
}

int
bc_box (int x1, int y1, int x2, int y2)
{
  for (int i = x1; i < x2; i++)
    {
      mt_gotoXY (i, y1);
      bc_printA (HOR);
      mt_gotoXY (i, y2);
      bc_printA (HOR);
    }
  for (int i = y1; i < y2; i++)
    {
      mt_gotoXY (x1, i);
      bc_printA (VERT);
      mt_gotoXY (x2, i);
      bc_printA (VERT);
    }
  mt_gotoXY (x1, y1);
  bc_printA (UP_L_CORN);
  mt_gotoXY (x2, y1);
  bc_printA (UP_R_CORN);
  mt_gotoXY (x1, y2);
  bc_printA (LOW_L_CORN);
  mt_gotoXY (x2, y2);
  bc_printA (LOW_R_CORN);

  return 0;
}

int
bc_printbigchar (unsigned int arr[2], int x, int y, enum colors fg,
                 enum colors bg)
{
  int rows, cols;
  mt_getscreensize (&rows, &cols);
  if (x < 0 || y < 0 || x > cols || y > rows)
    return -1;

  for (int i = 0; i < 8; i++)
    {
      mt_gotoXY (x, y++);
      for (int j = 0; j < 8; j++)
        {
          int value;
          bc_getbigcharpos (arr, j, i, &value);
          if (value)
            {
              mt_setbgcolor (bg);
              mt_setfgcolor (fg);
              bc_printA (CAGE);
            }
          else
            {
              bc_printA (" ");
            }
          mt_setbgcolor (cl_default);
        }
    }

  return 0;
}

int
bc_setbigcharpos (unsigned int *big, int x, int y, int value)
{
  if ((value != 0 && value != 1) || x < 0 || x > 7 || y < 0 || y > 7)
    return -1;

  int index = y / 4, place = y % 4, num = 1;

  num <<= ((4 - place) * 8 - x - 1);

  if (value)
    {
      big[index] |= num;
    }
  else
    {
      big[index] &= ~num;
    }

  return 0;
}

int
bc_getbigcharpos (unsigned int *big, int x, int y, int *value)
{
  if (x < 0 || x > 7 || y < 0 || y > 7)
    return -1;

  int num = (y / 4) ? big[1] : big[0];
  *value = (num >> ((4 - y % 4) * 8 - x - 1)) & 1;

  return 0;
}

int
bc_bigcharwrite (int fd, unsigned int *big, int count)
{
  write (fd, big, sizeof (count) * 2 * count);
  close (fd);
  return 0;
}
int
bc_bigcharread (int fd, unsigned int *big, int need_count, int *count)
{
  *count = read (fd, big, sizeof (need_count) * 2 * need_count) / 8;
  if (*count == 0)
    {
      return -1;
    }
  close (fd);
  return 0;
}