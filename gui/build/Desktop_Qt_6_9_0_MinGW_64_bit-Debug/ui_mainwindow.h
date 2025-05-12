/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *createAccountButton;
    QPushButton *viewAccountButton;
    QPushButton *depositButton;
    QPushButton *withdrawButton;
    QPushButton *deleteAccountButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 400);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        usernameLineEdit = new QLineEdit(centralwidget);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setGeometry(QRect(100, 30, 200, 30));
        passwordLineEdit = new QLineEdit(centralwidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(100, 70, 200, 30));
        passwordLineEdit->setEchoMode(QLineEdit::Password);
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(150, 110, 100, 30));
        createAccountButton = new QPushButton(centralwidget);
        createAccountButton->setObjectName("createAccountButton");
        createAccountButton->setGeometry(QRect(140, 160, 120, 30));
        viewAccountButton = new QPushButton(centralwidget);
        viewAccountButton->setObjectName("viewAccountButton");
        viewAccountButton->setGeometry(QRect(140, 200, 120, 30));
        depositButton = new QPushButton(centralwidget);
        depositButton->setObjectName("depositButton");
        depositButton->setGeometry(QRect(140, 240, 120, 30));
        withdrawButton = new QPushButton(centralwidget);
        withdrawButton->setObjectName("withdrawButton");
        withdrawButton->setGeometry(QRect(140, 280, 120, 30));
        deleteAccountButton = new QPushButton(centralwidget);
        deleteAccountButton->setObjectName("deleteAccountButton");
        deleteAccountButton->setGeometry(QRect(140, 320, 120, 30));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Bank Management System", nullptr));
        usernameLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        createAccountButton->setText(QCoreApplication::translate("MainWindow", "Create Account", nullptr));
        viewAccountButton->setText(QCoreApplication::translate("MainWindow", "View Account", nullptr));
        depositButton->setText(QCoreApplication::translate("MainWindow", "Deposit", nullptr));
        withdrawButton->setText(QCoreApplication::translate("MainWindow", "Withdraw", nullptr));
        deleteAccountButton->setText(QCoreApplication::translate("MainWindow", "Delete Account", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
