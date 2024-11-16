#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

// Class representing a single bank account
class BankAccount {
public:
    int accountNumber;
    string name;
    float balance;

    // Default constructor
    BankAccount() : accountNumber(0), name(""), balance(0.0f) {}

    // Parameterized constructor
    BankAccount(int accNum, const string& accName)
        : accountNumber(accNum), name(accName), balance(0.0f) {}

    void deposit(float amount) {
        if (amount <= 0) {
            cout << "Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
        cout << "Deposited ₹" << amount << ". New balance: ₹" << balance << "\n";
    }

    void withdraw(float amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive.\n";
            return;
        }
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            cout << "Withdrew ₹" << amount << ". New balance: ₹" << balance << "\n";
        }
    }

    void displayAccountInfo() const {
        cout << "\n--- Account Information ---\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder: " << name << "\n";
        cout << "Balance: ₹" << balance << "\n";
    }
};

// Class managing multiple bank accounts
class BankManagementSystem {
private:
    unordered_map<int, BankAccount> accounts;
    int nextAccountNumber;

public:
    BankManagementSystem() : nextAccountNumber(1) {}

    void createAccount(const string& name) {
        if (name.empty()) {
            cout << "Account holder's name cannot be empty!\n";
            return;
        }
        BankAccount newAccount(nextAccountNumber, name);
        accounts[nextAccountNumber] = newAccount;
        cout << "Account created successfully! Account Number: " << nextAccountNumber << "\n";
        nextAccountNumber++;
    }

    void viewAccount(int accountNumber) const {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            it->second.displayAccountInfo();
        } else {
            cout << "Account not found!\n";
        }
    }

    void depositMoney(int accountNumber, float amount) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            it->second.deposit(amount);
        } else {
            cout << "Account not found!\n";
        }
    }

    void withdrawMoney(int accountNumber, float amount) {
        auto it = accounts.find(accountNumber);
        if (it != accounts.end()) {
            it->second.withdraw(amount);
        } else {
            cout << "Account not found!\n";
        }
    }

    void menu() const {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Create Account\n";
        cout << "2. View Account\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
    }

    void run() {
        int choice;

        while (true) {
            menu();
            cin >> choice;

            // Input validation for numeric input
            if (cin.fail()) {
                cin.clear();             // Clear the error flag
                cin.ignore(1000, '\n');  // Discard invalid input
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            switch (choice) {
                case 1: {
                    string name;
                    cout << "Enter account holder's name: ";
                    cin.ignore(); // Clear newline character from input buffer
                    getline(cin, name);
                    createAccount(name);
                    break;
                }
                case 2: {
                    int accountNumber;
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    viewAccount(accountNumber);
                    break;
                }
                case 3: {
                    int accountNumber;
                    float amount;
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    depositMoney(accountNumber, amount);
                    break;
                }
                case 4: {
                    int accountNumber;
                    float amount;
                    cout << "Enter account number: ";
                    cin >> accountNumber;
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    withdrawMoney(accountNumber, amount);
                    break;
                }
                case 5:
                    cout << "Exiting... Thank you for using the Bank Management System.\n";
                    return; // Exit the program
                default:
                    cout << "Invalid choice! Please try again.\n";
                    break;
            }
        }
    }
};

int main() {
    BankManagementSystem bms;
    bms.run();
    return 0;
}
