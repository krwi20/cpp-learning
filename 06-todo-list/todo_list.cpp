#include <iostream>
#include <vector>
#include <string>

int main()
{

    std::vector<std::string> tasks; // tasks array
    char choice;

    do
    {
        std::cout << "\n--- To-Do List ---\n";
        std::cout << "a) Add task\n";
        std::cout << "l) List tasks\n";
        std::cout << "r) Remove task\n";
        std::cout << "q) Quit\n";
        std::cout << "Choose: ";
        std::cin >> choice;

        if (choice == 'a')
        {
            std::cout << "Enter task: ";
            std::string task;
            std::cin.ignore(); // clear leftover newline from cin >>
            std::getline(std::cin, task);
            tasks.push_back(task);
            std::cout << "Task added!\n";
        }
        else if (choice == 'l')
        {
            if (tasks.empty())
            {
                std::cout << "No tasks yet!\n";
            }
            else
            {
                for (size_t i = 0; i < tasks.size(); i++)
                { // size_t is the type returned by .size()—it’s an unsigned integer (safe for indexes).
                    std::cout << (i + 1) << ". " << tasks[i] << "\n";
                }
            }
        }
        else if (choice == 'r')
        {
            if (tasks.empty())
            {
                std::cout << "No tasks yet!\n";
            }
            else
            {
                std::cout << "Enter task number to remove: ";
                int index;
                std::cin >> index;
                if (index >= 1 && index <= (int)tasks.size())
                {
                    tasks.erase(tasks.begin() + index - 1);
                    std::cout << "Task removed.\n";
                }
                else
                {
                    std::cout << "Invalid task number!\n";
                }
            }
        }

    } while (choice != 'q');

    return 0;
}