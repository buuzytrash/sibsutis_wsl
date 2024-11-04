#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int
main ()
{
  const unsigned int wordsCollection = 6;

  std::vector<std::string> collection;
  std::string word;
  for (unsigned int i = 0; i < wordsCollection; ++i)
    {
      std::cin >> word;
      collection.push_back (word);
    }

  std::copy (collection.begin (), collection.end (),
             std::ostream_iterator<std::string> (std::cout, "\n"));

  std::cout << collection[0];
}