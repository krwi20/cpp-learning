#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

int main()
{
    srand(time(0)); // Uses current time as seed -> different sequence every run
    char playAgain;

    do
    {
        int secret = rand() % 100 + 1; // rand() retuerns a large random integer, % 100 ggives reminder when divided by 100 (0-99), +1 shifts range to 1-100
        int guess;
        int attempts = 0;

        std::cout << "\n🎮 New Game! Guess a number between 1 and 100:\n";

        do
        {
            std::cout << "Your guess: ";

            // Try to read an integer
            if (!(std::cin >> guess))
            {
                // Input failed (e.g., user typed "abc")
                std::cout << "Invalid input! Please enter a number.\n";
                std::cin.clear();                                                   // reset error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip bad input
                continue;                                                           // go back to top of loop
            }

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
                std::cout << "Correct! You got it in " << attempts << " attempts!\n";
            }

        } while (guess != secret);

        // Ask to play again
        std::cout << "\nPlay again? (y/n): ";
        std::cin >> playAgain;

        // Clear any extra input (e.g., if user types "yes" instead of "y")
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Thanks for playing!\n";
    return 0;
}