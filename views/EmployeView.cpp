#include "EmployeView.h"
#include "ui_EmployeView.h"

EmployeView::EmployeView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmployeView)
{
    ui->setupUi(this);
    
    // On s'assure que la DB est ouverte (par sécurité)
    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()) qDebug() << "Erreur DB fermée dans EmployeView";

    chargerEmployes();
}

EmployeView::~EmployeView()
{
    delete ui;
}

void EmployeView::chargerEmployes()
{
    ui->tableEmployes->setRowCount(0);

    // CORRECTION : Table 'employes' (pluriel) et toutes les colonnes
    QSqlQuery q("SELECT id, nom, prenom, poste, telephone, salaire FROM employes");

    int row = 0;
    while (q.next()) {
        ui->tableEmployes->insertRow(row);

        ui->tableEmployes->setItem(row, 0, new QTableWidgetItem(q.value(0).toString())); // ID
        ui->tableEmployes->setItem(row, 1, new QTableWidgetItem(q.value(1).toString())); // Nom
        ui->tableEmployes->setItem(row, 2, new QTableWidgetItem(q.value(2).toString())); // Prenom
        ui->tableEmployes->setItem(row, 3, new QTableWidgetItem(q.value(3).toString())); // Poste
        ui->tableEmployes->setItem(row, 4, new QTableWidgetItem(q.value(4).toString())); // Tel
        ui->tableEmployes->setItem(row, 5, new QTableWidgetItem(q.value(5).toString())); // Salaire

        row++;
    }
}

void EmployeView::on_btnAjouter_clicked()
{
    // CORRECTION : Utilisation des noms du .ui (inputNom, etc.)
    QString nom = ui->inputNom->text();
    QString prenom = ui->inputPrenom->text();
    QString poste = ui->inputPoste->text();
    QString tel = ui->inputTel->text();
    QString salaire = ui->inputSalaire->text();

    if(nom.isEmpty() || poste.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Le nom et le poste sont obligatoires.");
        return;
    }

    QSqlQuery q;
    q.prepare("INSERT INTO employes (nom, prenom, poste, telephone, salaire) VALUES (:n, :pr, :po, :t, :s)");
    q.bindValue(":n", nom);
    q.bindValue(":pr", prenom);
    q.bindValue(":po", poste);
    q.bindValue(":t", tel);
    q.bindValue(":s", salaire);

    if (q.exec()) {
        QMessageBox::information(this, "OK", "Employé ajouté.");
        
        // Vider les champs
        ui->inputNom->clear();
        ui->inputPrenom->clear();
        ui->inputPoste->clear();
        ui->inputTel->clear();
        ui->inputSalaire->clear();
        
        chargerEmployes();
    } else {
        QMessageBox::critical(this, "Erreur", q.lastError().text());
    }
}

void EmployeView::on_btnSupprimer_clicked()
{
    int row = ui->tableEmployes->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner un employé.");
        return;
    }

    QString id = ui->tableEmployes->item(row, 0)->text();

    QSqlQuery q;
    q.prepare("DELETE FROM employes WHERE id = :id");
    q.bindValue(":id", id);

    if (q.exec()) {
        QMessageBox::information(this, "OK", "Employé supprimé.");
        chargerEmployes();
    } else {
        QMessageBox::critical(this, "Erreur", q.lastError().text());
    }
}