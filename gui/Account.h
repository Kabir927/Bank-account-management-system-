#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account {
private:
    int accountID;
    QString holderName;
    QString accountType;
    double balance;

public:
    Account() : accountID(-1), balance(0.0) {}

    void create(int id, const QString &name, const QString &type, double initialBalance) {
        accountID = id;
        holderName = name;
        accountType = type;
        balance = initialBalance;
    }

    QString display() const {
        if (accountID == -1) {
            return "No account exists.";
        }
        return QString("Account ID: %1\nHolder Name: %2\nAccount Type: %3\nBalance: $%4")
            .arg(accountID)
            .arg(holderName)
            .arg(accountType)
            .arg(QString::number(balance));
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }

    int getID() const { return accountID; }
    double getBalance() const { return balance; }

    void deleteAccount() {
        accountID = -1;
        holderName.clear();
        accountType.clear();
        balance = 0.0;
    }
};

#endif // ACCOUNT_H
