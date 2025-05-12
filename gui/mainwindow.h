#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Account.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();
    void on_createAccountButton_clicked();
    void on_viewAccountButton_clicked();
    void on_depositButton_clicked();
    void on_withdrawButton_clicked();
    void on_deleteAccountButton_clicked();

private:
    Ui::MainWindow *ui;
    Account accounts[10];
    int accountCount = 0;
};

#endif // MAINWINDOW_H
