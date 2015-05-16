#ifndef REVERT_CPP
#define REVERT_CPP
#include "client.h"

#include "clientdefinitions.h"
#include "../../common/communications.h"
#include "../../common/instructions.h"

bool Client::handleRevert() {
    //filename in data.filename
    //required version is data.fileversion
    //max verison is fileversions[data.filename]

    //INITIALIZATION
    cout << "##cli brk1\n";
    std::string req(REVERT_REQUEST);
    std::string cont(CONTINUE);
    std::string conti; //for reading
    std::string filen = user.userID + "/" + CLIENT_SYNC_DIR+ "/" + data.filename;
    std::string filep = conn.returnAllButFileName(filen);
    boost::filesystem::path filep_path(filep);

    cout << "##cli brk2\n Filename=" << filen << "\n";

    if ( boost::filesystem::exists(filep_path)) {

    } else {
        boost::filesystem::create_directories(filep_path);
    }
    int req_version = data.fileversion;
    //ASSERT : Now, we merely have to download the file into location called filen.
    cout << "##cli brk3\n";

    conn.writeToSocket(req);
    cout << "##cli brk4\n";
    conn.readFromSocket(conti);
    cout << "##cli brk5\n";
    conn.writeToSocket(data.filename);
    cout << "##cli brk6\n";
    conn.readFromSocket(conti);
    cout << "##cli brk7\n";
    conn.writeToSocket(user.userID);
    cout << "##cli brk8\n";
    conn.readFromSocket(conti);
    cout << "##cli brk9\n";
    std::string str_req_v = to_string(req_version);

    conn.writeToSocket(str_req_v); //Tell the server the required version.
    cout << "##cli brk10\n";
    //Read the file and put it into the correct place.
    conn.readFromSocket_file(filen);
    cout << "##cli brk11\n";
    //And we're done.
    cout << "##cli brk12\n";
    this->addToFileLog(user.userID , data.filename , filen , req_version);
    cout << "##cli brk13\n";
    this->getServerFiles_login();
    cout << "##cli brk14\n";
    this->dropboxpage->updateServerFiles();
    cout << "##cli brk15\n";
    return true;
}

#endif
