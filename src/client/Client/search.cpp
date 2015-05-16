#ifndef SEARCH_CPP
#define SEARCH_CPP
#include "client.h"
#include "clientdefinitions.h"
#include "../../common/communications.h"
#include "../../common/instructions.h"

bool Client::handleSearch()
{
    //Search for all the users in the database.
    this->dropboxpage->userlist.clear(); //Empties it.
    string req(USER_FETCH);
    conn.writeToSocket(req);
    std::string conti;
    conn.readFromSocket(conti); //Read a continue.
    std::string cont(CONTINUE);

    string searchfor= data.other_user.userID;
    conn.writeToSocket(searchfor);




    char incomingbuf[INF_TRANSFER_BUFFER_SIZE];
    memset(incomingbuf , 0 , INF_TRANSFER_BUFFER_SIZE);

    conn.readFromSocket(incomingbuf , INF_TRANSFER_BUFFER_SIZE);
    //ASSERT : It has begun.
    bool moar= true;
    while(moar) {
        cout << "inside loop \n";
        conn.writeToSocket(cont);
        memset(incomingbuf , 0 , INF_TRANSFER_BUFFER_SIZE);
        conn.readFromSocket(incomingbuf , INF_TRANSFER_BUFFER_SIZE);
        if ( incomingbuf[INF_TRANSFER_BUFFER_SIZE-1] =='0' ) {//Denotes end of transfer.
            moar = false;
            break;
        }
        std::string next_user( incomingbuf );
        if( incomingbuf[INF_TRANSFER_BUFFER_SIZE-2] != 0){
            //The next_user string is too long.
            next_user = next_user.substr(0,next_user.size()-1);
        } else {
            //Its all cool yo.
        }
        if (next_user != "") {
            this->dropboxpage->userlist.push_back(next_user);
        }
    }
    return true;
}

#endif
