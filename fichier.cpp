#include "fichier.h"

fichier::fichier()
{
    indi= new QLabel("Rentrer le chemin du fichier : ");
    comp = new QLabel("Rentrer le mot à compter : ");
    trou = new QLabel("Rentrer le mot à trouver : ");
    remp = new QLabel("Rentrer le mot qui va remplacer celui à trouver");

    path = new QLineEdit;
    path->setReadOnly(true);

    chercher = new QPushButton("...");
    boutoncompter = new QPushButton("Compter");
    boutoncompter->setToolTip("Permet de compter le nombre de fois qu'un mot apparait");
    boutonremplacer = new QPushButton("Remplacer");
    boutonremplacer->setToolTip("Permet de remplacer un mot avec un autre");
    quitter = new QPushButton("Quitter");

    txt = new QRadioButton(".txt", this);
    txt->setChecked(true);
    ini = new QRadioButton(".ini", this);
    xml = new QRadioButton(".xml", this);

    compt = new QLineEdit;
    trouver = new QLineEdit;
    rempla = new QLineEdit;

    faireLayout();

    connect(txt, SIGNAL(clicked()), this, SLOT(choixtxt()));
    connect(ini, SIGNAL(clicked()), this, SLOT(choixini()));
    connect(xml, SIGNAL(clicked()), this, SLOT(choixxml()));
    connect(chercher, SIGNAL(clicked()), this, SLOT(choixfichier()));
    connect(boutoncompter, SIGNAL(clicked()), this, SLOT(comptage()));
    connect(boutonremplacer, SIGNAL(clicked()), this, SLOT(remplassage()));
    connect(quitter, SIGNAL(clicked()), qApp, SLOT(quit()));


}

void fichier::faireLayout()
{

    LayoutChemin = new QHBoxLayout;
    LayoutChemin->addWidget(indi);
    LayoutChemin->addWidget(path);
    LayoutChemin->addWidget(chercher);

    Layoutextension = new QHBoxLayout;
    Layoutextension->addWidget(txt);
    Layoutextension->addWidget(ini);
    Layoutextension->addWidget(xml);



    FormCompter = new QFormLayout;
    FormCompter->addRow(comp, compt);

    FormRemplacer = new QFormLayout;
    FormRemplacer->addRow(trou, trouver);
    FormRemplacer->addRow(remp, rempla);

    compter = new QGroupBox("Compter", this);
    compter->setLayout(FormCompter);

    remplacer = new QGroupBox("Remplacer", this);
    remplacer->setLayout(FormRemplacer);

    extension = new QGroupBox("Extension du fichier", this);
    extension->setLayout(Layoutextension);

    chemin = new QGroupBox("Chemin du fichier", this);
    chemin->setLayout(LayoutChemin);


    LayPrincipal = new QGridLayout;
    LayPrincipal->addWidget(extension, 0, 0, 1, 2);
    LayPrincipal->addWidget(chemin, 1, 0, 1, 2);
    LayPrincipal->addWidget(compter, 2, 0);
    LayPrincipal->addWidget(remplacer, 2, 1);
    LayPrincipal->addWidget(boutoncompter, 3,0);
    LayPrincipal->addWidget(boutonremplacer, 3, 1);
    LayPrincipal->addWidget(quitter, 4,0, 1, 2);

    setLayout(LayPrincipal);
}

void fichier::choixtxt()
{
    extent = "(*.txt)";
    path->setText("");
}

void fichier::choixini()
{
    extent = "(*.ini)";
    path->setText("");
}

void fichier::choixxml()
{
    extent = "(*.xml)";
    path->setText("");
}

void fichier::choixfichier()
{
    path->setText(QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Texte " + extent));
    cheminfichier=path->text();

}

void fichier::comptage()
{
    QVector<QString> copie;
    int c=0;
    int l=-1;

    if(path->text().isEmpty() || compt->text().isEmpty() || path->text() == "") // Si le chemin ou le mot a chercher n'est pas rempli, ne rien faire
    {
        if(path->text().isEmpty() || path->text() == "") QMessageBox::critical(this, "Erreur", "Veuillez spécifier un chemin !!!");
        if(compt->text().isEmpty()) QMessageBox::critical(this, "Erreur", "Veuillez spécifier un mot à chercher !!!");
        return;
    };

    QRegularExpression reg(compt->text(), QRegularExpression::CaseInsensitiveOption);

    QFile fich(path->text());

    if(!fich.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur", "Le fichier n'a pu être ouvert !!!");
        return;
    }else
    {
        QTextStream in(&fich);
        while (!in.atEnd()) copie.push_back(in.readLine()); // Copie les lignes du fichier dans un tableau
    };
    fich.close(); // Ferme le fichier

    for(unsigned i=0; i<copie.size(); i++)
    {
        while(-1 != (l=copie[i].indexOf(reg, l+1))) // Permet de trouver le mot chercher sur la ligne sans pour autant chercher plus loin que la fin de la ligne
        {
            c++;
            l+=compt->text().size(); // Permet de mettre a jour le "curseur de position" pour ne pas depasser la fin de la ligne
        };

    };
    QMessageBox::information(this, "Compter", QString("Il y a %1 fois le mot \"").arg(c) + compt->text() +"\"");

}

void fichier::remplassage()
{
    QVector<QString> copie;
    int c=0;
    int l=-1;

    if(path->text().isEmpty() || trouver->text().isEmpty() || rempla->text().isEmpty() || path->text() == "") // Si le chemin ou le mot a chercher n'est pas rempli, ne rien faire
    {
        if(path->text().isEmpty() || path->text() == "") QMessageBox::critical(this, "Erreur", "Veuillez spécifier un chemin !!!");
        if(trouver->text().isEmpty()) QMessageBox::critical(this, "Erreur", "Veuillez spécifier un mot à trouver !!!");
        if(rempla->text().isEmpty()) QMessageBox::critical(this, "Erreur", "Veuillez spécifier un mot à remplacer !!!");
        return;
    };

    QRegularExpression reg(trouver->text(), QRegularExpression::CaseInsensitiveOption);

    QFile fich(path->text());

    if(!fich.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur", "Le fichier n'a pu être ouvert !!!");
        return;
    }else
    {
        QTextStream in(&fich);
        while (!in.atEnd()) copie.push_back(in.readLine()); // Copie les lignes du fichier dans un tableau
    };
    fich.close(); // Ferme le fichier

    for(unsigned i=0; i<copie.size(); i++)
    {
        while(-1 != (l=copie[i].indexOf(reg, l+1))) // Permet de trouver le mot chercher sur la ligne sans pour autant chercher plus loin que la fin de la ligne
        {
            copie[i].replace(l, trouver->text().size(), rempla->text()); // Remplace le mot chercher par celui voulu
            c++;
            l+=compt->text().size(); // Permet de mettre a jour le "curseur de position" pour ne pas depasser la fin de la ligne
        };
    };

    if(!fich.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Erreur", "Le fichier n'a pu être ouvert !!!");
        return;
    }else
    {
        QTextStream out(&fich);
        for(unsigned i=0; i<copie.size(); i++) out << copie[i] << "\n";
    };
    fich.close();
    QMessageBox::information(this, "Remplacer", ("Le mot \""+trouver->text()+"\" a ete remplacer %1 fois par \""+rempla->text()+"\"").arg(c));
}
