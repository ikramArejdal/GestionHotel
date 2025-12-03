#ifndef RESERVATIONCONTROLLER_H
#define RESERVATIONCONTROLLER_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include "Reservation.h"
#include "connexionDB.h"

class ReservationController
{
public:
    ReservationController();
    
    bool ajouterReservation(int clientId, int chambreId, QDate dateIn, QDate dateOut, double total);
    QList<Reservation> getAllReservations();
    bool supprimerReservation(int id);
    
    // Vérifie si une chambre est libre entre deux dates
    bool isChambreDisponible(int chambreId, QDate dateIn, QDate dateOut);

private:
    ConnexionDB db;
};

#endif
