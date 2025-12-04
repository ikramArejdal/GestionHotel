#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include "client.h"
#include "connexionDB.h"

class ClientController
{
public:
    ClientController();

    QList<Client> getAllClients();
    bool ajouterClient(QString nom, QString prenom, QString cin, QString telephone);
    bool supprimerClient(QString id);
    Client getClientById(int id);
    bool modifierClient(int id, QString nom, QString prenom, QString cin, QString telephone);

private:
    ConnexionDB db;
};

#endif
