#include "ReservationController.h"
#include <QDebug>

ReservationController::ReservationController() {}

bool ReservationController::ajouterReservation(int clientId, int chambreId, QDate dateIn, QDate dateOut, double total)
{
    // 1. Vérifier la disponibilité avant d'insérer
    if (!isChambreDisponible(chambreId, dateIn, dateOut)) {
        return false; 
    }

    db.openConnection();
    QSqlQuery q;
    q.prepare("INSERT INTO reservations (client_id, chambre_id, dateEntree, dateSortie, montant_total) "
              "VALUES (:c, :ch, :de, :ds, :mt)");
    q.bindValue(":c", clientId);
    q.bindValue(":ch", chambreId);
    q.bindValue(":de", dateIn);
    q.bindValue(":ds", dateOut);
    q.bindValue(":mt", total);

    bool success = q.exec();
    db.closeConnection();
    return success;
}

bool ReservationController::isChambreDisponible(int chambreId, QDate dateIn, QDate dateOut)
{
    db.openConnection();
    QSqlQuery q;
    // Cette requête vérifie s'il existe une réservation qui chevauche les dates demandées
    q.prepare("SELECT COUNT(*) FROM reservations WHERE chambre_id = :id AND "
              "NOT (dateSortie <= :dateIn OR dateEntree >= :dateOut)");
    q.bindValue(":id", chambreId);
    q.bindValue(":dateIn", dateIn);
    q.bindValue(":dateOut", dateOut);
    
    q.exec();
    q.next();
    int count = q.value(0).toInt();
    
    db.closeConnection();
    
    // Si count == 0, la chambre est libre. Si > 0, elle est occupée.
    return (count == 0);
}

QList<Reservation> ReservationController::getAllReservations()
{
    QList<Reservation> liste;
    db.openConnection();
    // On fait des JOINS pour récupérer le nom du client et le numéro de chambre au lieu des ID
    QSqlQuery q("SELECT r.id, c.nom, c.prenom, ch.numero, r.dateEntree, r.dateSortie, r.montant_total "
                "FROM reservations r "
                "JOIN clients c ON r.client_id = c.id "
                "JOIN chambres ch ON r.chambre_id = ch.id");
    
    while(q.next()) {
        Reservation r;
        r.id = q.value(0).toInt();
        r.nomClient = q.value(1).toString() + " " + q.value(2).toString();
        r.numeroChambre = q.value(3).toString();
        r.dateEntree = q.value(4).toDate();
        r.dateSortie = q.value(5).toDate();
        r.montantTotal = q.value(6).toDouble();
        liste.append(r);
    }
    db.closeConnection();
    return liste;
}

bool ReservationController::supprimerReservation(int id)
{
    db.openConnection();
    QSqlQuery q;
    q.prepare("DELETE FROM reservations WHERE id = :id");
    q.bindValue(":id", id);
    bool ok = q.exec();
    db.closeConnection();
    return ok;
}