#ifndef CONNEXIONDB_H
#define CONNEXIONDB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

class ConnexionDB
{
public:
    ConnexionDB(); // Constructeur
    bool openConnection(); // Pour ouvrir la connexion
    void closeConnection(); // Pour fermer (bonnes pratiques)
    QSqlDatabase getDatabase() const; // Pour récupérer l'objet db si besoin

private:
    QSqlDatabase db; // L'objet Qt qui gère la connexion
};

#endif // CONNEXIONDB_H