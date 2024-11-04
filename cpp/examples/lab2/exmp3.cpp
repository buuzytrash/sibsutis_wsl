#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int
main ()
{
  std::string str = "Dr. Jekyll and Mr. Hyde";

  std::vector<std::string> AS;

  //   AS.push_back ("as");
  //   AS.push_back ("pidor");

  auto it = std::remove_if (str.begin (), str.end (), ::ispunct);
  str.erase (it, str.end ());

  for (int i = 0; i < str.length (); i++)
    {
      if (isupper (str[i]))
        {
          str[i] = tolower (str[i]);
        }
    }

  std::cout << AS[1] << " " << AS[0] << std::endl;

  //   std::string s;
  std::stringstream s (str);
  std::string ss;
  int i = 0;
  int j = 0;

  printf ("before while\n");

  while (s >> ss)
    {
      printf ("is okay\n");

      printf ("is okay\n");
      AS.push_back (ss);
      ss.clear ();
      std::cout << AS[i] << std::endl;
      i++;
    }

  std::cout << str << std::endl;

  return 0;
}