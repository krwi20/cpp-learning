#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Book
{
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool checkedOut;

public:
    // Constructor
    Book(std::string t, std::string a, std::string id) : title(t), author(a), isbn(id), checkedOut(false) {}

    // Getters (REMEMBER NO PARAMS)
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getIsbn() const { return isbn; }
    bool isAvailable() const { return !checkedOut; }

    // Actions (modify internal state)
    void checkOut()
    {
        if (!checkedOut)
        {
            checkedOut = true;
            std::cout << "Checked out: " << title << "\n";
        }
        else
        {
            std::cout << "Already checked out: " << title << "\n";
        }
    }

    void returnBook()
    {
        if (checkedOut)
        {
            checkedOut = false;
            std::cout << "Returned: " << title << "\n";
        }
        else
        {
            std::cout << "Already available: " << title << "\n";
        }
    }

    // For loading only
    void setCheckedOut(bool status)
    {
        checkedOut = status;
    }
};

// Library is a seperate class
class Library
{
private:
    std::vector<Book> books; // holds many Book objects

public:
    void addBook(const std::string &title, const std::string &author, const std::string &isbn);
    void listBooks() const;
    void checkOutBook(const std::string &isbn);
    void returnBook(const std::string &isbn);
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
};

void Library::addBook(const std::string &title, const std::string &author, const std::string &isbn)
{
    Book newBook(title, author, isbn); // uses your book constructor
    books.push_back(newBook);          // Can replace this with books.emplace_back(title, author, isbn); (constructs book in place)
}

void Library::listBooks() const
{
    if (books.empty())
    {
        std::cout << "No books in the library.\n";
        return;
    }

    int index = 1;
    for (const Book &book : books)
    { // const& = safe, efficient read-only acces
        std::cout << index << ". ";
        if (book.isAvailable())
        {
            std::cout << "[Available] ";
        }
        else
        {
            std::cout << "[Unavailable] ";
        }

        std::cout << book.getTitle() << " by " << book.getAuthor() << " (ISBN: " << book.getIsbn() << ")\n";
        index++;
    }
}

void Library::checkOutBook(const std::string &isbn)
{
    for (Book &book : books)
    {
        if (book.getIsbn() == isbn)
        {
            book.checkOut();
            return;
        }
    }

    std::cout << "Book with ISBN " << isbn << " not found.\n";
}

void Library::returnBook(const std::string &isbn)
{
    for (Book &book : books)
    {
        if (book.getIsbn() == isbn)
        {
            book.returnBook();
            return;
        }
    }

    std::cout << "Book with ISBN " << isbn << " not found.\n";
}

void Library::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename); // open file for writing
    if (!file.is_open())
    {
        std::cout << "Could not open file for saving: " << filename << "\n";
        return;
    }

    for (const Book &book : books)
    {
        file << book.getTitle() << "|" << book.getAuthor() << "|" << book.getIsbn() << "|" << (book.isAvailable() ? "0" : "1") << "\n"; // if available write 0 else 1
    }
    file.close();
    std::cout << "Library saved to " << filename << "\n";
}

void Library::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename); // open file for reading
    if (!file.is_open())
    {
        std::cout << "File not found: " << filename << ". Starting with empty library.\n";
        return;
    }

    books.clear(); // clear exisiting books

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        // Find the positions of the '|' seperators
        size_t first = line.find('|');
        size_t second = line.find('|', first + 1);
        size_t third = line.find('|', second + 1);

        if (first == std::string::npos || second == std::string::npos || third == std::string::npos)
        {
            std::cout << "Skipping invalid line: " << line << "\n";
            continue;
        }

        std::string title = line.substr(0, first);
        std::string author = line.substr(first + 1, second - first - 1);
        std::string isbn = line.substr(second + 1, third - second - 1);
        std::string checkedStr = line.substr(third + 1);

        bool checkedOut = (checkedStr == "1");

        Book book(title, author, isbn);
        if (checkedOut)
        {
            book.setCheckedOut(true);
        }
        books.push_back(book);
    }
    file.close();
    std::cout << "Library loaded from " << filename << "\n";
}

int main()
{
    Library lib;
    lib.addBook("1984", "Orwell", "111");
    lib.checkOutBook("111");
    lib.saveToFile("library.txt");

    Library lib2;
    lib2.loadFromFile("library.txt");
    lib2.listBooks(); // should show [] 1984...
    return 0;
}