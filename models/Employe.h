#ifndef EMPLOYE_H
#define EMPLOYE_H

#include <QString>

class Employe
{
public:
    int id;
    QString nom;
    QString prenom;
    QString poste;
    QString telephone;
    double salaire;
    // Constructeur par défaut
    Employe() {}

    // Constructeur complet (optionnel mais pratique)
    Employe(int i, QString n, QString p, QString post, QString tel,double s)
        : id(i), nom(n), prenom(p), poste(post), salaire(s) {}
};

#endif // EMPLOYE_H
