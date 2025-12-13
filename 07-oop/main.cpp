#include <iostream>

class BankAccount
{
private:
    double balance;

public:
    // Constructor
    BankAccount(double initialBalance);

    // Public interface
    void deposit(double amount);
    bool withdraw(double amount); // returns true if successful
    double getBalance() const;    // 'const' means it doesn't modify the object
};

// Defining
BankAccount::BankAccount(double initialBalance)
{
    balance = initialBalance;
}

void BankAccount::deposit(double amount)
{
    if (amount <= 0)
    {
        std::cout << "Deposit amount must be positive!\n";
        return;
    }

    balance += amount;
}

bool BankAccount::withdraw(double amount)
{
    if (amount > 0 && amount <= balance)
    {
        balance -= amount;
        return true;
    }
    return false; // failed
}

// get balance const = doesnt change the object
double BankAccount::getBalance() const
{
    return balance;
}

class SavingsAccount : public BankAccount
{
private:
    double interestRate; // e.g. 0.05 for 5%

public:
    SavingsAccount(double initialBalance, double rate);
    void addInterest();
};

SavingsAccount::SavingsAccount(double initialBalance, double rate) : BankAccount(initialBalance) // call parent constructor
{

    interestRate = rate;
}

void SavingsAccount::addInterest()
{
    deposit(getBalance() * interestRate); // reuse existing deposit
}

int main()
{
    BankAccount myAccount(50.0);       // start with $50
    SavingsAccount savings(100, 0.05); // $100 5% interest
    std::cout << "Savings balance: $" << savings.getBalance() << "\n";
    savings.addInterest();

    myAccount.deposit(1);
    std::cout << "Balance: $" << myAccount.getBalance() << "\n";

    bool success = myAccount.withdraw(0); // tries to withdraw $100
    if (!success)
    {
        std::cout << "Withdrawal failed: insufficient funds.\n";
    }

    std::cout << "Final balance: $" << myAccount.getBalance() << "\n";
    std::cout << "Final savings balance: $" << savings.getBalance() << "\n";
    return 0;
}
