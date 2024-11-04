#include <myTerm.h>

int
mt_clrscr ()
{
  char buff[] = "\E[H\E[J";
  unsigned bytes = 0;

  bytes = write (1, buff, strlen (buff));
  if (bytes == 0)
    return -1;
  return 0;
}

int
mt_gotoXY (int x, int y)
{
  int rows = 0, cols = 0;

  mt_getscreensize (&rows, &cols);
  if ((y < rows) && (x < cols) && (y >= 0) && (x >= 0))
    {
      char *buf = malloc (11);
      sprintf (buf, "\E[%d;%dH", y, x);
      write (1, buf, strlen (buf));

      free (buf);
      return 0;
    }
  return -1;
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize w;
  if (!ioctl (STDOUT_FILENO, TIOCGWINSZ, &w))
    {
      *rows = w.ws_row;
      *cols = w.ws_col;

      return 0;
    }
  return -1;
}

int
mt_setfgcolor (enum colors color)
{
  char *buf = malloc (6);
  int bytes = 0;
  switch (color)
    {
    case cl_default:
      strcpy (buf, "\E[39m");
      bytes = write (1, buf, strlen (buf));
      break;
    case black:
      strcpy (buf, "\E[30m");
      bytes = write (1, buf, strlen (buf));
      break;
    case red:
      strcpy (buf, "\E[31m");
      bytes = write (1, buf, strlen (buf));
      break;
    case green:
      strcpy (buf, "\E[32m");
      bytes = write (1, buf, strlen (buf));
      break;
    case yellow:
      strcpy (buf, "\E[33m");
      bytes = write (1, buf, strlen (buf));
      break;
    case blue:
      strcpy (buf, "\E[34m");
      bytes = write (1, buf, strlen (buf));
      break;
    case violet:
      strcpy (buf, "\E[35m");
      bytes = write (1, buf, strlen (buf));
      break;
    case aquamarine:
      strcpy (buf, "\E[36m");
      bytes = write (1, buf, strlen (buf));
      break;
    case gray:
      strcpy (buf, "\E[37m");
      bytes = write (1, buf, strlen (buf));
      break;
    default:
      return -1;
    }
  if (bytes == 0)
    {
      free (buf);
      return -1;
    }
  else
    {
      free (buf);
      return 0;
    }
}
int
mt_setbgcolor (enum colors color)
{
  char *buf = malloc (20);
  int bytes = 0;
  switch (color)
    {
    case cl_default:
      strcpy (buf, "\E[49m");
      bytes = write (1, buf, strlen (buf));
      break;
    case black:
      strcpy (buf, "\E[40m");
      bytes = write (1, buf, strlen (buf));
      break;
    case red:
      strcpy (buf, "\E[41m");
      bytes = write (1, buf, strlen (buf));
      break;
    case green:
      strcpy (buf, "\E[42m");
      bytes = write (1, buf, strlen (buf));
      break;
    case yellow:
      strcpy (buf, "\E[43m");
      bytes = write (1, buf, strlen (buf));
      break;
    case blue:
      strcpy (buf, "\E[44m");
      bytes = write (1, buf, strlen (buf));
      break;
    case violet:
      strcpy (buf, "\E[45m");
      bytes = write (1, buf, strlen (buf));
      break;
    case aquamarine:
      strcpy (buf, "\E[46m");
      bytes = write (1, buf, strlen (buf));
      break;
    case gray:
      strcpy (buf, "\E[47m");
      bytes = write (1, buf, strlen (buf));
      break;
    default:
      return -1;
    }
  if (bytes == 0)
    {
      free (buf);
      return -1;
    }
  else
    {
      free (buf);
      return 0;
    }
}