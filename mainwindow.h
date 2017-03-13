#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QListWidgetItem>
#include <QVector>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * @brief MainWindow
     * @param parent
     *constructeur de la mainwindow
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     *destructeur de la mainwindow
     */
    ~MainWindow();
    /**
     * @brief vectRequete
     *vecteur de requête qui permet stocker les requête historiser
     */
    QVector <QString> vectRequete;
    
private slots:
    /**
     * @brief selection de la données dans la combo box
     * @param nom de l'objet seelctionner
     *Permet de selectionner un objet dans la combo box et donc d'initialiser la base de données et les tables de celle-ci
     */
    void on_comboBoxListBDD_activated(const QString &arg1);
    /**
     * @brief selction d'une tables de la liste
     * @param item
     *Permet d'initialiser la liste des champs lorsqu'on selectionne une table
     */
    void on_listWidgetTable_itemClicked(QListWidgetItem *item);
    /**
     * @brief lorseque le texte change dans l'editeur de texte pour la requête
     *Permet de verifier si la requête est correcte à chaque fois que le texte change
     */
    void on_textEdit_textChanged();
    /**
     * @brief bouton erreur
     *Permet d'afficher l'erreur SQL de la requête quand la requête n'est pas correct
     */
    void on_pushButtonErreur_clicked();
    /**
     * @brief bouton nettoyer
     *Permet de nettoyer la zone de resultat,zone d'erreur et la zone de texte
     */
    void on_pushButtonClean_clicked();
    /**
     * @brief bouton historiser
     *Permet de mettre dans la liste historique et dans le vecteur de requête la requête inscrite dans la zone de texte
     */
    void on_pushButtonHistoriser_clicked();
    /**
     * @brief bouton enregistrer
     *Permet de sauvegarder ce qui a été historiser dans un document '.sql'
     */
    void on_pushButtonEnregistrer_clicked();
    /**
     * @brief bouton ouvrir
     *Permet d'ouvrir un fichier '.sql' pour charger des requête dans le vecteur et das la liste prévue à cette effet
     */
    void on_pushButton_clicked();
    /**
     * @brief menu fichier/quitter
     *Permet de quitter l'application
     */
    void on_action_Quitter_triggered();
    /**
     * @brief menu fichier/sauvegarde
     *Permet de sauvegarder dans un fichier '.sql' ce qui il ya dans la liste et dans le vecteur
     */
    void on_action_Save_triggered();
    /**
     * @brief menu fichier/ouvrir
     *Permet d'ouvrir un document '.sql' pour charger des requête dans le vecteur et la lsite
     */
    void on_action_Open_triggered();
    /**
     * @brief bouton sauvegarder le resultat
     *Permet d'exporter le tableaux du resultat au format '.csv'
     */
    void on_pushButton_2_clicked();
    /**
     * @brief l'utilisateur clicl sur un item de la liste de l'historique
     * @param item
     *Permet d'ajouter la requête selectionner dans la zone de texte
     */
    void on_listWidgetHistorique_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    void remplireListeTable();
};

#endif // MAINWINDOW_H
