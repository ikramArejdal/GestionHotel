#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Client
{
private:
    int id;
    QString nom;
    QString prenom;
    QString cin;
    QString telephone;

public:
    // Constructeurs
    Client() {}
    Client(int id, QString nom, QString prenom, QString cin, QString telephone)
    {
        this->id = id;
        this->nom = nom;
        this->prenom = prenom;
        this->cin = cin;
        this->telephone = telephone;
    }

    // Getters
    int getId() const { return id; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getCin() const { return cin; }
    QString getTelephone() const { return telephone; }

    // Setters
    void setId(int id) { this->id = id; }
    void setNom(QString nom) { this->nom = nom; }
    void setPrenom(QString prenom) { this->prenom = prenom; }
    void setCin(QString cin) { this->cin = cin; }
    void setTelephone(QString telephone) { this->telephone = telephone; }
};

#endif 
