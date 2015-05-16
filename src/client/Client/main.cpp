int PORT;
#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    string tempIP,tempport;
    string my(argv[1]);

    int i=0;

    while(my[i]!=':'){
        tempIP.push_back(my[i]);
        i++;
    }

    i++;

    while(i<my.size()){
        tempport.push_back(my[i]);
        i++;
    }

    Client w(tempIP);
    w.show();

    return a.exec();
}
