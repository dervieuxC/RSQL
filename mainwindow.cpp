#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QSqlError>
#include <QSqlResult>
#include <QPalette>
#include <QStyle>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QFile>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "test";
    ui->setupUi(this);
    qDebug() << "test2";
    QSqlQuery iniBDD("show databases;");
    while(iniBDD.next())
        {
            //recuperation des données d'une certaine ligne de la table
            QString nomBDD=iniBDD.value(0).toString();
            ui->comboBoxListBDD->addItem(nomBDD);
        }
    ui->labelIcon->setPixmap(QPixmap(":image/logo2.png"));
}//fin du constructeur de la mainWindow

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBoxListBDD_activated(const QString &arg1)
{
    QString nomBDD=arg1;
    QSqlQuery newQuery;
    //écriture de la requete
    QString texteRequete="use ";
    texteRequete+=nomBDD;
    texteRequete+=";";
    qDebug()<<texteRequete;
    //execution de la requete
    newQuery.exec(texteRequete);
    remplireListeTable();
    ui->textEdit->setEnabled(true);
    ui->pushButton->setEnabled(true);//bouton open
    ui->action_Open->setEnabled(true);
}

void MainWindow::remplireListeTable()
{
    ui->listWidgetTable->clear();
    QSqlQuery iniTable("show tables;");
    while(iniTable.next())
        {
            qDebug() << "Requete";
            //recuperation des données d'une certaine ligne de la table
            QString nomTable=iniTable.value(0).toString();
            ui->listWidgetTable->addItem(nomTable);
        }
}



void MainWindow::on_listWidgetTable_itemClicked(QListWidgetItem *item)
{
        ui->listWidgetChamps->clear();
        QSqlQuery iniChamps("show fields from " +item->text()+";");
        while(iniChamps.next())
            {
                qDebug() << "Requete";
                //recuperation des données d'une certaine ligne de la table
                QString nomChamps=iniChamps.value(0).toString();
                ui->listWidgetChamps->addItem(nomChamps);
            }
}

void MainWindow::on_textEdit_textChanged()
{
    QString texte=ui->textEdit->toPlainText();
    qDebug() << texte;
    QSqlQuery newquery(texte);
    qDebug() << newquery.isActive();
    if(newquery.isActive())
    {
        ui->pushButtonHistoriser->setEnabled(true);
        QSqlRecord nbColonnes = newquery.record();
        int nbC=nbColonnes.count();
        qDebug() << nbC;
        int nbL=newquery.size();
        qDebug() << nbL;
        ui->tableWidgetResultat->setColumnCount(nbC);
        ui->tableWidgetResultat->setRowCount(nbL);
        QStringList listeEntete;
        for (int i=0;i<nbC;i++)
        {
          QString nomColonnes=nbColonnes.fieldName(i);
          listeEntete.push_back(nomColonnes);
        }
        ui->tableWidgetResultat->setHorizontalHeaderLabels(listeEntete);
        ui->pushButtonErreur->setStyleSheet("background-color: green");
        int nbLigne=0;
        while(newquery.next())
        {
                int nb=0;
                while (nb!=nbC)
                {
                    QString resultat=newquery.value(nb).toString();
                    QTableWidgetItem * resultatConvertie= new QTableWidgetItem(resultat) ;
                    ui->tableWidgetResultat->setItem(nbLigne,nb,resultatConvertie);
                    nb+=1;
                }
                nbLigne+=1;
        }// fin while il y a une ligne suivante dans le resultat
    }//fin si la requête est correct
    else
    {
        ui->pushButtonHistoriser->setDisabled(true);
        ui->pushButtonErreur->setStyleSheet("background-color: red");
        QString error=(newquery.lastError()).text();
        qDebug() << error;

    }//fin du sinon
    ui->pushButtonErreur->setDisabled(newquery.isActive());
}

void MainWindow::on_pushButtonErreur_clicked()
{
    QString texte=ui->textEdit->toPlainText();
    QSqlQuery newquery(texte);
    QString error=(newquery.lastError()).text();
    ui->textBrowserErreur->setText(error);
    ui->textBrowserErreur->setStyleSheet("color:red");
}

void MainWindow::on_pushButtonClean_clicked()
{
    ui->textEdit->clear();
    ui->tableWidgetResultat->setColumnCount(0);
    ui->tableWidgetResultat->setRowCount(0);
}

void MainWindow::on_pushButtonHistoriser_clicked()
{
    ui->pushButtonHistoriser->setDisabled(true);
    QString texte=ui->textEdit->toPlainText();
    if (!(texte.endsWith(";")))
    {
        texte+=";";
    }
    ui->listWidgetHistorique->addItem(texte);
    vectRequete.push_back(texte);
    ui->pushButtonEnregistrer->setEnabled(true);
    ui->action_Save->setEnabled(true);
}

void MainWindow::on_pushButtonEnregistrer_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
       tr("Open Image"), "/home/", "*.sql");
    QFile file(fileName+".sql");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
            QTextStream out(&file);
            int nbOccurence=vectRequete.size();
            for(int i=0;i<nbOccurence;i++)
            {
                out << vectRequete[i] << "\n";
            }
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open Image"), "/home/", "*.sql");
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QTextStream in(&file);
            QString line="";
            while (!in.atEnd()) {
                line = line+in.readLine();
                if(line.endsWith(";"))
                {
                    ui->listWidgetHistorique->addItem(line);
                    vectRequete.push_back(line);
                    line="";
                }
            }
     ui->pushButtonEnregistrer->setEnabled(!ui->listWidgetHistorique->count()==0);
     ui->action_Save->setEnabled(!ui->listWidgetHistorique->count()==0);
}

void MainWindow::on_action_Quitter_triggered()
{
    close();
}

void MainWindow::on_action_Save_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
       tr("Open Image"), "/home/", "*.sql");
    QFile file(fileName+".sql");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
            QTextStream out(&file);
            int nbOccurence=vectRequete.size();
            for(int i=0;i<nbOccurence;i++)
            {
                out << vectRequete[i] << "\n";
            }
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open Image"), "/home/", "*.sql");
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                return;
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                ui->listWidgetHistorique->addItem(line);
                vectRequete.push_back(line);
            }
     ui->pushButtonEnregistrer->setEnabled(!ui->listWidgetHistorique->count()==0);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
       tr("Save file"), "/home/", "*.csv");
    QFile file(fileName+".csv");
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
            QTextStream out(&file);
            int nbLigne=ui->tableWidgetResultat->rowCount();
            int nbColonne=ui->tableWidgetResultat->columnCount();
            qDebug() << nbLigne;
            qDebug() << nbColonne;
            for(int i=0;i<nbLigne;i++)
            {
                //qDebug() << "lol";
                for(int o=0;o<nbColonne;o++)
                {
                    //qDebug() << "lol2";
                    QString result=ui->tableWidgetResultat->item(i,o)->text();
                    qDebug() << result;
                    if (o==nbColonne-1)
                    {
                        out << result;
                    }
                    else
                    {
                        out << result << ";";
                    }

                }
                           out << " \n";
            }
}


void MainWindow::on_listWidgetHistorique_itemClicked(QListWidgetItem *item)
{
    ui->textEdit->setText(item->text());
    ui->pushButtonErreur->setEnabled(true);
}
