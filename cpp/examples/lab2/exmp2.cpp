#include <iostream>
#include <string>

int
main ()
{
  std::string text{ "A friend in need is a friend indeed." };
  std::string word{ "friend" };
  std::cout << text.length () << " " << word.length () << std::endl;
  unsigned count{}; // количество вхождений
  for (unsigned i{}; i <= text.length () - word.length ();)
    {
      // получаем индекс
      size_t position = text.find (word, i);
      // если не найдено ни одного вхождения с индекса i, выходим из цикла
      if (position == std::string::npos)
        break;
      // если же вхождение найдено, увеличиваем счетчик вхождений
      ++count;
      // переходим к следующему индексу после position
      i = position + 1;
    }
  std::cout << "The word is found " << count << " times."
            << std::endl; // The word is found 2 times.
}