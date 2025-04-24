
#include <iostream>
#include <string>
using namespace std;

// ================== CONSTANTS ================== //
const int MAX_CUSTOMERS = 100;
const int MAX_ADMINS = 5;
const int MAX_TRANSACTIONS = 100;

// ================== ACCOUNT CLASS ================== //
class Account {
private:
    int accountID;
    string holderName;
    string accountType;
    double balance;

public:
    Account() {
        accountID = -1;
        holderName = "";
        accountType = "";
        balance = 0.0;
    }

    void create(int id, string name, string type, double initialBalance) {
        accountID = id;
        holderName = name;
        accountType = type;
        balance = initialBalance;
    }

    void display() {
        if (accountID == -1) {
            cout << "No account exists." << endl;
            return;
        }
        cout << "\n--- Account Details ---" << endl;
        cout << "Account ID: " << accountID << endl;
        cout << "Holder Name: " << holderName << endl;
        cout << "Account Type: " << accountType << endl;
        cout << "Balance: $" << balance << endl;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount Deposited Successfully. New Balance: $" << balance << endl;
        } else {
            cout << "Invalid Deposit Amount." << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Amount Withdrawn Successfully. New Balance: $" << balance << endl;
            return true;
        } else {
            cout << "Insufficient Balance or Invalid Amount." << endl;
            return false;
        }
    }

    int getID() { return accountID; }
    double getBalance() { return balance; }

    void deleteAccount() {
        accountID = -1;
        holderName = "";
        accountType = "";
        balance = 0.0;
    }
};

// ================== TRANSACTION CLASS ================== //
class Transaction {
public:
    int fromID, toID;
    double amount;
    string type;

    void log(int from, int to, double amt, string t) {
        fromID = from;
        toID = to;
        amount = amt;
        type = t;
    }

    void print() {
        cout << "Type: " << type << " | From: " << fromID << " | To: " << toID << " | Amount: $" << amount << endl;
    }
};

// ================== USER BASE CLASS ================== //
class User {
protected:
    string username;
    string password;

public:
    User() {}
    User(string u, string p) : username(u), password(p) {}
    bool login(string u, string p) { return username == u && password == p; }
    virtual void showMenu() = 0;
};

// Forward declaration
class Customer;

// ================== ADMIN CLASS ================== //
class Admin : public User {
public:
    Admin(string u, string p) : User(u, p) {}
    void showMenu() override;
};

// ================== CUSTOMER CLASS ================== //
class Customer : public User {
private:
    int accountID;

public:
    Customer() {}
    Customer(string u, string p, int accID) : User(u, p), accountID(accID) {}
    int getAccountID() { return accountID; }
    void showMenu() override;
    void viewMyAccount();
    void depositToMyAccount();
    void withdrawFromMyAccount();
};

// ================== GLOBAL VARIABLES ================== //
Account accounts[MAX_CUSTOMERS];
Transaction transactions[MAX_TRANSACTIONS];
Admin admins[MAX_ADMINS] = { Admin("admin", "1234") };
Customer customers[MAX_CUSTOMERS] = { Customer("user1", "pass1", 101) };

int accountCount = 0;
int customerCount = 1;
int transactionCount = 0;

// ================== UTILITY FUNCTIONS ================== //
int findAccountIndex(int id) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].getID() == id) return i;
    }
    return -1;
}

void logTransaction(int fromID, int toID, double amount, string type) {
    if (transactionCount < MAX_TRANSACTIONS) {
        transactions[transactionCount++].log(fromID, toID, amount, type);
    }
}

void showTransactions() {
    cout << "\n--- Transaction History ---" << endl;
    for (int i = 0; i < transactionCount; i++) {
        transactions[i].print();
    }
}

void createAccount() {
    if (accountCount >= MAX_CUSTOMERS) {
        cout << "Account limit reached!" << endl;
        return;
    }

    int id;
    string name, type;
    double balance;

    cout << "\nEnter Account ID: "; cin >> id;
    if (findAccountIndex(id) != -1) {
        cout << "Account with this ID already exists!" << endl;
        return;
    }

    cout << "Enter Holder Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Account Type: ";
    getline(cin, type);
    cout << "Enter Initial Balance: ";
    cin >> balance;

    accounts[accountCount++].create(id, name, type, balance);
    cout << "Account created successfully!" << endl;
}

