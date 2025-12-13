#include <iostream>

void swapPointers(int *a, int *b)
{
    int temp = *a; // get value at address a
    *a = *b;       // put value of b into a's location
    *b = temp;     // put temp (old a) into b's location
}

void reverseArray(int *arr, int size)
{
    if (size <= 1)
        return; // nothing to reverse

    int *left = arr;             // points to first element
    int *right = arr + size - 1; // points to last element

    while (left < right)
    { // stop when they meet or cross
        swapPointers(left, right);
        left++;  // move forward
        right--; // move backward
    }
}

int main()
{

    int numbers[3] = {10, 20, 30};
    std::cout << numbers[0] << "\n";
    std::cout << numbers[1] << "\n";
    std::cout << numbers[2] << "\n";
    std::cout << "\n";

    int *p = numbers;
    std::cout << *p << "\n";
    std::cout << *(p + 1) << "\n";
    std::cout << *(p + 2) << "\n";
    std::cout << "\n";

    int arr[3] = {5, 10, 15};
    int *q = &arr[1]; // q points to the *middle* element
    std::cout << *q << "\n";
    std::cout << *(q - 1) << "\n";
    std::cout << *(q + 1) << "\n";
    std::cout << "\n";

    int arr1[5] = {1, 2, 3, 4, 5};
    std::cout << "Before: ";
    for (int i = 0; i < 5; i++)
        std::cout << arr1[i] << " ";
    std::cout << "\n";

    reverseArray(arr1, 5);

    std::cout << "After:  ";
    for (int i = 0; i < 5; i++)
        std::cout << arr1[i] << " ";
    std::cout << "\n";
    return 0;

    return 0;
}