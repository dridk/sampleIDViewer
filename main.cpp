#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("SampleID viewer");
    a.setApplicationVersion("0.1beta");
    a.setOrganizationDomain("labsquare.org");
    a.setOrganizationName("labsquare");


    //==== Just for testing

    QSettings settings ;
    settings.beginGroup("server/pgm");
    settings.setValue("host","10.67.70.16");
    settings.setValue("username", "ionuser");
    settings.setValue("password", "ionuser");
    settings.endGroup();



    MainWindow w;
    w.show();

    return a.exec();
}
