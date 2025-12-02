#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "chambreController.h"


namespace Ui {
class Dashboard;
}

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QString role,QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    // Slot automatique pour le bouton ajouter
    void on_btnAjouterChambre_clicked();
    void on_btnSupprimerChambre_clicked();

private:
    Ui::Dashboard *ui;
    ChambreController chambreCtrl;
    QString currentRole;

    // Fonction pour récupérer la liste depuis MySQL et remplir le tableau
    void chargerListeChambres();
    void appliquerRole();
};

#endif // DASHBOARD_H
