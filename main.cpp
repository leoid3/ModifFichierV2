#include <QApplication>
#include <fichier.h>

int main(int argc, char *argv[])
{

    QApplication appli(argc, argv);

    fichier fich;

    fich.show();

    return appli.exec();
}
