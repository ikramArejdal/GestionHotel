#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QString>
#include "connexionDB.h"

class LoginController
{
public:
    LoginController();
    
    // Fonction principale : vérifie user/pass et renvoie le rôle (Admin/Receptionniste)
    // Renvoie une chaine vide "" si la connexion échoue
    QString authenticateUser(QString username, QString password);

private:
    ConnexionDB dbManager; // Le contrôleur possède une instance de la DB
};

#endif // LOGINCONTROLLER_H
