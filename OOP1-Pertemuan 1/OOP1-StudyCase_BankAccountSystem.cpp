#include <iostream>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string holderName;
    double balance;

public:
    BankAccount(string accNum, string name, double bal = 0) {
        accountNumber = accNum;
        holderName = name;
        balance = (bal >= 0) ? bal : 0;
    }

    void deposit(double amount) {
        if (amount > 0) balance += amount;
        else cout << "Deposit amount must be positive.\n";
    }

    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) balance -= amount;
        else cout << "Insufficient balance or invalid amount.\n";
    }

    void transfer(BankAccount& target, double amount) {
        if (amount > 0 && amount <= balance) {
            withdraw(amount);
            target.deposit(amount);
        }
        else cout << "Transfer failed: Insufficient balance or invalid amount.\n";
    }

    double getBalance() const { return balance; }
};