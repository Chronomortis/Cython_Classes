#include <iostream>
#include <stdexcept>  // for std::runtime_error
#include "account.h"

// Constructor
    Account::Account(double initial_balance) {
        if (initial_balance < 0) {
            throw std::invalid_argument("Initial balance cannot be negative.");
        }
        balance = initial_balance;
    }

    // Deposit function
    void Account::deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive.");
        }
        balance += amount;
        std::cout << "Deposited: " << amount << " | New Balance: " << balance << std::endl;
    }

    // Withdraw function
    void Account::withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive.");
        }
        if (amount > balance) {
            throw std::runtime_error("Insufficient funds for withdrawal.");
        }
        balance -= amount;
        std::cout << "Withdrew: " << amount << " | Remaining Balance: " << balance << std::endl;
    }

    // Getter for the balance
    double Account::get_balance() const {
        return balance;
    }


/*
int main() {
    try {
        // Create an account with an initial balance of 100
        Account my_account(100);

        // Perform valid operations
        my_account.deposit(50);   // Successful deposit
        my_account.withdraw(30);  // Successful withdrawal

        // Perform invalid operations to trigger exceptions
        my_account.withdraw(200);  // Will throw exception (insufficient funds)
    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;
}
*/
