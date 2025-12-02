#ifndef CHAMBRE_H
#define CHAMBRE_H

#include <QString>

class Chambre
{
public:
    int id;
    QString numero;
    QString type;
    double prix;
    QString etat;

    // Constructeur par défaut
    Chambre() {}

    // Constructeur complet (optionnel mais pratique)
    Chambre(int id, QString n, QString t, double p, QString e) 
        : id(id), numero(n), type(t), prix(p), etat(e) {}
};

#endif // CHAMBRE_H