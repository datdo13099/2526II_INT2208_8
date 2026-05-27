#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <iomanip>

std::string classify_triangle(double a, double b, double c);

int main() {
    std::vector<std::tuple<double, double, double, std::string>> test_data = {
        // Equilateral
        {5, 5, 5, "Equilateral"}, {1, 1, 1, "Equilateral"}, {100, 100, 100, "Equilateral"},
        // Isosceles
        {5, 5, 7, "Isosceles"}, {7, 5, 5, "Isosceles"}, {5, 7, 5, "Isosceles"},
        {10, 10, 15, "Isosceles"}, {15, 10, 10, "Isosceles"}, {20, 30, 20, "Isosceles"},
        // Scalene
        {3, 4, 5, "Scalene"}, {5, 6, 7, "Scalene"}, {6, 8, 10, "Scalene"},
        {7, 8, 9, "Scalene"}, {10, 20, 25, "Scalene"},
        // Not a Triangle
        {1, 2, 3, "Not a Triangle"}, {1, 2, 4, "Not a Triangle"}, {1, 5, 2, "Not a Triangle"},
        {5, 1, 2, "Not a Triangle"}, {2, 3, 5, "Not a Triangle"},
        // Invalid Input
        {0, 5, 5, "Invalid Input"}, {-5, 5, 5, "Invalid Input"}, {101, 5, 5, "Invalid Input"},
        {5, 0, 5, "Invalid Input"}, {5, 101, 5, "Invalid Input"}, {5, 5, 0, "Invalid Input"},
        {5, 5, 101, "Invalid Input"}
    };

    std::cout << "Running tests...\n";
    int passed = 0, failed = 0;

    for (const auto& tc : test_data) {
        double a = std::get<0>(tc);
        double b = std::get<1>(tc);
        double c = std::get<2>(tc);
        std::string expected = std::get<3>(tc);

        std::string result = classify_triangle(a, b, c);
        std::string status = (result == expected) ? "PASS" : "FAIL";

        std::cout << status << " TC(" 
                  << std::setw(3) << a << ", " << std::setw(3) << b << ", " << std::setw(3) << c 
                  << ")=> Expected: " << std::left << std::setw(15) << expected 
                  << " | Got: " << std::left << std::setw(15) << result << "\n";

        if (result == expected) passed++;
        else failed++;
    }

    std::string separator(60, '=');
    std::cout << "\n" << separator << "\n"
              << "Total: " << test_data.size() << " | Passed: " << passed << " | Failed: " << failed << "\n"
              << separator << "\n";

    return 0;
}