#include <iostream>
#include <string>
using namespace std;

int
main ()
{

  string string1 = "Tom went to water the crops and water.";

  int value = string1.find ("water");

  cout << value << endl;

  if (string1.find ("banana") == std::string::npos)
    {
      std::cout << "Not found" << std::endl;
    }

  //   value = string1.find ("dinner");

  //   cout << value << endl;
}