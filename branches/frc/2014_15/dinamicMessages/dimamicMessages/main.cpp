#include <QCoreApplication>
#include "Message.h"
#include "MessageInterface.h"
#include "MessageInterfaceServer.h"
#include "MessageLoader.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
