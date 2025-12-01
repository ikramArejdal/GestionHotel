#include "logincontroller.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

LoginController::LoginController()
{
    // Rien de spécial à construire pour l'instant
}

QString LoginController::authenticateUser(QString username, QString password)
{
    // 1. On ouvre la base de données
    if (!dbManager.openConnection()) {
        return "ERROR_DB"; // Code d'erreur spécial
    }

    // 2. On prépare la requête (Sécurisée contre les injections SQL)
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE username = :user AND passwordHash = :pass");
    query.bindValue(":user", username);
    query.bindValue(":pass", password);

    // 3. On exécute
    if (query.exec()) {
        if (query.next()) {
            // Utilisateur trouvé ! On retourne son rôle
            QString role = query.value("role").toString();
            dbManager.closeConnection(); // On ferme proprement
            return role;
        }
    } else {
        qDebug() << "Erreur Requete :" << query.lastError().text();
    }

    dbManager.closeConnection();
    return ""; // Retourne vide si introuvable
}