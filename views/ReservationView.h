#ifndef RESERVATIONVIEW_H
#define RESERVATIONVIEW_H

#include <QWidget>
#include "ReservationController.h"

namespace Ui {
class ReservationView;
}

class ReservationView : public QWidget
{
    Q_OBJECT

public:
    explicit ReservationView(QWidget *parent = nullptr);
    ~ReservationView();

    // Fonction publique pour rafraichir les listes (utile quand on ajoute un nouveau client)
    void rafraichirDonnees();

private slots:
    void on_btnValiderRes_clicked();
    
    // Slots pour recalculer le prix automatiquement
    void recalculerPrix();

private:
    Ui::ReservationView *ui;
    ReservationController resCtrl;

    void chargerReservations();
    void remplirComboBoxes(); // Charge les clients et chambres
};

#endif // RESERVATIONVIEW_H