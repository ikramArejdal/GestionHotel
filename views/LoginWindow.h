#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "logincontroller.h" // On inclut le contrôleur
#include "Dashboard.h"             // Pour ouvrir la fenêtre suivante

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_btnLogin_clicked(); // Le seul slot nécessaire pour l'instant

private:
    Ui::LoginWindow *ui;
    LoginController loginController;
    // L'instance du cerveau
};
#endif // LOGINWINDOW_H
