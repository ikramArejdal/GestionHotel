#include "EmployeController.h"

EmployeController::EmployeController() {}

QList<Employe> EmployeController::getAllEmployes()
{
    QList<Employe> liste;
    db.openConnection();
    QSqlQuery q("SELECT id, nom, prenom, poste, telephone, salaire FROM employes");
    while(q.next()) {
        Employe e;
        e.id = q.value(0).toInt();
        e.nom = q.value(1).toString();
        e.prenom = q.value(2).toString();
        e.poste = q.value(3).toString();
        e.telephone = q.value(4).toString();
        e.salaire = q.value(5).toDouble();
        liste.append(e);
    }
    db.closeConnection();
    return liste;
}

bool EmployeController::ajouterEmploye(QString nom, QString prenom, QString poste, QString tel, double salaire)
{
    db.openConnection();
    QSqlQuery q;
    q.prepare("INSERT INTO employes (nom, prenom, poste, telephone, salaire) VALUES (:n, :pr, :po, :t, :s)");
    q.bindValue(":n", nom);
    q.bindValue(":pr", prenom);
    q.bindValue(":po", poste);
    q.bindValue(":t", tel);
    q.bindValue(":s", salaire);
    bool ok = q.exec();
    db.closeConnection();
    return ok;
}

bool EmployeController::modifierEmploye(int id, QString nom, QString prenom, QString poste, QString tel, double salaire)
{
    db.openConnection();
    QSqlQuery q;
    q.prepare("UPDATE employes SET nom=:n, prenom=:pr, poste=:po, telephone=:t, salaire=:s WHERE id=:id");
    q.bindValue(":n", nom);
    q.bindValue(":pr", prenom);
    q.bindValue(":po", poste);
    q.bindValue(":t", tel);
    q.bindValue(":s", salaire);
    q.bindValue(":id", id);
    bool ok = q.exec();
    db.closeConnection();
    return ok;
}

bool EmployeController::supprimerEmploye(int id)
{
    db.openConnection();
    QSqlQuery q;
    q.prepare("DELETE FROM employes WHERE id = :id");
    q.bindValue(":id", id);
    bool ok = q.exec();
    db.closeConnection();
    return ok;
}