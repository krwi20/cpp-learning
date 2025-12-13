#include <iostream>
#include <vector>

int main()
{

    int n;
    std::cout << "How many numbers? ";
    std::cin >> n;
    std::vector<int> list(n); // size n, all elements default to

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

    return 0;
}