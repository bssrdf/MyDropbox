#ifndef REVERT_CPP
#define REVERT_CPP


#include "server.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"

bool Server::handleRevert() {
    //Fetch file name,
    //Fetch owner
    //Fetch version,
    //FETCHING

    cout << "##srv brk1\n";
    std::string cont(CONTINUE);
    std::string filen , usr, str_ver;
    int ver;
    //fetched request already.
    conn.writeToSocket(cont);
    cout << "##srv brk2\n";

    conn.readFromSocket(filen);
    cout << "##srv brk3\n";

    conn.writeToSocket(cont);
    cout << "##srv brk4\n";
    conn.readFromSocket(usr);
    cout << "##srv brk5\n";
    conn.writeToSocket(cont);
    cout << "##srv brk6\n";
    conn.readFromSocket(str_ver); //Read the flename, use and version.

    //Fetch the file and write it.
    //To find filep.
    cout << "##srv brk7" << str_ver << "\n";

    db.open();
    QSqlQuery getMaxVersion;
    std::string a = "SELECT FILENAME,VERSION FROM " ;
    string b= USERTABLE;
    string c=" WHERE FILENAME='";
    string d="' AND OWNER='";
    string e = "';";
    string q =  a + b + c + filen + d + usr+e;
    QString qq = QString::fromStdString(q);
    getMaxVersion.exec(qq);
    db.close();
    cout << "###executed cmd=" << q << "\n";
    cout << "##srv brk8\n";

    int maxv=0;
    while( getMaxVersion.next() ) {
        maxv++;
    }

    cout << "##srv brk9" <<maxv <<"\n";

    string filep;
    cout << "##srv brk10\n";

    ver = atoi(str_ver.c_str());
    if ( ver == maxv ) {
        filep = SERVER_DIRECTORY + user.userID + "/" + filen;
    } else {
        filep = SERVER_DIRECTORY + user.userID + "/v_" + str_ver + "/" +  filen;
    }
    cout << "##srv brk11"<< filep<< "\n";

    conn.writeToSocket_file( filep );
    //ASSERT : File handling is done.
    cout << "##srv brk12\n";

    handleSync(user.userID);
    return true;
}

#endif
