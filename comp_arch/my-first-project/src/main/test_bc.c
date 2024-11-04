#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <unistd.h>

int
main ()
{
  mt_clrscr ();
  sc_memoryInit ();
  sc_regInit ();
  bc_init ();

  int k = 1;
  bc_setbigcharpos (big_chars, 0, 0, 1);
  bc_setbigcharpos (big_chars, 1, 1, 0);

  for (int i = 0; i < 18; i++)
    {
      bc_box (i * 10, 0, k * 10, 10);
      k++;
      bc_printbigchar (big_chars + i * 2, k + i * 9, 2, green, green);
    }

  int j = 0;
  bc_box (1, 11, 10, 20);
  while (1)
    {
      if (sleep (1) == 0)
        {
          bc_printbigchar (big_chars + j * 2, 2, 12, green, green);
          mt_gotoXY (15, 15);
        }
      if (j == 18)
        {
          j = 0;
        }
      j++;
    }
  return 0;
}