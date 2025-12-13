#include <iostream>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{

    int num1 = 5;
    int num2 = 10;

    std::cout << "Before swap: " << num1 << " " << num2 << "\n";

    swap(num1, num2);

    std::cout << "After swap: " << num1 << " " << num2 << "\n";

    int x = 42;
    std::cout << &x << "\n";

    int *p = &x;
    std::cout << p << " Should match above\n";
    std::cout << *p << " Should print value of x 42\n";
    *p = 100;
    std::cout << p << "\n";
    std::cout << x << " Is what happened to x\n";

    int a = 10;
    int b = 20;
    int *ptr = &a;
    *ptr = 99;
    ptr = &b; // Now points to b
    *ptr = 88;
    // What are a and b now?
    std::cout << "a: " << a << ", b: " << b << "\n";

    return 0;
}