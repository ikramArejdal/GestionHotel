#include "Dashboard.h"
#include "ui_Dashboard.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "EmployeView.h"

Dashboard::Dashboard(QString role, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard),
    currentRole(role)
{
    ui->setupUi(this);

    // --- CONFIG TABLEAU CHAMBRES ---
    ui->tableChambres->setColumnCount(6);
    ui->tableChambres->setColumnHidden(0, true); // Cacher ID
    ui->tableChambres->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // --- CONFIG TABLEAU EMPLOYES ---
    ui->tableEmployes->setColumnCount(7); // ID, Nom, Pre, Poste, Tel, Sal, Action
    ui->tableEmployes->setColumnHidden(0, true);
    ui->tableEmployes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Charger les données
    chargerListeChambres();
    chargerListeEmployes();

    // Appliquer les droits (Cacher l'onglet si besoin)
    applyingRole();
}

Dashboard::~Dashboard() { delete ui; }

void Dashboard::applyingRole()
{
    // Si l'utilisateur n'est PAS manager (ou admin)
    if (currentRole != "manager" && currentRole != "admin") {
        
        // 1. On cherche l'index de l'onglet Employés
        int index = ui->tabWidget->indexOf(ui->tab_employes);
        
        // 2. On le supprime (le cache)
        if (index != -1) {
            ui->tabWidget->removeTab(index);
        }
    }
}

// ==========================================
// GESTION DES EMPLOYES
// ==========================================

void Dashboard::chargerListeEmployes()
{
    ui->tableEmployes->setRowCount(0);
    QList<Employe> liste = employeCtrl.getAllEmployes();

    int row = 0;
    for(const Employe &e : liste) {
        ui->tableEmployes->insertRow(row);
        ui->tableEmployes->setItem(row, 0, new QTableWidgetItem(QString::number(e.id)));
        ui->tableEmployes->setItem(row, 1, new QTableWidgetItem(e.nom));
        ui->tableEmployes->setItem(row, 2, new QTableWidgetItem(e.prenom));
        ui->tableEmployes->setItem(row, 3, new QTableWidgetItem(e.poste));
        ui->tableEmployes->setItem(row, 4, new QTableWidgetItem(e.telephone));
        ui->tableEmployes->setItem(row, 5, new QTableWidgetItem(QString::number(e.salaire)));

        // --- BOUTONS ACTIONS ---
        QWidget *pWidget = new QWidget();
        QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
        pLayout->setContentsMargins(0, 0, 0, 0);
        
        QPushButton *btnEdit = new QPushButton("Modif");
        QPushButton *btnDelete = new QPushButton("Suppr");
        btnEdit->setStyleSheet("background:#ffc107; border:none; padding:5px;");
        btnDelete->setStyleSheet("background:#dc3545; color:white; border:none; padding:5px;");
        
        pLayout->addWidget(btnEdit);
        pLayout->addWidget(btnDelete);
        ui->tableEmployes->setCellWidget(row, 6, pWidget);

        // Connexion Modifier
        connect(btnEdit, &QPushButton::clicked, [=]() {
            ui->txtEmpNom->setText(e.nom);
            ui->txtEmpPrenom->setText(e.prenom);
            ui->txtEmpPoste->setText(e.poste);
            ui->txtEmpTel->setText(e.telephone);
            ui->txtEmpSalaire->setText(QString::number(e.salaire));
            
            idEmployeEnModif = e.id;
            ui->btnAjouterEmp->setVisible(false);
            ui->btnSauvegarderEmp->setVisible(true);
            ui->groupBoxEmp->setTitle("Modifier " + e.nom);
        });

        // Connexion Supprimer
        connect(btnDelete, &QPushButton::clicked, [=]() {
           if(QMessageBox::question(this,"Supprimer", "Supprimer " + e.nom + "?") == QMessageBox::Yes) {
               employeCtrl.supprimerEmploye(e.id);
               chargerListeEmployes();
           }
        });

        row++;
    }
}

void Dashboard::on_btnAjouterEmp_clicked()
{
    QString n = ui->txtEmpNom->text();
    QString p = ui->txtEmpPrenom->text();
    QString po = ui->txtEmpPoste->text();
    QString t = ui->txtEmpTel->text();
    double s = ui->txtEmpSalaire->text().toDouble();

    if(employeCtrl.ajouterEmploye(n, p, po, t, s)) {
        QMessageBox::information(this, "Succès", "Employé ajouté");
        chargerListeEmployes();
        // Reset champs
        ui->txtEmpNom->clear(); ui->txtEmpPrenom->clear(); ui->txtEmpPoste->clear();
        ui->txtEmpTel->clear(); ui->txtEmpSalaire->clear();
    }
}

