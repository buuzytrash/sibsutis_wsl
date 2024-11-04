#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#include <unistd.h>
#include <termios.h>

int main()
{
    char var1, var2;
    int mul1, mul2, degree1, degree2, free_member;

    std::string equation, precision, bounds, out;
    std::fstream file("input.txt");

    std::getline(file, equation);
    std::getline(file, precision);
    std::getline(file, bounds);
    std::getline(file, out);

    std::cout << equation << std::endl;
    std::cout << precision << std::endl;
    std::cout << bounds << std::endl;
    std::cout << out << std::endl;


    std::pair<char, std::pair<int, int>> first_num(var1, std::make_pair(mul1, degree1)), second_num(var2, std::make_pair(mul2, degree2));
    // auto lambda_func = [degree, free_member] (double value) { return pow(value, degree) + free_member; };
 
}