void viewAccount() {
    int id;
    cout << "\nEnter Account ID to view: ";
    cin >> id;
    int index = findAccountIndex(id);
    if (index != -1) accounts[index].display();
    else cout << "Account not found!" << endl;
}

void deleteAccount() {
    int id;
    cout << "\nEnter Account ID to delete: ";
    cin >> id;
    int index = findAccountIndex(id);
    if (index != -1) {
        accounts[index].deleteAccount();
        cout << "Account deleted successfully." << endl;
    } else cout << "Account not found!" << endl;
}

void depositToAccount() {
    int id;
    double amount;
    cout << "\nEnter Account ID: "; cin >> id;
    int index = findAccountIndex(id);
    if (index != -1) {
        cout << "Enter amount to deposit: "; cin >> amount;
        accounts[index].deposit(amount);
        logTransaction(id, id, amount, "Deposit");
    } else cout << "Account not found!" << endl;
}

void withdrawFromAccount() {
    int id;
    double amount;
    cout << "\nEnter Account ID: "; cin >> id;
    int index = findAccountIndex(id);
    if (index != -1) {
        cout << "Enter amount to withdraw: "; cin >> amount;
        if (accounts[index].withdraw(amount)) {
            logTransaction(id, id, amount, "Withdraw");
        }
    } else cout << "Account not found!" << endl;
}

void transferAmount() {
    int fromID, toID;
    double amount;
    cout << "\nEnter Sender Account ID: "; cin >> fromID;
    cout << "Enter Receiver Account ID: "; cin >> toID;
    if (fromID == toID) { cout << "Cannot transfer to same account." << endl; return; }
    int fromIndex = findAccountIndex(fromID);
    int toIndex = findAccountIndex(toID);
    if (fromIndex != -1 && toIndex != -1) {
        cout << "Enter amount to transfer: "; cin >> amount;
        if (accounts[fromIndex].withdraw(amount)) {
            accounts[toIndex].deposit(amount);
            logTransaction(fromID, toID, amount, "Transfer");
        }
    } else cout << "One or both accounts not found!" << endl;
}

// ================== ADMIN MENU ================== //
void Admin::showMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---" << endl;
        cout << "1. Create Account\n2. View Account\n3. Delete Account\n4. Show Transactions\n0. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: deleteAccount(); break;
            case 4: showTransactions(); break;
            case 0: cout << "Logging out..." << endl; break;
            default: cout << "Invalid option." << endl;
        }
    } while (choice != 0);
}

// ================== CUSTOMER METHODS ================== //
void Customer::viewMyAccount() {
    int index = findAccountIndex(accountID);
    if (index != -1) accounts[index].display();
    else cout << "Account not found!" << endl;
}

void Customer::depositToMyAccount() {
    int index = findAccountIndex(accountID);
    if (index != -1) {
        double amount;
        cout << "Enter deposit amount: "; cin >> amount;
        accounts[index].deposit(amount);
        logTransaction(accountID, accountID, amount, "Deposit");
    }
}

void Customer::withdrawFromMyAccount() {
    int index = findAccountIndex(accountID);
    if (index != -1) {
        double amount;
        cout << "Enter withdrawal amount: "; cin >> amount;
        if (accounts[index].withdraw(amount)) {
            logTransaction(accountID, accountID, amount, "Withdraw");
        }
    }
}

void Customer::showMenu() {
    int choice;
    do {
        cout << "\n--- Customer Menu ---" << endl;
        cout << "1. View My Account\n2. Deposit\n3. Withdraw\n0. Logout\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: viewMyAccount(); break;
            case 2: depositToMyAccount(); break;
            case 3: withdrawFromMyAccount(); break;
            case 0: cout << "Logging out..." << endl; break;
            default: cout << "Invalid option." << endl;
        }
    } while (choice != 0);
}

// ================== LOGIN SYSTEM ================== //
void loginSystem() {
    string u, p;
    cout << "\nUsername: "; cin >> u;
    cout << "Password: "; cin >> p;

    for (int i = 0; i < MAX_ADMINS; i++) {
        if (admins[i].login(u, p)) {
            cout << "Admin logged in.\n";
            admins[i].showMenu();
            return;
        }
    }
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].login(u, p)) {
            cout << "Customer logged in.\n";
            customers[i].showMenu();
            return;
        }
    }
    cout << "Invalid credentials.\n";
}

// ================== MAIN ================== //
int main() {
    int choice;
    do {
        cout << "\n===== BANK SYSTEM =====" << endl;
        cout << "1. Login\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: loginSystem(); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
