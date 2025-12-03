#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "chambreController.h"
#include "EmployeController.h" // <--- AJOUT

namespace Ui { class Dashboard; }

class Dashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dashboard(QString role, QWidget *parent = nullptr);
    ~Dashboard();

private slots:
    // --- Chambres ---
    void on_btnAjouterChambre_clicked();
    void on_btnSauvegarder_clicked();
    void on_btnSupprimerChambre_clicked();
    void on_tableChambres_cellClicked(int, int);


    // --- Employés (NOUVEAU) ---
    void on_btnAjouterEmp_clicked();
    void on_btnSauvegarderEmp_clicked();
    void on_btnEmployes_clicked();

private:
    Ui::Dashboard *ui;
    QString currentRole;
    
    // Contrôleurs
    ChambreController chambreCtrl;
    EmployeController employeCtrl; // <--- AJOUT

    // Variables d'état pour modification
    int idChambreEnModif = -1;
    int idEmployeEnModif = -1;     // <--- AJOUT

    // Fonctions
    void chargerListeChambres();
    void chargerListeEmployes();   // <--- AJOUT
    void applyingRole();
};

#endif // DASHBOARD_H
