#include "accueil.h"
#include "ui_accueil.h"
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

Accueil::Accueil(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Accueil)
{
    ui->setupUi(this);
}

Accueil::~Accueil()
{
    delete ui;
}

void Accueil::on_pushButton_clicked()
{
    close();
}

void Accueil::on_pushButtonConnexion_clicked()
{
    QString login=ui->lineEditLogin->text();
    QString motDePasse=ui->lineEditMdp->text();
    QString serveur=ui->lineEditServeur->text();
    QSqlDatabase maBase=QSqlDatabase::addDatabase("QMYSQL");
    maBase.setHostName(serveur);
    maBase.setUserName(login);
    maBase.setPassword(motDePasse);
    if (maBase.open())
    {
        accept();
    }
    else
        qDebug() << "echec de connexion";
}

void Accueil::actBoutonConnexion()
{
    ui->pushButtonConnexion->setEnabled(ui->lineEditLogin->text()!="" && ui->lineEditMdp->text()!="" && ui->lineEditServeur->text()!="");
}

void Accueil::on_lineEditServeur_textChanged(const QString &arg1)
{
    actBoutonConnexion();
}

void Accueil::on_lineEditLogin_textChanged(const QString &arg1)
{
    actBoutonConnexion();
}

void Accueil::on_lineEditMdp_textChanged(const QString &arg1)
{
    actBoutonConnexion();
}
