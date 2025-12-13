#include <iostream>
#include <limits>

double add(double a, double b)
{
    //
}

double subtract(double a, double b)
{
    return a - b;
}

double multiply(double a, double b)
{
    return a * b;
}

double divide(double a, double b)
{
    if (b == 0)
    {
        std::cout << "Error: Division by zero!\n";
        return 0;
    }
    return a / b;
}

int main()
{
    char calcAgain;

    do
    {
        double num1, num2;
        char op;

        std::cout << "Enter first number: ";
        std::cin >> num1;

        std::cout << "Enter operator (+, -, *, /): ";
        std::cin >> op;

        std::cout << "Enter second number: ";
        std::cin >> num2;

        double result;

        if (op == '+')
        {
            result = add(num1, num2);
        }
        else if (op == '-')
        {
            result = subtract(num1, num2);
        }
        else if (op == '*')
        {
            result = multiply(num1, num2);
        }
        else if (op == '/')
        {
            result = divide(num1, num2);
        }
        else
        {
            std::cout << "Error: Invalid operator!\n";
            continue; // skip to next loop iteration
        }

        std::cout << "Result: " << num1 << " " << op << " " << num2 << " = " << result << "\n";

        // Ask to calculate again
        std::cout << "Calculate again? (y/n): ";
        std::cin >> calcAgain;

        // Clear any extra input (e.g., if user types "yes" instead of "y")
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (calcAgain == 'y' || calcAgain == 'Y');

    return 0;
}