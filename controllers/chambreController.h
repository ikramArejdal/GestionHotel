#ifndef CHAMBRECONTROLLER_H
#define CHAMBRECONTROLLER_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include "Chambre.h"
#include "connexionDB.h"

class ChambreController
{
public:
    ChambreController();

    QList<Chambre> getAllChambres();
    bool ajouterChambre(QString numero, QString type, QString prix);
    bool supprimerChambre(QString id);

private:
    ConnexionDB db;
};

#endif
