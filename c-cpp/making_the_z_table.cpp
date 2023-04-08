#include <cmath>
#include <gmpxx.h>
#include <iomanip>
#include <iostream>

using namespace std; // :)

long double pdf_of_x(long double x, long double pi, long double euler_num) {
    return (1.00 / sqrt(2.00 * pi)) * pow(euler_num, -0.50 * pow(x, 2.00));
}

long double integral_to_x(long double x, long double pi, long double euler_num) {
    long double result = 0.00;
    for (long double num = -10.00; num <= x; num += 0.001) {
        result += pdf_of_x(num, pi, euler_num) * 0.001;
    }
    return result;
}

int le_signum(auto number) {
    if (number > )
}

int main() {
    long double pi = 3.1415926535897932384626433832795028841;
    long double e = 2.71828182845904523536028747135266249775;
    cout << fixed << setprecision(7) << "|       ";

    for (long double a = 0.00; a < 0.09; a += 0.01) {
        cout << "|" << a;
    }

    cout << "|" << endl;

    for (long double x = -4.00; x < 4.10; x += 0.1) {
        cout << setprecision(4) << "|" << x;
        cout << setprecision(7) << "|" << integral_to_x(x, pi, e);
        for (long double y = 0.01; y < 0.09; y += 0.01) {
            if 
            long double z = integral_to_x(x + y, pi, e);
            cout << "|" << z;
        }
        cout << "|" << endl;
    }
    return 0;
}
