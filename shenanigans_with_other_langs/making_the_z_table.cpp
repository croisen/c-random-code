#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>

using namespace std; // :)

long double pdf_of_x(long double x, long double pi, long double euler_num) {
    return (1.00 / sqrt(2.00 * pi)) * pow(euler_num, -0.50 * pow(x, 2.00));
}

long double integral_to_x(long double x, long double pi, long double euler_num) {
    long double result = 0.00;
    for (long double num = -10.00; num <= x; num += 0.001) {
        result += pdf_of_x(num, pi, euler_num);
    }
    return result;
}

int main() {
    long double pi = static_cast<long double>(numbers::pi);
    long double e = pow((1.00 + (1.00 / 10000000.00)), 10000000.00);
    cout << fixed << setprecision(7) << "|       ";

    for (long double a = 0.00; a < 0.1; a += 0.01) {
        cout << "|" << a;
    }

    cout << "|" << endl;

    for (long double x = -4.00; x < 4.10; x += 0.1) {
        cout << setprecision(4) << "|" << x;
        cout << setprecision(7) << "|" << integral_to_x(x, pi, e) / 1000.00;
        for (long double y = 0.01; y < 0.1; y += 0.01) {
            long double z = integral_to_x(x + y, pi, e) / 1000.00;
            cout << "|" << z;
        }
        cout << "|" << endl;
    }
    return 0;
}
