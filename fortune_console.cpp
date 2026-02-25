#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Account {
    int accountNumber;
    string name;
    string password;
    double balance;
    vector<string> history;
};

vector<Account> accounts;
Account* loggedIn = nullptr;
int nextAccountNo = 2; // Start from 2 since Admin is 1

// Create new account
void createAccount() {
    Account acc;
    acc.accountNumber = nextAccountNo++;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, acc.name);
    cout << "Set a password: ";
    cin >> acc.password;
    acc.balance = 0;
    acc.history.push_back("Account created with balance 0");
    accounts.push_back(acc);
    cout << "Account created successfully! Your Account Number is "
         << acc.accountNumber << endl;
}

// Login to account
void login() {
    int accNo;
    string pass;
    cout << "Enter account number: ";
    cin >> accNo;
    cout << "Enter password: ";
    cin >> pass;

    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo && acc.password == pass) {
            loggedIn = &acc;
            cout << "Login successful! Welcome, " << acc.name << endl;
            return;
        }
    }
    cout << "Login failed! Wrong account number or password.\n";
}

// Check balance
void checkBalance() {
    cout << "Balance: " << loggedIn->balance << endl;
}

// Deposit money
void deposit() {
    double amount;
    cout << "Enter amount to deposit: ";
    cin >> amount;
    loggedIn->balance += amount;
    loggedIn->history.push_back("Deposited " + to_string(amount));
    cout << "Deposited. New balance: " << loggedIn->balance << endl;
}

// Withdraw money
void withdraw() {
    double amount;
    cout << "Enter amount to withdraw: ";
    cin >> amount;
    if (amount <= loggedIn->balance) {
        loggedIn->balance -= amount;
        loggedIn->history.push_back("Withdrew " + to_string(amount));
        cout << "Withdrawn. Remaining balance: " << loggedIn->balance << endl;
    } else {
        cout << "Insufficient funds!\n";
        loggedIn->history.push_back("Failed withdrawal of " + to_string(amount));
    }
}

// Transfer money
void transfer() {
    int targetAccNo;
    double amount;
    cout << "Enter target account number: ";
    cin >> targetAccNo;
    cout << "Enter amount to transfer: ";
    cin >> amount;

    if (amount > loggedIn->balance) {
        cout << "Insufficient funds!\n";
        loggedIn->history.push_back("Failed transfer of " + to_string(amount));
        return;
    }

    for (auto &acc : accounts) {
        if (acc.accountNumber == targetAccNo && &acc != loggedIn) {
            loggedIn->balance -= amount;
            acc.balance += amount;
            loggedIn->history.push_back("Transferred " + to_string(amount) +
                                        " to " + acc.name);
            acc.history.push_back("Received " + to_string(amount) +
                                  " from " + loggedIn->name);
            cout << "Transferred " << amount << " to " << acc.name << endl;
            return;
        }
    }
    cout << "Target account not found!\n";
}

// Show transaction history
void showHistory() {
    cout << "\n--- Transaction History for " << loggedIn->name << " ---\n";
    for (string h : loggedIn->history) {
        cout << "- " << h << endl;
    }
}

int main() {
    // Show welcome banner
    cout << "=====================================\n";
    cout << "      Welcome to Fortune Bank!       \n";
    cout << "=====================================\n";

    // Create default Admin account
    Account admin;
    admin.accountNumber = 1;
    admin.name = "Admin";
    admin.password = "1234";
    admin.balance = 2000;
    admin.history.push_back("Admin account created with balance 2000");
    accounts.push_back(admin);

    int choice;
    while (true) {
        if (loggedIn == nullptr) {
            cout << "\n--- Banking System ---\n";
            cout << "1. Create Account\n";
            cout << "2. Login\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) createAccount();
            else if (choice == 2) login();
            else if (choice == 0) break;
            else cout << "Invalid choice!\n";
        } else {
            cout << "\n--- Dashboard (" << loggedIn->name << ") ---\n";
            cout << "1. Check Balance\n";
            cout << "2. Deposit\n";
            cout << "3. Withdraw\n";
            cout << "4. Transfer\n";
            cout << "5. Show History\n";
            cout << "6. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) checkBalance();
            else if (choice == 2) deposit();
            else if (choice == 3) withdraw();
            else if (choice == 4) transfer();
            else if (choice == 5) showHistory();
            else if (choice == 6) {
                cout << "Logged out.\n";
                loggedIn = nullptr;
            }
            else cout << "Invalid choice!\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
