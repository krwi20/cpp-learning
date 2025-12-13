#include <iostream>

int main()
{

    std::cout << "How many number? \n";
    int n;
    std::cin >> n;
    int *list = new int[n];

    for (int i = 0; i < n; i++)
    {
        std::cout << "Enter number " << (i + 1) << ": ";
        std::cin >> list[i];
    }

    std::cout << "You entered: ";
    for (int i = 0; i < n; i++)
    {
        std::cout << list[i] << " ";
    }

    std::cout << "\n";
    delete[] list;  // Must use delete[] for arrays!
    list = nullptr; // optional: good habit to avoid accidental reuse

    return 0;
}