void Dashboard::on_btnSauvegarderEmp_clicked()
{
    QString n = ui->txtEmpNom->text();
    QString p = ui->txtEmpPrenom->text();
    QString po = ui->txtEmpPoste->text();
    QString t = ui->txtEmpTel->text();
    double s = ui->txtEmpSalaire->text().toDouble();

    if(employeCtrl.modifierEmploye(idEmployeEnModif, n, p, po, t, s)) {
        QMessageBox::information(this, "Succès", "Employé modifié");
        chargerListeEmployes();
        
        // Reset UI
        ui->txtEmpNom->clear(); ui->txtEmpPrenom->clear(); ui->txtEmpPoste->clear();
        ui->txtEmpTel->clear(); ui->txtEmpSalaire->clear();
        ui->btnAjouterEmp->setVisible(true);
        ui->btnSauvegarderEmp->setVisible(false);
        ui->groupBoxEmp->setTitle("Ajouter ou Modifier un employé");
        idEmployeEnModif = -1;
    }
}

// ==========================================
// GESTION DES CHAMBRES (Code Existant)
// ==========================================

void Dashboard::chargerListeChambres()
{
    ui->tableChambres->setRowCount(0);
    QList<Chambre> chambres = chambreCtrl.getAllChambres();

    int row = 0;
    for (const Chambre &c : chambres) {
        ui->tableChambres->insertRow(row);

        ui->tableChambres->setItem(row, 0, new QTableWidgetItem(QString::number(c.id)));
        ui->tableChambres->setItem(row, 1, new QTableWidgetItem(c.numero));
        ui->tableChambres->setItem(row, 2, new QTableWidgetItem(c.type));
        ui->tableChambres->setItem(row, 3, new QTableWidgetItem(QString::number(c.prix)));
        ui->tableChambres->setItem(row, 4, new QTableWidgetItem(c.etat));

        // Actions
        QWidget *pWidget = new QWidget();
        QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
        pLayout->setContentsMargins(0, 0, 0, 0);

        QPushButton *btnEdit = new QPushButton("Modif");
        QPushButton *btnDelete = new QPushButton("Suppr");

        btnEdit->setStyleSheet("background:#ffc107;");
        btnDelete->setStyleSheet("background:#dc3545;color:white;");

        pLayout->addWidget(btnEdit);
        pLayout->addWidget(btnDelete);
        pWidget->setLayout(pLayout);

        ui->tableChambres->setCellWidget(row, 5, pWidget);

        connect(btnDelete, &QPushButton::clicked, [=]() {
            if (QMessageBox::question(this, "Confirmer",
                "Supprimer la chambre " + c.numero + " ?") == QMessageBox::Yes)
            {
                chambreCtrl.supprimerChambre(QString::number(c.id));
                chargerListeChambres();
            }
        });

        connect(btnEdit, &QPushButton::clicked, [=]() {
            ui->txtNum->setText(c.numero);
            ui->txtType->setText(c.type);
            ui->txtPrix->setText(QString::number(c.prix));

            idChambreEnModif = c.id;

            ui->btnAjouterChambre->setVisible(false);
            ui->btnSauvegarder->setVisible(true);
            ui->groupBox->setTitle("Modifier la chambre " + c.numero);
        });

        row++;
    }
}

void Dashboard::on_btnAjouterChambre_clicked()
{
    QString num = ui->txtNum->text();
    QString type = ui->txtType->text();
    QString prix = ui->txtPrix->text();

    if (chambreCtrl.ajouterChambre(num, type, prix)) {
        QMessageBox::information(this, "Succès", "Chambre ajoutée !");
        ui->txtNum->clear();
        ui->txtType->clear();
        ui->txtPrix->clear();
        chargerListeChambres();
    } else {
        QMessageBox::critical(this, "Erreur", "Ajout échoué !");
    }
}

void Dashboard::on_btnSauvegarder_clicked()
{
    QString num = ui->txtNum->text();
    QString type = ui->txtType->text();
    QString prix = ui->txtPrix->text();

    if (chambreCtrl.modifierChambre(idChambreEnModif, num, type, prix, "Disponible")) {
        QMessageBox::information(this, "OK", "Chambre modifiée !");
        ui->txtNum->clear();
        ui->txtType->clear();
        ui->txtPrix->clear();

        ui->btnAjouterChambre->setVisible(true);
        ui->btnSauvegarder->setVisible(false);
        ui->groupBox->setTitle("Ajouter une chambre");

        idChambreEnModif = -1;
        chargerListeChambres();
    }
}

void Dashboard::on_btnSupprimerChambre_clicked()
{
    int row = ui->tableChambres->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Erreur", "Sélectionnez une chambre.");
        return;
    }

    QString id = ui->tableChambres->item(row, 0)->text();
    chambreCtrl.supprimerChambre(id);
    chargerListeChambres();
}

void Dashboard::on_tableChambres_cellClicked(int, int)
{
}

void Dashboard::on_btnEmployes_clicked()
{
    if (currentRole != "manager" && currentRole != "admin") {
        QMessageBox::warning(this, "Accès refusé", "Vous n'avez pas les droits.");
        return;
    }

    EmployeView *ev = new EmployeView();
    ev->show();
}
