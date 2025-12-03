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
    bool ajouterChambre(QString numero, QString type, double prix);
    bool supprimerChambre(QString id);
    bool modifierChambre(int id, QString numero, QString type, double prix, QString etat);
private:
    ConnexionDB db;
};

#endif
