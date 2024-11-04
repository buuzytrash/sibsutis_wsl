#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

int main()
{
    const double precision = 10e-10;
    double degree, lower_bound, upper_bound;
    int free_member;

    cout << "This app can solve equation like : <x^2 - 3 = 0>\nEnter degree of variable : ";
    cin >> degree;

    cout << "Enter free member(without variable) : ";
    cin >> free_member;

    cout << "Enter lower_bound : ";
    cin >> lower_bound;

    cout << "Enter upper_bound : ";
    cin >> upper_bound;

    double last_c = 0, c = 0;
    auto lambda_func = [degree, free_member] (double value) { return pow(value, degree) + free_member; };
    do {
        last_c = c;
        c = (lower_bound * lambda_func(upper_bound) - upper_bound * lambda_func(lower_bound)) / (lambda_func(upper_bound) - lambda_func(lower_bound));  
        if (lambda_func(lower_bound) * lambda_func(c) < 0) upper_bound = c;
        else lower_bound = c;


    } while ((c - last_c) > precision);

    cout << "x = " << lower_bound << endl;
 
}

