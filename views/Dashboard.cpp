#include "Dashboard.h"
#include "ui_Dashboard.h"
<<<<<<< HEAD
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "ReservationView.h"
// Note : On a retiré "EmployeView.h" car tout est géré ici maintenant
=======
#include "clientController.h"
>>>>>>> cc71cd9 (Gestion Clients)

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
    
    // --- INTEGRATION RESERVATION ---
    QVBoxLayout *resLayout = new QVBoxLayout(ui->tab_reservations);
    ReservationView *resView = new ReservationView(this);
    resLayout->addWidget(resView);
    resLayout->setContentsMargins(0,0,0,0); 

<<<<<<< HEAD
    // --- INITIALISATION ---
    chargerListeChambres();
    chargerListeEmployes();

    // Appliquer les droits (Cacher l'onglet employés si besoin)
    applyingRole();
    
    // On cache les boutons de sauvegarde au démarrage
    ui->btnSauvegarder->setVisible(false);
    ui->btnSauvegarderEmp->setVisible(false);
=======
    // 2. Charger les données au démarrage
    chargerListeChambres(); // Charger d'abord
    appliquerRole();        // Appliquer les restrictions ensuite

    // Configuration du tableau des clients (5 colonnes)
    // Configuration du tableau des clients (6 colonnes : + colonne Action)
   /* ui->tableClients->setColumnCount(6);
    QStringList titresClients;
    titresClients << "ID" << "Nom" << "Prénom" << "CIN" << "Téléphone" << "Action";
    ui->tableClients->setHorizontalHeaderLabels(titresClients);
    ui->tableClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableClients->setColumnHidden(0, true);*/

    clientView = new ClientView(this);
    ui->layoutClients->addWidget(clientView);

>>>>>>> cc71cd9 (Gestion Clients)
}

Dashboard::~Dashboard() { delete ui; }

void Dashboard::applyingRole()
{
    // Si l'utilisateur n'est PAS manager (ou admin)
    if (currentRole != "manager" && currentRole != "admin") {
        
        // 1. On supprime l'onglet Employés
        int index = ui->tabWidget->indexOf(ui->tab_employes);
        if (index != -1) {
            ui->tabWidget->removeTab(index);
        }
        
        // 2. On désactive le bouton du haut s'il existe encore
        if(ui->tableEmployes) ui->tableEmployes->setVisible(false);
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
// GESTION DES CHAMBRES
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

        btnEdit->setStyleSheet("background:#ffc107; border:none; padding:5px;");
        btnDelete->setStyleSheet("background:#dc3545; color:white; border:none; padding:5px;");

        pLayout->addWidget(btnEdit);
        pLayout->addWidget(btnDelete);
        ui->tableChambres->setCellWidget(row, 5, pWidget);

        // Supprimer via le bouton du tableau
        connect(btnDelete, &QPushButton::clicked, [=]() {
            if (QMessageBox::question(this, "Confirmer",
                "Supprimer la chambre " + c.numero + " ?") == QMessageBox::Yes)
            {
                chambreCtrl.supprimerChambre(QString::number(c.id));
                chargerListeChambres();
            }
        });

        // Modifier via le bouton du tableau
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

    if (chambreCtrl.ajouterChambre(num, type, prix.toDouble())) {
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

    // CORRECTION : Conversion du prix en Double avec .toDouble()
    if (chambreCtrl.modifierChambre(idChambreEnModif, num, type, prix.toDouble(), "Disponible")) {
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

<<<<<<< HEAD
void Dashboard::on_btnEmployes_clicked()
{
    // Ce bouton sert maintenant uniquement à changer d'onglet
    // Si l'onglet est caché, on ne fait rien (ou on affiche un message)
    if (currentRole == "manager" || currentRole == "admin") {
        ui->tabWidget->setCurrentWidget(ui->tab_employes);
    } else {
        QMessageBox::warning(this, "Accès refusé", "Vous n'avez pas les droits.");
    }
}
=======
/*void Dashboard::on_btnAjouterClient_clicked()
{
    QString nom       = ui->lineNom->text();
    QString prenom    = ui->linePrenom->text();
    QString cin       = ui->lineCin->text();
    QString telephone = ui->lineTelephone->text();

    // Vérification des champs obligatoires
    if (nom.isEmpty() || prenom.isEmpty() || cin.isEmpty() || telephone.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs.");
        return;
    }

    // Appel du controller (adapte le nom si nécessaire : clientCtrl / clientController)
    bool ok = clientCtrl.ajouterClient(nom, prenom, cin, telephone);

    if (ok) {
        QMessageBox::information(this, "Succès", "Client ajouté !");
        chargerListeClients();   // équivalent de chargerListeChambres()
        ui->lineNom->clear();
        ui->linePrenom->clear();
        ui->lineCin->clear();
        ui->lineTelephone->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ajouter le client.");
    }
}*/




>>>>>>> cc71cd9 (Gestion Clients)
