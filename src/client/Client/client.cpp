#ifndef CLIENT_CPP
#define CLIENT_CPP
#include "client.h"
#include "ui_client.h"


//UNNECESSARY INCLUDES. REMOVE SOON.
#include"stdio.h"
#include"stdlib.h"
#include"sys/types.h"
#include"sys/socket.h"
#include"string.h"
#include"netinet/in.h"
#include"netdb.h"
#include "arpa/inet.h"
#include <iostream>
#include "../../common/instructions.h"
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <queue>
#include <QLineEdit>
#include <QMessageBox>

#include "clientping.cpp"
#include "launcher.cpp" // Also contains unlauncher.
#include "logintoreg.cpp" //
#include "userRegistration.cpp" //handleRegistration()
#include "userLogin.cpp" // handleLogin();
#include "fileUpload.cpp" // handleUpload();
#include "fileDownload.cpp" //handleDownload();
#include "fileRemove.cpp"
#include "sync.cpp"
#include "revert.cpp"
#include "share.cpp"
#include <boost/filesystem.hpp>
#include <unordered_map>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    this->loginpage = new LoginPage(this , csock);
    this->registerpage = new RegisterPage(this , csock);
    this->loginpage->hide();
    this->registerpage->hide();
    this->dropboxpage = NULL;
    ui->setupUi(this);

    //Assert : Presently, the client wants the IP Address.
}

Client::Client(string IP) {
    ui=new Ui::Client();

    this->loginpage = new LoginPage(this , csock);
    this->registerpage = new RegisterPage(this , csock);
    this->loginpage->hide();
    this->registerpage->hide();
    this->dropboxpage = NULL;
    ui->setupUi(this);
    QString x = QString::fromStdString(IP);
    this->ui->txt_serverip->setText(x);
    //Assert : Presently, the client wants the IP Address.
}

Client::~Client()
{
    delete ui;
}

void Client::on_btn_launch_clicked()
{
    this->eventHandler(LAUNCH);
}

bool Client::eventHandler( INSTRUCTION_TYPE instr ) { //Handle the InstructionData data appropriately.
    if (instr == PING_INSTR) {// to server
        return this->handlePing();
    } else if ( instr == LAUNCH) { // internal, except for connection
        this->launch(); //Done.
    } else if ( instr == LOGIN_TO_CLIENT) { //internal
        this->unlaunch(); //Done.
    } else if ( instr == LOGIN_TO_REGISTER) { //internal
        this->goToRegisterPage();
    } else if ( instr == REGISTER_TO_LOGIN_BACK) { //internal
        this->goBackToLoginPage(); //Done.
    } else if ( instr == REGISTER_TO_LOGIN_REGISTER) { //to server
        return this->handleRegistration(); //Done. Need to write server side
    } else if ( instr == LOGIN_TO_MAIN) { //to server
        return this->handleLogin(); //Done. Need to write server side.
    } else if ( instr == MAIN_TO_LOGIN) { //to server
        return this->handleLogout(); // Need to link GUI click to the event
    } else if ( instr == UPLOAD_FILE) { //to server
        std::queue<string> paths;
        string present = data.filename;
//        cout << "request to upload " << present << "\n";
        paths.push(present);
        bool rv =true;
        while ( paths.size() > 0 ) {
            //Get p.
            boost::filesystem::path p( paths.front() );
            paths.pop();
            if( boost::filesystem::is_directory(p)) {
//                cout << p.string() << " it is a directory\n";
                //Add all its kids into the vector of paths.
                for( boost::filesystem::directory_iterator it(p) ; it != boost::filesystem::directory_iterator() ; ++it) {
                    boost::filesystem::path nt = p/((it->path()).filename());
//                    cout << " #### NT=" <<  nt.string() << " #### ";
                    paths.push(nt.string());
                }
            } else {
//                cout << "file to be uploaded=" << p.string() << "\n";
                data.filename = p.string();
                rv = rv && this->handleUpload(); //Done. Need to write the communications and server side equivalent.
            }
        }
        return rv;
        //Haroun magic 1.

    } else if ( instr == DOWNLOAD_FILE) { //to server
        return this->handleDownload();
    } else if (instr == DOWNLOAD_SHARED_FILE) {
        return this->handleSharedDownload();
    } else if ( instr == REMOVE_FILE) { //to server
        return this->handleRemove();
    } else if ( instr == SYNC) { //to server - retrieves dates and decides. Works only for files which have been uploaded at least once.
        return this->handleSync();
    } else if ( instr == REVERT) { //to server
        return this->handleRevert();
    } else if ( instr == FILE_SHARE) { //to server
        return this->handleShare();
    } else if ( instr == FILE_UNSHARE ) {
        return this->handleUnshare();
    } else if ( instr == FILE_SEARCH ) {
        return this->handleSearch();
    } else if ( instr == MAIN_TO_DESKTOP ) {//have you handled this already?? its for exiting
        this->handleExit();
    } else if ( instr == MAIN_TO_DESKTOP ) {//have you handled this already?? its for exiting
        this->handleMyShare();//Assumes data.filename.
    } else { // to server
        //Assume exitting.
        this->handleExit();
    }
    return true;
}

/*
 *##################### MINION FUNCTIONS FOLLOW #############
*/

void Client::showMain() {
    bfs::path cwd(bfs::current_path());
    bfs::path syncpath = cwd;
    syncpath /= (user.userID + "/");

    this->dropboxpage = new DropBox( this , csock , syncpath.string());

    this->getServerFiles_login(); //Fetches files.
    this->dropboxpage->updateServerFiles(); //Updates GUI.
    this->loginpage->hide();
    this->dropboxpage->show();
}


void Client::handleExit() {
    std::string temp(EXIT_REQUEST);
    conn.writeToSocket( temp );
    ::close(csock);
    SSL_CTX_free(clientCTX);
    if (this->dropboxpage != NULL ){
        this->dropboxpage->client = NULL;
        delete this->dropboxpage;
    }
    if (this->loginpage != NULL) {
        this->loginpage->client= NULL;
        delete this->loginpage;
    }
    if (this->registerpage != NULL) {
        this->registerpage->client=NULL;
        delete this->registerpage;
    }
    delete ui;
    //return true;
}

//Populate Server List.




void Client::on_txt_serverip_selectionChanged()
{
    this->ui->txt_serverip->setText("");
}

#endif
