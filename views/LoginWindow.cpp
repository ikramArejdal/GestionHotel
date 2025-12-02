#include "LoginWindow.h"
#include "ui_LoginWindow.h" // Attention au chemin (parfois "ui_LoginWindow.h" suffit)
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnLogin_clicked()
{
    QString user = ui->txtUser->text();
    QString pass = ui->txtPass->text();

    // APPEL AU CONTROLEUR (Le cerveau travaille)
    QString resultRole = loginController.authenticateUser(user, pass);

    // ANALYSE DU RESULTAT
    if (resultRole == "ERROR_DB") {
        QMessageBox::critical(this, "Erreur Critique", "Impossible de se connecter à la base de données !");
    } 
    else if (resultRole != "") {
        // Connexion réussie
       QMessageBox::information(this, "Bienvenue", "Connexion réussie !");
Dashboard *dash = new Dashboard(resultRole);
dash->show();
this->close();
// Fermer le login
    } 
    else {
        // Connexion échouée
        QMessageBox::warning(this, "Erreur", "Identifiant ou mot de passe incorrect.");
    }
}
