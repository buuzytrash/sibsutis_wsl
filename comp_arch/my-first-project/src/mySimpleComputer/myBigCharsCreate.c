#include <myBigChars.h>

int
main ()
{
  int fd = open ("/home/ayusha/second-year/comp_arch/my-first-project/BigChar",
                 O_WRONLY | O_CREAT);
  if (fd < 0)
    perror ("Ошибка открытия файла");
  unsigned int b[36] = {
    0x3c428181, 0x8181423c, 0x3878d818, 0x1818187e, 0x7ec30106, 0x186080ff,
    0xff02040f, 0x0101817e, 0x0e122242, 0xff020202, 0xff8080ff, 0x010101ff,
    0x183060c0, 0xff8181ff, 0xff03060c, 0x183060c0, 0xff818181, 0xff8181ff,
    0xff8181ff, 0x03060c18, 0x3c66c381, 0xff818181, 0xfec1c1c1, 0xfec1c1fe,
    0x3fc0c0c0, 0xc0c0c03f, 0xfec1c1c1, 0xc1c1c1fe, 0xffc0c0c0, 0xffc0c0ff,
    0xffc0c0c0, 0xfcc0c0c0, 0x181818ff, 0xff181818, 0x000000ff, 0xff000000,
  };

  bc_bigcharwrite (fd, b, 18);
}