#ifndef FICHIER_H
#define FICHIER_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QFormLayout>
#include <QVector>
#include <QInputDialog>
#include <QTextEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QRegularExpression>
#include <QDebug>

class fichier : public QWidget
{
    Q_OBJECT

private :

        QLabel *indi, *comp, *remp, *trou;

        QPushButton *boutoncompter;
        QPushButton *boutonremplacer;
        QPushButton *chercher;
        QPushButton *quitter;
        QRadioButton *txt;
        QRadioButton *ini;
        QRadioButton *xml;

        QLineEdit *path, *compt, *trouver, *rempla;

        QGroupBox *extension;
        QGroupBox *chemin;
        QGroupBox *compter;
        QGroupBox *remplacer;

        QGridLayout *LayPrincipal;
        QHBoxLayout *LayoutChemin;
        QHBoxLayout *Layoutextension;
        QFormLayout *FormCompter, *FormRemplacer;

        QString cheminfichier, extent = "(*.txt)";


public slots:
        void choixtxt();
        void choixini();
        void choixxml();
        void choixfichier();
        void comptage();
        void remplassage();


public:
    fichier();
    void faireLayout();

};

#endif // FICHIER_H
