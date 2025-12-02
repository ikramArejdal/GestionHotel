#include "Dashboard.h"
#include "ui_Dashboard.h"

Dashboard::Dashboard(QString role, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard),
    currentRole(role)
{
    ui->setupUi(this);

    // 1. Configuration du tableau (5 colonnes)
    ui->tableChambres->setColumnCount(5);
    QStringList titres;
    titres << "ID" << "Numéro" << "Type" << "Prix" << "État";
    ui->tableChambres->setHorizontalHeaderLabels(titres);

    // Ajuster la largeur des colonnes automatiquement
    ui->tableChambres->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    
    // Cacher la colonne ID (c'est plus propre, l'utilisateur n'a pas besoin de la voir)
    ui->tableChambres->setColumnHidden(0, true);

    // 2. Charger les données au démarrage
    chargerListeChambres(); // Charger d'abord
    appliquerRole();        // Appliquer les restrictions ensuite
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::appliquerRole()
{
    // --- Contrôle des accès ---
    if (currentRole != "manager" && currentRole != "admin") { // Vérifiez bien le rôle exact dans votre DB
        ui->btnAjouterChambre->setEnabled(false);
        
        // ATTENTION : Si le bouton "btnSupprimerChambre" n'existe pas dans le .ui, cette ligne plantera
        if(ui->btnSupprimerChambre) {
             ui->btnSupprimerChambre->setEnabled(false);
        }

        QMessageBox::information(
            this,
            "Mode Réceptionniste",
            "Vous êtes connecté avec des droits limités.");
    }
}

void Dashboard::chargerListeChambres()
{
    // On vide le tableau
    ui->tableChambres->setRowCount(0);

    QList<Chambre> chambres = chambreCtrl.getAllChambres();

    int row = 0;
    for (const Chambre &c : chambres)
    {
        ui->tableChambres->insertRow(row);
        ui->tableChambres->setItem(row, 0, new QTableWidgetItem(QString::number(c.id)));
        ui->tableChambres->setItem(row, 1, new QTableWidgetItem(c.numero));
        ui->tableChambres->setItem(row, 2, new QTableWidgetItem(c.type));
        ui->tableChambres->setItem(row, 3, new QTableWidgetItem(QString::number(c.prix)));
        ui->tableChambres->setItem(row, 4, new QTableWidgetItem(c.etat));

        if (c.etat == "Occupée") {
            ui->tableChambres->item(row, 4)->setBackground(Qt::red);
            ui->tableChambres->item(row, 4)->setForeground(Qt::white);
        }
        row++;
    }
} // <--- Fin de la fonction chargerListeChambres

// Les slots doivent être à l'extérieur !

void Dashboard::on_btnAjouterChambre_clicked()
{
    QString num = ui->txtNum->text();
    QString type = ui->txtType->text();
    QString prix = ui->txtPrix->text();

    if(num.isEmpty() || prix.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
    }

    bool ok = chambreCtrl.ajouterChambre(num, type, prix);

    if (ok) {
        QMessageBox::information(this, "Succès", "Chambre ajoutée !");
        chargerListeChambres();
        ui->txtNum->clear();
        ui->txtType->clear();
        ui->txtPrix->clear();
    }
    else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter la chambre.");
    }
}

void Dashboard::on_btnSupprimerChambre_clicked()
{
    int row = ui->tableChambres->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Veuillez sélectionner une chambre.");
        return;
    }

    QString id = ui->tableChambres->item(row, 0)->text();

    if (chambreCtrl.supprimerChambre(id)) {
        QMessageBox::information(this, "Succès", "Chambre supprimée.");
        chargerListeChambres();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de supprimer la chambre.");
    }
}