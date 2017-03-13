#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <QDialog>

namespace Ui {
class Accueil;
}

class Accueil : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Accueil
     * @param parent
     *constructeur permettant de créer le dialog de connexion
     */
    explicit Accueil(QWidget *parent = 0);
    /**
     *destructeur permettant de supprimer le dialog de connexion
     */
    ~Accueil();
    
private slots:
    /**
     * @brief bouton connexion
     *bouton quitter qui permet de fermer l'application
     */
    void on_pushButton_clicked();
    /**
     * @brief bouton quitter
     *bouton de connexion qui permet d'acceder à la mainWindow
     *apres avoir entrer son identifiant et son mot de passe
     */
    void on_pushButtonConnexion_clicked();
    /**
     * @brief lorsque le texte du lineEdit change
     * @param ce qu'il y a dans la line edit
     *Permet de verifier lorsqe le texte du lineEdit serveur change de savoir si tout les lineEdit son remplie
     */
    void on_lineEditServeur_textChanged(const QString &arg1);
    /**
     * @brief lorsque le texte du lineEdit change
     * @param ce qu'il y a dans la line edit
     *Permet de verifier lorsqe le texte du lineEdit identifiant change de savoir si tout les lineEdit son remplie
     */
    void on_lineEditLogin_textChanged(const QString &arg1);
    /**
     * @brief lorsque le texte du lineEdit change
     * @param ce qu'il y a dans la line edit
     *Permet de verifier lorsqe le texte du lineEdit mot de passe change de savoir si tout les lineEdit son remplie
     */
    void on_lineEditMdp_textChanged(const QString &arg1);

private:
    Ui::Accueil *ui;
    /**
     * @brief activation du bouton connexion
     *Permet d'activer le bouton connexion lorsque tout les champs de la connexion sont remplie
     */
    void actBoutonConnexion();
};

#endif // ACCUEIL_H
