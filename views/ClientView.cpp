#include "ClientView.h"
#include "Dashboard.h"
#include "ui_Dashboard.h"
#include <QMessageBox>
#include "ui_ClientView.h"

ClientView::ClientView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientView)
{
    ui->setupUi(this);
    
    // On s'assure que la DB est ouverte (par sécurité)
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()) qDebug() << "Erreur DB fermée dans EmployeView";

    chargerListeClients();
}

ClientView::~ClientView()
{
    delete ui;
}
void ClientView::chargerListeClients()
{
    // On vide le tableau
    ui->tableClients->setRowCount(0);

    ui->tableClients->setColumnCount(6);
    QStringList headers = {"ID", "Nom", "Prénom", "CIN", "Téléphone", "Actions"};
    ui->tableClients->setHorizontalHeaderLabels(headers);

    QList<Client> clients = clientCtrl.getAllClients();

    int row = 0;
    for (const Client &c : clients)
    {
        ui->tableClients->insertRow(row);
        ui->tableClients->setItem(row, 0, new QTableWidgetItem(QString::number(c.getId())));
        ui->tableClients->setItem(row, 1, new QTableWidgetItem(c.getNom()));
        ui->tableClients->setItem(row, 2, new QTableWidgetItem(c.getPrenom()));
        ui->tableClients->setItem(row, 3, new QTableWidgetItem(c.getCin()));
        ui->tableClients->setItem(row, 4, new QTableWidgetItem(c.getTelephone()));

        // === Bouton Modifier ===
        QPushButton *btnModifier = new QPushButton("✏");
        btnModifier->setStyleSheet(
            "background-color: #0275d8;"
            "color: white;"
            "padding: 2px 6px;"
            "font-size: 10px;"
            "border-radius: 3px;"
            );
        btnModifier->setMaximumWidth(90);
        btnModifier->setMinimumHeight(24);
        btnModifier->setProperty("idClient", c.getId());

        connect(btnModifier, &QPushButton::clicked, this, [=]() {
            int id = btnModifier->property("idClient").toInt();

            Client c = clientCtrl.getClientById(id);

            idEnEdition = id;  // 🎯 mémorisation interne

            ui->lineNom->setText(c.getNom());
            ui->linePrenom->setText(c.getPrenom());
            ui->lineCin->setText(c.getCin());
            ui->lineTelephone->setText(c.getTelephone());

            ui->btnAjouterClient->setText("Mettre à jour");
        });


        // === Bouton Supprimer ===
        QPushButton *btnSupprimer = new QPushButton("🗑");
        btnSupprimer->setStyleSheet(
            "background-color: #d9534f;"
            "color: white;"
            "padding: 2px 6px;"       // plus petit padding
            "font-size: 10px;"        // police plus petite
            "border-radius: 3px;"
            );

        // Taille fixe ou maximum
        btnSupprimer->setMaximumWidth(100);
        btnSupprimer->setMinimumHeight(24);
        btnSupprimer->setProperty("idClient", c.getId());

        connect(btnSupprimer, &QPushButton::clicked, this, [=]() {
            int id = btnSupprimer->property("idClient").toInt();

            if (QMessageBox::question(this, "Confirmation",
                "Voulez-vous vraiment supprimer ce client ?") == QMessageBox::Yes)
            {
                if (clientCtrl.supprimerClient(QString::number(id))) {
                    QMessageBox::information(this, "Succès", "Client supprimé.");
                    chargerListeClients();
                } else {
                    QMessageBox::critical(this, "Erreur", "Impossible de supprimer le client.");
                }
            }
        });

        // === Layout Actions (Modifier + Supprimer) ===
        QWidget *actionsWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(actionsWidget);
        layout->setContentsMargins(2, 2, 2, 2);
        layout->setSpacing(5);  // espace entre les boutons

        layout->addWidget(btnModifier);
        layout->addWidget(btnSupprimer);

        actionsWidget->setLayout(layout);

        // Ajouter dans la cellule
        ui->tableClients->setCellWidget(row, 5, actionsWidget);
        row++;
        };
 }
void ClientView::on_btnAjouterClient_clicked()
{
    QString nom = ui->lineNom->text();
    QString prenom = ui->linePrenom->text();
    QString cin = ui->lineCin->text();
    QString telephone = ui->lineTelephone->text();

    if (nom.isEmpty() || prenom.isEmpty() || cin.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires.");
        return;
    }

    if (idEnEdition == -1)
    {
        // === AJOUT ===
        bool ok = clientCtrl.ajouterClient(nom, prenom, cin, telephone);

        if (ok) {
            QMessageBox::information(this, "Succès", "Client ajouté !");
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le client.");
        }
    }
    else
    {
        // === MODIFICATION ===
        bool ok = clientCtrl.modifierClient(idEnEdition, nom, prenom, cin, telephone);

        if (ok) {
            QMessageBox::information(this, "Succès", "Client mis à jour !");
        } else {
            QMessageBox::critical(this, "Erreur", "Impossible de modifier le client.");
        }

        idEnEdition = -1;
        ui->btnAjouterClient->setText("+ Ajouter");
    }

    // Rafraîchir la liste après ajout/modif
    chargerListeClients();

    // Effacer le formulaire
    ui->lineNom->clear();
    ui->linePrenom->clear();
    ui->lineCin->clear();
    ui->lineTelephone->clear();

}

/*void ClientView::supprimerClientParBouton(QPushButton *btn)
{
    int id = btn->property("clientId").toInt();

    if (clientCtrl.supprimerClient(QString::number(id))) {
        QMessageBox::information(dash, "Succès", "Client supprimé.");
        chargerListeClients();
    }
    else {
        QMessageBox::critical(dash, "Erreur", "Impossible de supprimer le client.");
    }
}*/
/*void ClientView::on_btnSupprimerChambre_clicked()
{
    int row = ui->tableClients->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner un client.");
        return;
    }

    QString id = ui->tableClients->item(row, 0)->text();

    if (clientCtrl.supprimerClient(id)) {
        QMessageBox::information(this, "Succès", "Client supprimée.");
        chargerListeClients();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de supprimer le client.");
    }
}*/
