#include "clientController.h"

ClientController::ClientController()
{
}

QList<Client> ClientController::getAllClients()
{
    QList<Client> liste;

    db.openConnection();
    QSqlQuery q("SELECT id, nom, prenom, cin, telephone FROM clients");

    while(q.next())
    {
        Client c;
        c.setId(q.value(0).toInt()) ;
        c.setNom(q.value(1).toString());
        c.setPrenom(q.value(2).toString());
        c.setCin(q.value(3).toString());
        c.setTelephone(q.value(4).toString());
        liste.append(c);
    }

    db.closeConnection();
    return liste;
}

bool ClientController::ajouterClient(QString nom, QString prenom, QString cin, QString telephone)
{
    db.openConnection();
    QSqlQuery q;

    q.prepare("INSERT INTO clients (nom, prenom, cin, telephone) VALUES (:nom, :prenom, :cin, :telephone)");
    q.bindValue(":nom", nom);
    q.bindValue(":prenom", prenom);
    q.bindValue(":cin", cin);
    q.bindValue(":telephone", telephone);

    bool success = q.exec();
    db.closeConnection();
    return success;
}

bool ClientController::supprimerClient(QString id)
{
    db.openConnection();
    QSqlQuery q;

    q.prepare("DELETE FROM clients WHERE id = :id");
    q.bindValue(":id", id);

    bool success = q.exec();
    db.closeConnection();
    return success;
}

Client ClientController::getClientById(int id)
{
    db.openConnection();   // IMPORTANT
    QSqlQuery query;
    query.prepare("SELECT id, nom, prenom, cin, telephone FROM clients WHERE id = :id");
    query.bindValue(":id", id);

    Client c;

    if (query.exec() && query.next()) {
        c.setId(query.value("id").toInt());
        c.setNom(query.value("nom").toString());
        c.setPrenom(query.value("prenom").toString());
        c.setCin(query.value("cin").toString());
        c.setTelephone(query.value("telephone").toString());
    }

    db.closeConnection();
    return c;
}


bool ClientController::modifierClient(int id, QString nom, QString prenom, QString cin, QString telephone)
{
    db.openConnection();   // OBLIGATOIRE

    QSqlQuery query;
    query.prepare("UPDATE clients SET nom = :nom, prenom = :prenom, cin = :cin, telephone = :telephone WHERE id = :id");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":cin", cin);
    query.bindValue(":telephone", telephone);
    query.bindValue(":id", id);

    bool ok = query.exec();

    db.closeConnection();
    return ok;
}
