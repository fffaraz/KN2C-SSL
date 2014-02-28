
// http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
// http://www.possibility.com/Cpp/CppCodingStandard.html
// http://geosoft.no/development/cppstyle.html


#include <QApplication>
#include <QDebug>
#include <iostream>

#include <signal.h>
#include <stdlib.h>
#include <assert.h>

#include "ui/mainwindow.h"

using namespace std;

void SignalHandler(int)
{
    // save current state here
    // and then ...
    qDebug() << "Segmentation Fault !!!";
    exit(1);
}

int main(int argc, char *argv[])
{
    //signal(SIGSEGV, SignalHandler);
    //signal(SIGALRM, SignalHandler);

    QCoreApplication::setOrganizationName("KN2C");
    QCoreApplication::setOrganizationDomain("www.kn2c.ir");
    QCoreApplication::setApplicationName("KN2C-SSL");

    QApplication a(argc, argv);
    cout << endl;
    cout << "KN2C Small Size League Robocup Team" << endl;
    cout << "K.N.Toosi University of Technology" << endl;
    cout << "Computer & Electrical Eng. Faculty" << endl;
    cout << "Version 6.0.0" << endl;
    cout << endl;

    MainWindow w;
    w.show();

    return a.exec();
}
