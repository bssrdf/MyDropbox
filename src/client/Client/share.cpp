#ifndef SHARE_CPP
#define SHARE_CPP
#include "client.h"

bool Client::handleShare() {
    std::string filename = data.filename;
    std::string otheruser = data.other_user.userID;

    std::string cont;
    std::string conti(CONTINUE);

    std::string req(SHARE_REQUEST);
    conn.writeToSocket(req); //Write request
    conn.readFromSocket(cont); //read a continue
    conn.writeToSocket(filename); //Send the filename
    conn.readFromSocket(cont); //read a continue;
    conn.writeToSocket(otheruser); //Write the other user.
    //Read answer.
    std::string answer;
    conn.readFromSocket(answer);

    conn.writeToSocket(conti);
    this->getServerFiles_login();
    this->dropboxpage->updateServerFiles();
    //And we're done.
    if (answer == SHARE_ACCEPTED) {
        return true;
    } else {
        return false;
    }
}

bool Client::handleUnshare() {
    std::string filename = data.filename;
    std::string otheruser = data.other_user.userID;
    cout << " unsharing file=" << filename << " of user=" << user.userID << " with otherdude=" << data.other_user.userID << "\n";

    std::string cont;
    std::string conti(CONTINUE);
    std::string req(UNSHARE_REQUEST);
    conn.writeToSocket(req); //Write request
    conn.readFromSocket(cont);
    conn.writeToSocket(filename);
    conn.readFromSocket(cont); //read a continue
    conn.writeToSocket(otheruser); //Write the other user.
    //Read answer.
    std::string answer;
    conn.readFromSocket(answer);
    conn.writeToSocket(conti);

    this->getServerFiles_login();
    this->dropboxpage->updateServerFiles();
    //And we're done.
    if (answer == UNSHARE_ACCEPTED) {
        return true;
    } else {
        return false;
    }
}

bool Client::handleMyShare() {
    //Reads a file, assumes filename given in data.filename, userId in data.user
    //Puts the data into a vector - kabir decides.
    cout << " #### bak1\n";
    std::string req(RETURN_ALL_SHARED);
    conn.writeToSocket((req));
    cout << " #### bak2\n";
    std::string conti;

    conn.readFromSocket(conti);
    cout << " #### bak3\n";
    conn.writeToSocket(data.filename);
    cout << " #### bak4\n";
    conn.readFromSocket(conti);
    cout << " #### bak5\n";
    conn.writeToSocket(data.user.userID);
    cout << " #### bak6\n";
    conn.readFromSocket(conti);
    cout << " #### bak7\n";

    string _tempfile = "HarmanDeclares.txt";
    cout << " #### bak8\n";
    conn.readFromSocket_file(_tempfile);
    cout << " #### bak9\n";
    std::string cont(CONTINUE);
    conn.writeToSocket(cont);
    //Harman processes filea nd puts it in place for kabir.

//    this->getServerFiles_login();
//    cout << " #### bak10\n";
//    this->dropboxpage->updateServerFiles();
//    cout << " #### bak11\n";
    string name;
    ifstream f;
    f.open(_tempfile);
    string trash;
    f >> trash; //Trash values.
    while(f) {
        f >> name;
        if (name=="") {
            //Dont add it.
        } else {
            this->dropboxpage->names.insert(name);
        }
    }
    cout << " #### bak12\n";
    f.close();

    return true;
}


bool Client::addToFileLog_shared(string uid, string fname, string _owner) {
    string logfilepath = uid + "/" + CLIENT_SHARE_DIR + "/" + uid + CLIENT_SHARE_DIR;
    fstream reader(logfilepath , ios::in);
    string logfilepathtemp = uid + "/" + CLIENT_SHARE_DIR + "/" + uid + CLIENT_SHARE_DIR + "temp";
    fstream writer(logfilepathtemp , ios::out);


    bool found = false;
    string file , owner;
    while ( !found ) {
        reader >> file;
        reader >> owner;
        if ( file == fname ) {
            found = true;
            file = fname;
            owner = _owner;
        }
        writer << file;
        writer << owner;
    }
    if ( !found ) {
        writer << fname << "\t" << _owner << "\n";
    }

    boost::filesystem::path olfile( logfilepathtemp );
    boost::filesystem::path newfile( logfilepath );
    boost::filesystem::rename( olfile, newfile );
    return true;
}

#endif
