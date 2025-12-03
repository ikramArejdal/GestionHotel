#ifndef EMPLOYEVIEW_H
#define EMPLOYEVIEW_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include "connexionDB.h" // Assurez-vous d'inclure votre connexion si nécessaire

namespace Ui {
class EmployeView;
}

class EmployeView : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeView(QWidget *parent = nullptr);
    ~EmployeView();

private slots:
    void on_btnAjouter_clicked();
    void on_btnSupprimer_clicked();

private:
    Ui::EmployeView *ui;
    void chargerEmployes();
};

#endif // EMPLOYEVIEW_H
