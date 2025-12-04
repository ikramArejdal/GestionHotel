#ifndef CLIENTVIEW_H
#define CLIENTVIEW_H

#include <QDialog>
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QMessageBox>

#include "clientController.h"

namespace Ui {
class ClientView;
}

class ClientView : public QWidget
{
    Q_OBJECT

public:
    explicit ClientView(QWidget *parent = nullptr);
    ~ClientView();
    int idEnEdition = -1;


private slots:
    void on_btnAjouterClient_clicked();
    //void on_btnSupprimerChambre_clicked();  // suppression via colonne Action

private:
    Ui::ClientView *ui;
    ClientController clientCtrl;

    void chargerListeClients();      // équivalent de Dashboard::chargerListeClient()
    void connecterBouton(QPushButton *btn, int idClient);
};

#endif // CLIENTVIEW_H
