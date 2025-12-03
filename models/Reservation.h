#ifndef RESERVATION_H
#define RESERVATION_H


#include <QDate>

class Reservation
{
public:
public:
    int id;
    int client_id;
    int chambre_id;
    QDate dateEntree;
    QDate dateSortie;
    double montantTotal;
    
    // Pour l'affichage dans le tableau, on aura besoin des noms, pas juste des IDs
    QString nomClient;
    QString numeroChambre;

    Reservation() {}
};
#endif // RESERVATION_H