#include "main-window.h"

#include <iostream>
#include <QApplication>

#include "object-manager.h"
#include "socket-routines.h"
#include "version.h"

int main(int argc, char *argv[])
{
    std::cout << "byte-messenger version=" << version::getVersionString() << std::endl;

    ObjectManager::createInstance();
#ifdef WIN_BUILD
    tcp::initialize(); // Winsock2 startup stuff
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ObjectManager::setMainWindow(&w);

    return a.exec();
}
