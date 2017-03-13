#include <QApplication>
#include "mainwindow.h"
#include "accueil.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator qtTranslator;
           qtTranslator.load("qt_" + QLocale::system().name(),
                   QLibraryInfo::location(QLibraryInfo::TranslationsPath));
           a.installTranslator(&qtTranslator);
           QTranslator myappTranslator;
           QString nomFichier="interroBDD_" + QLocale::system().name()+".qm";
           qDebug()<<nomFichier;
           QString baseName;
/*#ifdef Q_OS_LINUX
        baseName="/usr/share/applications/interroBDD/translations/";
#endif
#ifdef Q_OS_MACOS
        baseName=QApplication::applicationDirPath()+QLatin1String("/../Resources/translations/"); // path defaults to app dir.
#endif
#ifdef Q_OS_DARWIN
        baseName=QApplication::applicationDirPath()+QLatin1String("/translations/"); // path defaults to app dir.
#endif
#ifdef Q_OS_WIN
        baseName=QApplication::applicationDirPath();
#endif         */
           baseName="/home/cdervieux/Documents/QT/interroBDD/";
           qDebug() << baseName;
           myappTranslator.load(baseName+nomFichier);
           a.installTranslator(&myappTranslator);

    Accueil test;
    if(test.exec()==QDialog::Accepted)
    {
        //qDebug() << "mainwindow";
        MainWindow w;
        w.show();
        return a.exec();
    }

}
