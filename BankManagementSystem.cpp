#include <iostream>
#include <string>
using namespace std;

const int MAX_CUSTOMERS = 100;
const int MAX_ADMINS = 5;
const int MAX_TRANSACTIONS = 100;

class Account {
private:
    int accountID;
    string holderName;
    string accountType;
    double balance;

public:
    Account() : accountID(-1), balance(0.0) {}

    void create(int id, const string& name, const string& type, double initialBalance) {
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
        cout << "\n--- Account Details ---\n";
        cout << "Account ID: " << accountID << "\nHolder Name: " << holderName
             << "\nAccount Type: " << accountType << "\nBalance: $" << balance << endl;
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
        holderName.clear();
        accountType.clear();
        balance = 0.0;
    }
};

class Transaction {
public:
    int fromID, toID;
    double amount;
    string type;

    void log(int from, int to, double amt, const string& t) {
        fromID = from;
        toID = to;
        amount = amt;
        type = t;
    }

    void print() {
        cout << "Type: " << type << " | From: " << fromID << " | To: " << toID << " | Amount: $" << amount << endl;
    }
};

class User {
protected:
    string username, password;

public:
    User() {}
    User(const string& u, const string& p) : username(u), password(p) {}
    bool login(const string& u, const string& p) { return username == u && password == p; }
    virtual void showMenu() = 0;
};

class Customer;

class Admin : public User {
public:
    Admin() {}
    Admin(const string& u, const string& p) : User(u, p) {}
    void showMenu() override;
};

class Customer : public User {
private:
    int accountID;

public:
    Customer() {}
    Customer(const string& u, const string& p, int accID) : User(u, p), accountID(accID) {}
    int getAccountID() { return accountID; }
    void showMenu() override;
    void viewMyAccount();
    void depositToMyAccount();
    void withdrawFromMyAccount();
};

Account accounts[MAX_CUSTOMERS];
Transaction transactions[MAX_TRANSACTIONS];
Admin admins[MAX_ADMINS];
Customer customers[MAX_CUSTOMERS] = { Customer("user1", "pass1", 101) };

int accountCount = 0;
int customerCount = 1;
int transactionCount = 0;
int adminCount = 1;

int findAccountIndex(int id) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].getID() == id) return i;
    }
    return -1;
}

void logTransaction(int fromID, int toID, double amount, const string& type) {
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

    cout << "\nEnter Account ID: ";
    cin >> id;
    if (findAccountIndex(id) != -1) {
        cout << "Account with this ID already exists!" << endl;
        return;
    }

    cin.ignore();
    cout << "Enter Holder Name: ";
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
    } else {
        cout << "Account not found!" << endl;
    }
}

void depositToAccount() {
    int id;
    double amount;
    cout << "\nEnter Account ID: ";
    cin >> id;
    int index = findAccountIndex(id);
    if (index != -1) {
        cout << "Enter amount to deposit: ";
        cin >> amount;
        accounts[index].deposit(amount);
        logTransaction(id, id, amount, "Deposit");
    } else {
        cout << "Account not found!" << endl;
    }
}

void withdrawFromAccount() {
    int id;
    double amount;
    cout << "\nEnter Account ID: ";
    cin >> id;
    int index = findAccountIndex(id);
    if (index != -1) {
        cout << "Enter amount to withdraw: ";
        cin >> amount;
        if (accounts[index].withdraw(amount)) {
            logTransaction(id, id, amount, "Withdraw");
        }
    } else {
        cout << "Account not found!" << endl;
    }
}

void transferAmount() {
    int fromID, toID;
    double amount;
    cout << "\nEnter Sender Account ID: ";
    cin >> fromID;
    cout << "Enter Receiver Account ID: ";
    cin >> toID;
    if (fromID == toID) {
        cout << "Cannot transfer to same account." << endl;
        return;
    }
    int fromIndex = findAccountIndex(fromID);
    int toIndex = findAccountIndex(toID);
    if (fromIndex != -1 && toIndex != -1) {
        cout << "Enter amount to transfer: ";
        cin >> amount;
        if (accounts[fromIndex].withdraw(amount)) {
            accounts[toIndex].deposit(amount);
            logTransaction(fromID, toID, amount, "Transfer");
        }
    } else {
        cout << "One or both accounts not found!" << endl;
    }
}

void Admin::showMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n1. Create Account\n2. View Account\n3. Delete Account\n4. Show Transactions\n0. Logout\nChoice: ";
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

void Customer::viewMyAccount() {
    int index = findAccountIndex(accountID);
    if (index != -1) accounts[index].display();
    else cout << "Account not found!" << endl;
}

void Customer::depositToMyAccount() {
    int index = findAccountIndex(accountID);
    if (index != -1) {
        double amount;
        cout << "Enter deposit amount: ";
        cin >> amount;
        accounts[index].deposit(amount);
        logTransaction(accountID, accountID, amount, "Deposit");
    }
}

void Customer::withdrawFromMyAccount() {
    int index = findAccountIndex(accountID);
    if (index != -1) {
        double amount;
        cout << "Enter withdrawal amount: ";
        cin >> amount;
        if (accounts[index].withdraw(amount)) {
            logTransaction(accountID, accountID, amount, "Withdraw");
        }
    }
}

void Customer::showMenu() {
    int choice;
    do {
        cout << "\n--- Customer Menu ---\n1. View My Account\n2. Deposit\n3. Withdraw\n0. Logout\nChoice: ";
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

void loginSystem() {
    string u, p;
    cout << "\nUsername: ";
    cin >> u;
    cout << "Password: ";
    cin >> p;

    for (int i = 0; i < adminCount; i++) {
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

int main() {
    admins[0] = Admin("admin", "1234");
    int choice;
    do {
        cout << "\n===== BANK SYSTEM =====\n1. Login\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: loginSystem(); break;
            case 0: cout << "Goodbye!" << endl; break;
            default: cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
