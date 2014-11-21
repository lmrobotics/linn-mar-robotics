#include <QCoreApplication>
#include "Message.h"
#include "MessageInterface.h"
#include "MessageInterfaceServer.h"
#include "MessageLoader.h"

using namespace message;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    string val("<m>");
    size_t e = val.rfind("<");
    size_t t = val.rfind(">");
    char buffer[23];
    std::size_t length = val.copy(buffer, t - 1, e + 1);
    buffer[length]='\0';
    string val2(buffer);

    printf(val2.c_str());
    return a.exec();
}
