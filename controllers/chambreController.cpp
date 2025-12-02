#include "chambreController.h"

ChambreController::ChambreController()
{
}

QList<Chambre> ChambreController::getAllChambres()
{
    QList<Chambre> liste;

    db.openConnection();
    QSqlQuery q("SELECT id, numero, type, prix, etat FROM chambres");

    while(q.next())
    {
        Chambre c;
        c.id = q.value(0).toInt();
        c.numero = q.value(1).toString();
        c.type = q.value(2).toString();
        c.prix = q.value(3).toDouble();
        c.etat = q.value(4).toString();
        liste.append(c);
    }

    db.closeConnection();
    return liste;
}

bool ChambreController::ajouterChambre(QString numero, QString type, QString prix)
{
    db.openConnection();
    QSqlQuery q;

    q.prepare("INSERT INTO chambres (numero, type, prix, etat) VALUES (:n, :t, :p, 'Disponible')");
    q.bindValue(":n", numero);
    q.bindValue(":t", type);
    q.bindValue(":p", prix);

    bool success = q.exec();
    db.closeConnection();
    return success;
}

bool ChambreController::supprimerChambre(QString id)
{
    db.openConnection();
    QSqlQuery q;

    q.prepare("DELETE FROM chambres WHERE id = :id");
    q.bindValue(":id", id);

    bool success = q.exec();
    db.closeConnection();
    return success;
}
