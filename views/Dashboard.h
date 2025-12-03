#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "chambreController.h"
#include "EmployeController.h"

namespace Ui { class Dashboard; }

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QString role, QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    // --- Slots Chambres ---
    void on_btnAjouterChambre_clicked();
    void on_btnSauvegarder_clicked();

    // --- Slots Employés ---
    void on_btnAjouterEmp_clicked();
    void on_btnSauvegarderEmp_clicked();

    // Le bouton pour changer d'onglet (celui du haut)
    void on_btnEmployes_clicked();

    // Note : On a SUPPRIMÉ les slots de réservation et de suppression chambre
    // car ils sont gérés ailleurs ou différemment.

private:
    Ui::Dashboard *ui;
    QString currentRole;

    // Contrôleurs
    ChambreController chambreCtrl;
    EmployeController employeCtrl;

    // Variables pour modification
    int idChambreEnModif = -1;
    int idEmployeEnModif = -1;

    // Fonctions d'affichage
    void chargerListeChambres();
    void chargerListeEmployes();
    void applyingRole();
};

#endif // DASHBOARD_H
