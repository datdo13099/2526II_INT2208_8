#include <string>

std::string classify_triangle(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0 || a > 100 || b > 100 || c > 100) {
        return "Invalid Input";
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return "Not a Triangle";
    }
    if (a == b && b == c) {
        return "Equilateral";
    }
    if (a == b || a == c || b == c) {
        return "Isosceles";
    }
    return "Scalene";
}