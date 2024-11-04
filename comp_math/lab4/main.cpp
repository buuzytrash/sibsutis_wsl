#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
    const double precision = 1e-5;
    double degree, lower_bound, upper_bound, curr_precision;
    int free_member;

    cout << "This app can solve equation like : <x^2 - 3 = 0>\nEnter degree of variable : ";
    cin >> degree;

    cout << "Enter free member(without variable) : ";
    cin >> free_member;

    cout << "Enter lower_bound : ";
    cin >> lower_bound;

    cout << "Enter upper_bound : ";
    cin >> upper_bound;

    auto lambda_func = [degree, free_member] (double value) { return pow(value, degree) + free_member; };
    do {
        double half = (lower_bound + upper_bound) / 2;   
        if (lambda_func(lower_bound) * lambda_func(half) < 0) upper_bound = half;
        else lower_bound = half;

        curr_precision = (upper_bound - lower_bound) / 2;

    } while (curr_precision > precision);

    cout << "x = " << (lower_bound + upper_bound) / 2 << endl;
 
}
