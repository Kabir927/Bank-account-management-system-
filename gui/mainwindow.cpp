#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Bank Management System");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_loginButton_clicked()
{
    QString u = ui->usernameLineEdit->text();
    QString p = ui->passwordLineEdit->text();

    if (u == "admin" && p == "1234") {
        QMessageBox::information(this, "Login", "Admin logged in.");
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}

void MainWindow::on_createAccountButton_clicked()
{
    if (accountCount >= 10) {
        QMessageBox::warning(this, "Error", "Account limit reached.");
        return;
    }
    bool ok1, ok2, ok3;
    int id = QInputDialog::getInt(this, "Create Account", "Enter Account ID:", 0, 0, 9999, 1, &ok1);
    QString name = QInputDialog::getText(this, "Create Account", "Enter Holder Name:", QLineEdit::Normal, "", &ok2);
    QString type = QInputDialog::getText(this, "Create Account", "Enter Account Type:", QLineEdit::Normal, "", &ok3);

    if (ok1 && ok2 && ok3) {
        accounts[accountCount++].create(id, name, type, 0.0);
        QMessageBox::information(this, "Success", "Account created successfully.");
    } else {
        QMessageBox::warning(this, "Cancelled", "Account creation cancelled.");
    }
}

void MainWindow::on_viewAccountButton_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "View Account", "Enter Account ID:", 0, 0, 9999, 1, &ok);
    if (ok) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].getID() == id) {
                QMessageBox::information(this, "Account Details", accounts[i].display());
                return;
            }
        }
        QMessageBox::warning(this, "Not Found", "Account not found.");
    }
}

void MainWindow::on_depositButton_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Deposit", "Enter Account ID:", 0, 0, 9999, 1, &ok);
    if (ok) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].getID() == id) {
                double amt = QInputDialog::getDouble(this, "Deposit", "Enter Amount:", 0, 0);
                accounts[i].deposit(amt);
                QMessageBox::information(this, "Success", "Amount deposited successfully.");
                return;
            }
        }
        QMessageBox::warning(this, "Not Found", "Account not found.");
    }
}

void MainWindow::on_withdrawButton_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Withdraw", "Enter Account ID:", 0, 0, 9999, 1, &ok);
    if (ok) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].getID() == id) {
                double amt = QInputDialog::getDouble(this, "Withdraw", "Enter Amount:", 0, 0);
                if (accounts[i].withdraw(amt))
                    QMessageBox::information(this, "Success", "Amount withdrawn successfully.");
                else
                    QMessageBox::warning(this, "Failed", "Insufficient balance.");
                return;
            }
        }
        QMessageBox::warning(this, "Not Found", "Account not found.");
    }
}

void MainWindow::on_deleteAccountButton_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Delete Account", "Enter Account ID:", 0, 0, 9999, 1, &ok);
    if (ok) {
        for (int i = 0; i < accountCount; ++i) {
            if (accounts[i].getID() == id) {
                accounts[i].deleteAccount();
                QMessageBox::information(this, "Deleted", "Account deleted successfully.");
                return;
            }
        }
        QMessageBox::warning(this, "Not Found", "Account not found.");
    }
}
