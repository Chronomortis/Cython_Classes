#ifndef ACCOUNT_H  // Include guard to prevent multiple inclusions
#define ACCOUNT_H

#include <stdexcept>  // for std::runtime_error and std::invalid_argument

class Account {
private:
    double balance;  // Private member to hold the account balance

public:
    // Constructor that accepts an initial balance
    Account(double initial_balance);

    // Function to deposit money into the account
    void deposit(double amount);

    // Function to withdraw money from the account
    void withdraw(double amount);

    // Getter function to retrieve the current balance
    double get_balance() const;
};

#endif  // ACCOUNT_H
