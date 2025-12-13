#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand(time(0));                // Uses current time as seed -> different sequence every run
    int secret = rand() % 100 + 1; // rand() retuerns a large random integer, % 100 ggives reminder when divided by 100 (0-99), +1 shifts range to 1-100
    std::cout << "Guess the number: \n";

    int attempts = 0;
    int guess;

    do
    {
        std::cout << "Guess the number (1-100): ";
        std::cin >> guess;
        attempts++;

        if (guess < secret)
        {
            std::cout << "Too low!\n";
        }
        else if (guess > secret)
        {
            std::cout << "Too high!\n";
        }
        else
        {
            std::cout << "Correct! You got it in " << attempts << " attempts.\n";
        }

    } while (guess != secret);

    return 0;
}