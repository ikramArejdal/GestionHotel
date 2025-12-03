#include "ReservationView.h"
#include "ui_ReservationView.h"
#include <QMessageBox>
#include <QHBoxLayout>

ReservationView::ReservationView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReservationView)
{
    ui->setupUi(this);

    // Initialisation des Dates
    ui->dateResIn->setDate(QDate::currentDate());
    ui->dateResOut->setDate(QDate::currentDate().addDays(1));

    // Configuration Tableau
    ui->tableReservations->setColumnHidden(0, true); // Cacher ID
    ui->tableReservations->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Connexions pour le calcul automatique du prix
    connect(ui->dateResIn, &QDateEdit::dateChanged, this, &ReservationView::recalculerPrix);
    connect(ui->dateResOut, &QDateEdit::dateChanged, this, &ReservationView::recalculerPrix);
    connect(ui->comboResChambre, &QComboBox::currentIndexChanged, this, &ReservationView::recalculerPrix);

    // Chargement initial
    rafraichirDonnees();
}

ReservationView::~ReservationView()
{
    delete ui;
}

void ReservationView::rafraichirDonnees()
{
    remplirComboBoxes();
    chargerReservations();
    recalculerPrix();
}

void ReservationView::remplirComboBoxes()
{
    ui->comboResClient->clear();
    ui->comboResChambre->clear();

    QSqlQuery q;
    
    // 1. Remplir Clients
    if(q.exec("SELECT id, nom, prenom FROM clients")) {
        while(q.next()) {
            int id = q.value(0).toInt();
            QString nom = q.value(1).toString() + " " + q.value(2).toString();
            ui->comboResClient->addItem(nom, id); // On cache l'ID dans userData
        }
    }

    // 2. Remplir Chambres (Uniquement celles qui existent)
    // Amélioration possible : N'afficher que les chambres 'Disponibles' ou 'Nettoyage'
    if(q.exec("SELECT id, numero, prix FROM chambres")) {
        while(q.next()) {
            int id = q.value(0).toInt();
            QString numero = q.value(1).toString();
            double prix = q.value(2).toDouble();
            
            QString label = "Chambre " + numero + " (" + QString::number(prix) + " DH)";
            ui->comboResChambre->addItem(label, id);
        }
    }
}

void ReservationView::recalculerPrix()
{
    QDate in = ui->dateResIn->date();
    QDate out = ui->dateResOut->date();
    
    if (in >= out) {
        ui->txtTotal->setText("Erreur Date");
        return;
    }

    int nuits = in.daysTo(out);
    int chambreId = ui->comboResChambre->currentData().toInt();
    
    // Récupérer le prix de la chambre sélectionnée
    double prixUnitaire = 0.0;
    QSqlQuery q;
    q.prepare("SELECT prix FROM chambres WHERE id = :id");
    q.bindValue(":id", chambreId);
    if(q.exec() && q.next()) {
        prixUnitaire = q.value(0).toDouble();
    }

    double total = nuits * prixUnitaire;
    ui->txtTotal->setText(QString::number(total, 'f', 2) + " DH");
}

void ReservationView::on_btnValiderRes_clicked()
{
    int clientId = ui->comboResClient->currentData().toInt();
    int chambreId = ui->comboResChambre->currentData().toInt();
    QDate in = ui->dateResIn->date();
    QDate out = ui->dateResOut->date();
    
    // Extraction du prix (on enlève " DH")
    double total = ui->txtTotal->text().split(" ")[0].toDouble();

    if (in >= out) {
        QMessageBox::warning(this, "Erreur", "La date de départ doit être après la date d'arrivée.");
        return;
    }

    if (resCtrl.ajouterReservation(clientId, chambreId, in, out, total)) {
        QMessageBox::information(this, "Succès", "Réservation validée !");
        chargerReservations();
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible de réserver.\nCette chambre est déjà occupée à ces dates.");
    }
}

void ReservationView::chargerReservations()
{
    ui->tableReservations->setRowCount(0);
    QList<Reservation> liste = resCtrl.getAllReservations();

    int row = 0;
    for (const Reservation &r : liste) {
        ui->tableReservations->insertRow(row);
        ui->tableReservations->setItem(row, 0, new QTableWidgetItem(QString::number(r.id)));
        ui->tableReservations->setItem(row, 1, new QTableWidgetItem(r.nomClient));
        ui->tableReservations->setItem(row, 2, new QTableWidgetItem(r.numeroChambre));
        ui->tableReservations->setItem(row, 3, new QTableWidgetItem(r.dateEntree.toString("dd/MM/yyyy")));
        ui->tableReservations->setItem(row, 4, new QTableWidgetItem(r.dateSortie.toString("dd/MM/yyyy")));
        ui->tableReservations->setItem(row, 5, new QTableWidgetItem(QString::number(r.montantTotal)));

        // Bouton Annuler
        QWidget *pWidget = new QWidget();
        QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
        pLayout->setContentsMargins(0, 0, 0, 0);
        QPushButton *btnDelete = new QPushButton("Annuler");
        btnDelete->setStyleSheet("background:#dc3545; color:white; font-weight:bold; border:none; padding:5px; border-radius:3px;");
        pLayout->addWidget(btnDelete);
        ui->tableReservations->setCellWidget(row, 6, pWidget);

        connect(btnDelete, &QPushButton::clicked, [=]() {
           if(QMessageBox::question(this, "Confirmation", "Annuler cette réservation ?") == QMessageBox::Yes) {
               if(resCtrl.supprimerReservation(r.id)){
                   chargerReservations();
               }
           }
        });

        row++;
    }
}