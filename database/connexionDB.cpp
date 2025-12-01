#include "connexionDB.h"

ConnexionDB::ConnexionDB()
{
    // On vérifie si une connexion existe déjà pour éviter les doublons
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("hotel_gestion"); // Votre nom de base phpMyAdmin
        db.setUserName("root");
        db.setPassword(""); // Vide par défaut sur XAMPP
    }
}

bool ConnexionDB::openConnection()
{
    if (db.isOpen()) {
        return true;
    }

    if (db.open()) {
        qDebug() << "Connexion DB reussie !";
        return true;
    } else {
        qDebug() << "Erreur Connexion DB :" << db.lastError().text();
        return false;
    }
}

void ConnexionDB::closeConnection()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "Connexion DB fermee.";
    }
}

QSqlDatabase ConnexionDB::getDatabase() const
{
    return db;
}