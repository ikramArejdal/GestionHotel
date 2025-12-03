#ifndef EMPLOYECONTROLLER_H
#define EMPLOYECONTROLLER_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include "Employe.h"
#include "connexionDB.h"

class EmployeController
{
public:
    EmployeController();
    QList<Employe> getAllEmployes();
    bool ajouterEmploye(QString nom, QString prenom, QString poste, QString tel, double salaire);
    bool modifierEmploye(int id, QString nom, QString prenom, QString poste, QString tel, double salaire);
    bool supprimerEmploye(int id);

private:
    ConnexionDB db;
};

#endif