#include <QCoreApplication>
#include <iostream>

#include "controller.h"

using namespace std;

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    Controller controller;

    return app.exec();
}
