#include <mySimpleComputer.h>
#include <myTerm.h>

int
main ()
{
  int *rows = malloc (4), *cols = malloc (4);

  mt_getscreensize (rows, cols);
  mt_clrscr ();

  int x, y;
  x = rand () % *cols, y = rand () % *rows;
  char *str1 = " Я ОЧЕНЬ", *str2 = " СИЛЬНО ЛЮБЛЮ ",
       *str3 = " АРХИТЕКТУРУ ЭВМ ";
  srand (time (NULL));
  while (1)
    {
      mt_gotoXY (x, y);
      mt_setfgcolor (green);
      mt_setbgcolor (red);
      write (1, str1, strlen (str1));
      x = rand () % *cols, y = rand () % *rows;

      mt_gotoXY (x, y);
      mt_setfgcolor (yellow);
      mt_setbgcolor (gray);
      write (1, str2, strlen (str2));
      x = rand () % *cols, y = rand () % *rows;

      mt_gotoXY (x, y);
      mt_setfgcolor (gray);
      mt_setbgcolor (violet);
      write (1, str3, strlen (str3));
      x = rand () % *cols, y = rand () % *rows;

      mt_setbgcolor (black);
      mt_setfgcolor (cl_default);
    }

  mt_gotoXY (0, *rows);

  putchar ('\n');
  printf ("rows = %d\ncols = %d\n", *rows, *cols);

  return 0;
}