#ifndef SEARCH_CPP
#define SEARH_CPP

#include "server.h"
#include "serverdefinitions.h"
#include "../../common/instructions.h"
#include "../../common/communications.h"

bool Server::handleSearch(){
    //Got the request.
    string conti(CONTINUE);
    conn.writeToSocket(conti);
    string cont;
    string searchfor;
    conn.readFromSocket(searchfor); //Get the search result.

    db.open();
    QSqlQuery searcher;
    //SELECT USERNAME FROM TABLE_NAME WHERE USERNAME LIKE 'searchfor%'
    string a,b,c,d,e;
    a= "SELECT USERNAME FROM " ;
    b = TABLE_NAME;
    c = " WHERE USERNAME LIKE '";
    d = "%";
    e = "';";
    string q= a+b+c+searchfor+d+e;
    QString qq = QString::fromStdString(q);
    searcher.exec(qq);
    cout << q << "\n";
    //Now , to send each result over.



    char msg[INF_TRANSFER_BUFFER_SIZE];
    char delimit[INF_TRANSFER_BUFFER_SIZE];
    memset(delimit , 0 , INF_TRANSFER_BUFFER_SIZE);
        delimit[0] = INF_TRANSFER_BEGIN_CHAR;
        delimit[INF_TRANSFER_BUFFER_SIZE-1] = '0';
    conn.writeToSocket(delimit , INF_TRANSFER_BUFFER_SIZE);
    cout << "wrote delimiter\n";
    while ( searcher.next() ) {
        conn.readFromSocket(cont);
        std::string next_user = searcher.value(0).toString().toStdString();
        //Convert next_user to char buffer.
        memset(msg , 0 , INF_TRANSFER_BUFFER_SIZE);
        for(int i=0; i<next_user.size(); ++i){
            msg[i] = next_user[i];
        }
        msg[INF_TRANSFER_END_CHAR] =='1';

        conn.writeToSocket(msg , INF_TRANSFER_BUFFER_SIZE);
    }
    cout << "done writing users \n";
    conn.readFromSocket(cont);
    memset(delimit , 0 , INF_TRANSFER_BUFFER_SIZE);
        delimit[0] = INF_TRANSFER_END_CHAR;
        delimit[INF_TRANSFER_BUFFER_SIZE-1] = '0';
    conn.writeToSocket(delimit , INF_TRANSFER_BUFFER_SIZE);

    db.close();
    return true;
}

#endif
