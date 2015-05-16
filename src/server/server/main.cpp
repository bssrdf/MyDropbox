#include <QCoreApplication>

using namespace std;

#include "server.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //ASSERT : argv[1] is the port.
    Server w;
    return 1;
}
