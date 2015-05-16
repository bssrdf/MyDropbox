#ifndef DROPBOX_CPP
#define DROPBOX_CPP
#include "dropbox.h"
#include "ui_dropbox.h"
#include <QTreeView>
#include <QDirModel>
#include <QFileSystemModel>
#include "clientdefinitions.h"
#include <boost/filesystem.hpp>
#include <QFileDialog>
#include <algorithm>
DropBox::DropBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DropBox)
{
    ui->setupUi(this);
}
namespace bfs = boost::filesystem;
DropBox::DropBox(Client* _client , Socket& _csock , string sharedfiledir) { // NECESSARY CONSTERUCTOE.
    ui =  new Ui::DropBox();
    ui->setupUi(this);

    this->setFixedSize(1900,1080);

    client = _client;

    QString userWelcome = "Welcome " + QString::fromStdString( this->client->user.userID);

    ui->lblUser->setText(userWelcome);

    this->distinguisher=0;

    this->sharer=0;

    this->clicked=0;

    this->listshare=0;

    //this->setStyleSheet("background-color: black;");
    ui->serverTreeWidget->setColumnCount(1);


    csock = _csock;

    model = new QFileSystemModel(this);

    model->setReadOnly(false);

    QString sPath = QString::fromStdString(sharedfiledir);

    //dirmodel = new QFileSystemModel(this);
    //model->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    model->setRootPath(sPath);

    //model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name );
    ui->clientTreeView->setModel(model);

    ui->clientTreeView->setRootIndex(model->setRootPath(sPath));


    QModelIndex index =model->index(QDir::currentPath());

    ui->clientTreeView->expand(index);

    ui->clientTreeView->scrollTo(index);

    ui->clientTreeView->setCurrentIndex((index));

    ui->clientTreeView->resizeColumnToContents(0);

    //ui->serverTreeView->setHeader("System Files");
}

DropBox::~DropBox()
{
    delete ui;
}

void DropBox::AddRoot(QString Name, const std::vector<QString> childName)
{
    QTreeWidgetItem *itm= new QTreeWidgetItem(ui->serverTreeWidget);
    itm->setText(0,Name);
    // ui->copTreeWidget->addTopLevelItem(itm);
    AddChild(itm,childName[0]);
    AddChild(itm,childName[1]);
}

void DropBox::AddChild(QTreeWidgetItem *parent,QString Name)
{

    QTreeWidgetItem *itm= new QTreeWidgetItem();
    itm->setText(0,Name);
    //ui->treeWidget->addTopLevelItem(itm);
    parent->addChild(itm);

}


void DropBox::on_btnMake_clicked()
{
    if(distinguisher==3)
    {
        QModelIndex index=ui->clientTreeView->currentIndex();
        if (!index.isValid())
        {
            QMessageBox::information(this,"Error","Choose an index first");
            return;
        }
        QString name = QInputDialog::getText(this,"Name","Enter a Name");
        if(name.isEmpty())
        {
            QMessageBox::information(this,"Error","Choose an index first");
            return;
        }
        model->mkdir(index,name);
    }
    else
    {
        QMessageBox::information(this,"Error","Choose an index in your directory first");
    }
}

void DropBox::on_btnDelete_clicked()
{
    if(distinguisher==3)
    {
        QModelIndex index=ui->clientTreeView->currentIndex();
        if (!index.isValid())
        {
            QMessageBox::information(this,"Error","Choose an index first");
            return;
        }
        if (model->fileInfo(index).isDir())
        {
            model->rmdir(index);
        }
        else
        {
            model->remove(index);
        }
    }
    else
    {
        QMessageBox::information(this,"Error","Choose an item to delete in your directory first");
    }
}

//void DropBox::on_btnSearch_clicked()
//{
//    if(this->ui->textSearch->text().toStdString()!="")
//    {
//        this->client->data.other_user.userID = this->ui->textSearch->text().toStdString();
//        this->client->data.type = USER_SEARCH;
//        bool reply= this->client->eventHandler(USER_SEARCH);
//        if(!reply)
//        {
//            QMessageBox msg;
//            msg.setText("Search error ");
//            msg.exec();
//        }
//        //ASSERT : userlist on Client->dropboxpage is now populated. USE THAT TO DISPLAY STUFF.
//        QMessageBox msg;
//        msg.setText(QString::fromStdString(userlist[0]));
//        msg.exec();
//    }
//    else
//    {
//        QMessageBox::information(this,"Error","Enter What to search");
//        return;
//    }
//}

void DropBox::on_btnUpload_clicked()
{
    if (this->distinguisher==3)
    {
        cout<<"yothere"<<endl<<endl;
        QModelIndex index=ui->clientTreeView->currentIndex();
        cout<<"indexinfo"<<index.data().toString().toStdString()<<endl<<endl;
        if (!index.isValid())
        {
            QMessageBox::information(this,"Error","Select Item to upload");
            return;
        }
        this->client->data.type = UPLOAD_FILE;
        //string pat = " hihihihih" + this->client->data.filename ;
        //    QString qpat = (model->filePath(this->ui->clientTreeView->currentIndex()));
        //    QMessageBox brk; brk.setText( qpat ); brk.exec();
        this->client->data.filename = (model->filePath(this->ui->clientTreeView->currentIndex())).toUtf8().constData();//this is a model index, convert to string
        bool reply= this->client->eventHandler(UPLOAD_FILE);
        if(!reply)
        {
            QMessageBox msg;
            msg.setText("File transfer error ");
            msg.exec();
        }
    }
    else
    {
        QMessageBox::information(this,"Error","Choose Item to Upload");

    }
}

void DropBox::on_btnSync_clicked()
{
    this->client->data.type = SYNC;
    bool reply= this->client->eventHandler(SYNC);
    if(!reply)
    {
       // QMessageBox::information(this,tr("Error"),tr("Sync Failed"));
    }
}

void DropBox::on_btnLogout_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this,"Just Checking","Are you sure you want to Logout?",QMessageBox::Yes | QMessageBox::No );
    if(reply==QMessageBox::No)
    {
        return;
    }
    else
    {
        this->client->eventHandler(MAIN_TO_LOGIN);
    }

}

void DropBox::on_btnExit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::information(this,"Just Checking","Are you sure you want to Exit?",QMessageBox::Yes | QMessageBox::No );
    if(reply==QMessageBox::No)
    {
        return;
    }
    else
    {
        this->client->eventHandler(MAIN_TO_DESKTOP);
    }
}

void DropBox::on_btnDownload_clicked()
{
    if(this->distinguisher==1)
    {
        if(ui->serverTreeWidget->currentItem()!=NULL)
        {
            //    cout<<"hey1"<<endl;
            QTreeWidgetItem* indie=(ui->serverTreeWidget->currentItem());

            std::string indexer=indie->text(0).toStdString();
            //QMessageBox::information(this,"hi",QString::fromStdString(indexer));
            while (indie->parent()!=NULL)
            {
                indie=(indie->parent());
                indexer= indie->text(0).toStdString() + "/" + indexer; //toString().toUtf8().constData();
            }

            std::set<string> filenames_copy = filenames;

            string beginningpart = indexer; //this is a model index, convert to string
            //QMessageBox::information(this,"hi",QString::fromStdString(beginningpart));
            for( std::set<string>::iterator it = filenames_copy.begin() ; it !=  filenames_copy.end() ; ++it) {
                std::string its = *it;

                auto res = std::mismatch(beginningpart.begin() ,  beginningpart.end() , its.begin());//Return mistmatch thingy
                if (  (its != "") && (fileowners[its] == this->client->user.userID) && (res.first == beginningpart.end()) ) {
                    this->client->data.filename = its;
                    //This thing should send a request for all files that are a subset
                    this->client->data.type = DOWNLOAD_FILE;
                    this->client->data.other_user.userID=this->client->user.userID;
                    bool reply= this->client->eventHandler(DOWNLOAD_FILE);

                    if(!reply)
                    {
                        //QMessageBox::information(this,tr("Error"),tr("Download Failed"));
                    }
                }
            }

        }
        else
        {
            QMessageBox::information(this,"Error","Select an item to download first");
        }
    }
    else if(this->distinguisher==2)
    {
        if(ui->shareTreeWidget->currentItem()!=NULL)
        {
            QTreeWidgetItem* indie=(ui->shareTreeWidget->currentItem());

            std::string indexer=indie->text(0).toStdString();
            //QMessageBox::information(this,"hi",QString::fromStdString(indexer));
            while (indie->parent()!=NULL)
            {
                indie=(indie->parent());
                indexer= indie->text(0).toStdString() + "/" + indexer; //toString().toUtf8().constData();
            }

            std::set<string> filenames_copy = filenames;

            string beginningpart = indexer; //this is a model index, convert to string
            //QMessageBox::information(this,"hi",QString::fromStdString(beginningpart));
            for( std::set<string>::iterator it = filenames_copy.begin() ; it !=  filenames_copy.end() ; ++it) {
                std::string its = *it;

                auto res = std::mismatch(beginningpart.begin() ,  beginningpart.end() , its.begin());//Return mistmatch thingy
                if (  (its != "") && (fileowners[its] != this->client->user.userID) && (res.first == beginningpart.end()) ) {
                    this->client->data.filename = its;
                    //This thing should send a request for all files that are a subset
                    this->client->data.type = DOWNLOAD_SHARED_FILE;
                    this->client->data.other_user.userID = fileowners[its];
                    bool reply= this->client->eventHandler(DOWNLOAD_SHARED_FILE);

                    if(!reply)
                    {
                       // QMessageBox::information(this,tr("Error"),tr("Download Failed"));
                    }
                }
            }
        }
        else
        {
            QMessageBox::information(this,"Error","Select an item to download first");

        }
    }
    else
    {
        QMessageBox::information(this,"Error","Select an item to download first");
    }
}

void DropBox::on_btnRemove_clicked() //TODEBUG.
{
    if (distinguisher==0)
    {
        QMessageBox::information(this,"Error","Select an item to remove from the server");

    }
    else if (distinguisher==1)
    { //Take from the server tree widget.
        if(ui->serverTreeWidget->currentItem())
        {
            std::string target;
            QTreeWidgetItem* indie=(ui->serverTreeWidget->currentItem());

            std::string indexer=indie->text(0).toStdString();
            //QMessageBox::information(this,"hi",QString::fromStdString(indexer));
            while (indie->parent()!=NULL)
            {
                indie=(indie->parent());
                indexer= indie->text(0).toStdString() + "/" + indexer; //toString().toUtf8().constData();
            } //GET THE INITIAL NODE

            //TODO : ASK FOR CONFIRMATION.

            std::set<string> filenames_copy = filenames;
            string beginningpart = indexer; //this is a model index, convert to string
            for( std::set<string>::iterator it = filenames_copy.begin() ; it !=  filenames_copy.end() ; ++it)
            {
                std::string its = *it;

                auto res = std::mismatch(beginningpart.begin() ,  beginningpart.end() , its.begin());//Return mistmatch thingy
                if (  (its != "") && (fileowners[its] == this->client->user.userID) && (res.first == beginningpart.end()) )
                {
                    this->client->data.filename = its;
                    //This thing should send a request for all files that are a subset
                    this->client->data.type = REMOVE_FILE;
                    this->client->data.other_user.userID= this->client->user.userID;
                    bool reply= this->client->eventHandler(REMOVE_FILE);

                    if(!reply)
                    {

                    }
                }
            }
        }
        else
        {
            QMessageBox::information(this,"Error","Select an item to remove");
        }


    }
    else
    {
        QMessageBox::information(this,"Error","Select an item to remove from the server");
    }
}

void DropBox::on_btnShare_clicked()
{
    cout << "btnShareClick detected\n";
    if (distinguisher==0)
    {
        QMessageBox::information(this,"Error","Select an item to share");

    }
    else if (distinguisher==1)
    {
        if(ui->serverTreeWidget->currentItem())
        {
            if (sharer==1)
            {
                cout << "###br1"<<endl;
                string target;
                QTreeWidgetItem* indie=(ui->serverTreeWidget->currentItem());
                cout << "###br2"<<endl;
                std::string indexer=indie->text(0).toStdString();
                //QMessageBox::information(this,"hi",QString::fromStdString(indexer));
                while (indie->parent()!=NULL)
                {
                    indie=(indie->parent());
                    indexer= indie->text(0).toStdString() + "/" + indexer; //toString().toUtf8().constData();
                } //GET THE INITIAL NODE
                cout << "###br3"<<endl;
                bool ok;

                string templol = "SHARE FILE " + indexer + " WITH " ;
                //            QString text = QInputDialog::getText(this, tr(templol.c_str()),
                //                                                 tr("User name:"), QLineEdit::Normal,
                //                                                 QDir::home().dirName(), &ok);
                QString text=this->ui->userListWidget->currentItem()->text();
                cout << "###br4"<<endl;
                if (!text.isEmpty()) {
                    target = text.toStdString(); //Far simpler to std::string !

                } else {

                }
                cout << "###br5"<<endl;
                std::set<string> filenames_copy = filenames;
                string beginningpart = indexer; //this is a model index, convert to string
                for( std::set<string>::iterator it = filenames_copy.begin() ; it !=  filenames_copy.end() ; ++it)
                {
                    std::string its = *it;

                    auto res = std::mismatch(beginningpart.begin() ,  beginningpart.end() , its.begin());//Return mistmatch thingy
                    if (  (its != "") && (fileowners[its] == this->client->user.userID) && (res.first == beginningpart.end()) )
                    {
                        this->client->data.filename = its;
                        //This thing should send a request for all files that are a subset
                        this->client->data.type = FILE_SHARE;
                        this->client->data.other_user.userID= target;
                        bool reply= this->client->eventHandler(FILE_SHARE);

                        if(!reply)
                        {

                        }
                    }
                }
                cout << "###br6"<<endl;
            }
            else
            {
                cout << "###br7"<<endl;
                QMessageBox::information(this,"Error","Select a user to share with");

            }
        }
        else
        {
            QMessageBox::information(this,"Error","Select an item to share");
        }
    }
    else
    {
        QMessageBox::information(this,"Error","Select an item to share");
    }
}

void DropBox::on_btnUnshare_clicked()
{
    if (distinguisher==0)
    {
        QMessageBox::information(this,"Error","Select an item to unshare");

    }
    else if (distinguisher==1)
    {
        if(ui->serverTreeWidget->currentItem())
        {
            if(listshare==1)
            {    string target;
                QTreeWidgetItem* indie=(ui->serverTreeWidget->currentItem());

                std::string indexer=indie->text(0).toStdString();
                //QMessageBox::information(this,"hi",QString::fromStdString(indexer));
                while (indie->parent()!=NULL)
                {
                    indie=(indie->parent());
                    indexer= indie->text(0).toStdString() + "/" + indexer; //toString().toUtf8().constData();
                } //GET THE INITIAL NODE

                bool ok;
                string templol = "UNSHARE FILE " + indexer + " FROM " ;
    //            QString text = QInputDialog::getText(this, tr(templol.c_str()),
    //                                                 tr("User name:"), QLineEdit::Normal,
    //                                                 QDir::home().dirName(), &ok);
                QString text=this->ui->sharedListWidget->currentItem()->text();
                if (!text.isEmpty())
                {
                    target = text.toStdString(); //Far simpler to std::string !
                }
                else
                {

                }
                std::set<string> filenames_copy = filenames;
                string beginningpart = indexer; //this is a model index, convert to string
                for( std::set<string>::iterator it = filenames_copy.begin() ; it !=  filenames_copy.end() ; ++it)
                {
                    std::string its = *it;

                    auto res = std::mismatch(beginningpart.begin() ,  beginningpart.end() , its.begin());//Return mistmatch thingy
                    if (  (its != "") && (fileowners[its] == this->client->user.userID) && (res.first == beginningpart.end()) )
                    {
                        this->client->data.filename = its;
                        //This thing should send a request for all files that are a subset
                        this->client->data.type = FILE_UNSHARE;
                        this->client->data.other_user.userID = target;
                        bool reply= this->client->eventHandler(FILE_UNSHARE);

                        if(!reply)
                        {
                            //QMessageBox::information(this,tr("Error"),tr("Download Failed"));
                        }
                    }
                }
                this->listshare=0;
            }
            else
            {
                QMessageBox::information(this,"Error","Select a user to unshare with");

            }
        }
        else
        {
            QMessageBox::information(this,"Error","Select an item to unshare");

        }
    }
    else
    {
        QMessageBox::information(this,"Error","Select an item to unshare");

    }
}

void DropBox::on_btnConfirmRevert_clicked()
{
    if(distinguisher==1)
    {
        std::string version =  this->ui->comboRevert->currentText().toStdString();
        std::string versionno=version.substr(8);
        cout << "versionnumber ="<<versionno<< "\n";


        if(ui->serverTreeWidget->currentItem())
        {

            QTreeWidgetItem* indie=(ui->serverTreeWidget->currentItem());
            cout << " ##hark1 \n";
            std::string indexer=indie->text(0).toStdString();
            cout << "##hark2 " << indexer << "\n";
            //QMessageBox::information(this,"hi",QString::fromStdString(indexer));
            while (indie->parent()!=NULL)
            {
                indie=(indie->parent());
                indexer= indie->text(0).toStdString() + "/" + indexer; //toString().toUtf8().constData();
            }
            cout << "#hark3 "<< indexer << "\n";


            this->client->data.fileversion = atoi(versionno.c_str());
            this->client->data.filename  = indexer;
            cout<<indexer<<" "<<this->client->data.fileversion<<endl;
            //QMessageBox::information(this,"hi",this->ui->serverTreeWidget->currentItem()->text(0));
            this->client->data.type = REVERT;
            bool reply= this->client->eventHandler( REVERT);
            if(!reply)
            {

            }
        }
        else
        {
            QMessageBox::information(this,"Error","Select an Item first");
        }
    }
    else
    {
        QMessageBox::information(this,"Error","Select an Item first");
    }
}

void DropBox::updateServerFiles() {

    std::set<std::string>::iterator it;
    it =filenames.begin();

    this->ui->serverTreeWidget->clear();
    this->ui->shareTreeWidget->clear();

    //    for( ; it != filenames.end(); ++it) {
    //        //For each file name ,
    //        std::string fn1 = *it; //Gets the file name.
    //        std::string fo1 = fileowners[fn1];
    //        QString fn = QString::fromStdString(fn1);
    //        QString fo = QString::fromStdString(fo1);
    //        if ( fo1 == this->client->user.userID) {
    //            AddItem( fn );
    //        } else {
    //            AddItemShare( fn , fo );
    //        }
    //    }

    this->populateServer();
    this->populateShareTree();
}

void DropBox::on_shareTreeWidget_clicked(const QModelIndex &index)
{
    this->ui->comboRevert->clear();
    this->ui->serverTreeWidget->clearSelection();
    this->ui->clientTreeView->clearSelection();
    this->distinguisher=2;
    //int y=this->fileversions[toString(index->data())];
    ui->comboRevert->addItem("Version 1");//+QString::number(i));


}

void DropBox::AddItem(QString Name) //Add an item to the serverTreeWidget
{
    QTreeWidgetItem *itm= new QTreeWidgetItem(ui->serverTreeWidget);
    itm->setText(0,Name); // itm->setText(1,size); // itm->setText(2,version);
}

void DropBox::AddItemShare(QString Name, QString Owner) //Add a widget to the sharewidget
{
    QTreeWidgetItem *itm= new QTreeWidgetItem(ui->shareTreeWidget);
    itm->setText(0,Name); itm->setText(1,Owner);
}

void DropBox::on_serverTreeWidget_clicked(const QModelIndex &index) //Just sets the active items and also toggles the distinguisher
{
    cout << "##brk1\n";
    this->ui->clientTreeView->clearSelection();
    cout << "##br2\n";
    this->ui->shareTreeWidget->clearSelection();
    cout << "##br3\n";
    this->ui->comboRevert->clear();
    cout << "##br4\n";
    this->distinguisher=1;
    cout << "##br5\n";
    std::string indexer=index.data().toString().toStdString();
    cout << "##br6\n";
    QModelIndex indie=index;
    cout << "##br7\n";
    while (indie.parent()!=QModelIndex())
    {
        indie=indie.parent();
        indexer= indie.data().toString().toStdString() + "/" + indexer; //toString().toUtf8().constData();
    }
    cout << "##br8\n";
    int y= this->fileversions[indexer];
    cout << "##br9\n";
    //QMessageBox::information(this,"hi",QString::fromStdString(indexer));
    for (int i=1;i<=y;i++)
    {
        ui->comboRevert->addItem("Version "+QString::number(i));
    }
    cout << "##br10\n";
    this->client->data.filename=index.data().toString().toStdString();
    cout<<this->client->data.filename<<endl;
    cout << "##br11\n";
    this->client->data.user.userID=this->client->user.userID;
    cout << "##br12\n";

    this->client->handleMyShare();

    cout << "##br13\n";
    this->ui->sharedListWidget->clear();
    cout << "##br14\n";
    std::set<string>::iterator it = names.begin();
    for (; it!=names.end(); ++it)
    {
        string its = *it;
        cout << its << "\n";
        this->ui->sharedListWidget->addItem(QString::fromStdString(its));
    }
    names.clear();
    cout << "##br15\n";
}

void DropBox::on_textSearch_selectionChanged()
{
    this->ui->textSearch->setText("");
}


void DropBox::on_btnMove_clicked() //Move button moves directory in pc into the shareable directory.
{
    using namespace boost::filesystem;
    //    QMessageBox::StandardButton reply;
    //    reply=QMessageBox::information(this,"hi","what",QMessageBox::Yes|QMessageBox::No);
    QMessageBox msgBox;
    msgBox.setText(trUtf8("What Do you want to move?"));
    QAbstractButton *myYesButton = msgBox.addButton(trUtf8("Directory"), QMessageBox::YesRole);
    QAbstractButton *myNoButton = msgBox.addButton(trUtf8("File"), QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.exec();

    //if(msgBox.clickedButton() == myNoButton)




    if (msgBox.clickedButton() == myYesButton)
    {
        QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        QDir::currentPath()
                                                        );
        std::string dir1=dir.toUtf8().constData();
        if (!exists(dir1)) {
            return;
        }
        boost::filesystem::path sourcepath(dir1);
        std::string pathcreator = this->client->user.userID+"/"+ CLIENT_SYNC_DIR + "/" + sourcepath.filename().string();


        path destinationpath(pathcreator);
        //        copy(sourcepath,destinationpath);

        this->client->conn.copy_directory_contents(sourcepath,destinationpath);

        QMessageBox::information(this,"hi",dir);
    }
    else if(msgBox.clickedButton() == myNoButton)
    {
        QString dir = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                   QDir::currentPath()
                                                   );
        std::string dir1=dir.toUtf8().constData();
        if (!exists(dir1)) {
            return;
        }
        boost::filesystem::path sourcepath(dir1);
        std::string pathcreator = this->client->user.userID+"/"+ CLIENT_SYNC_DIR + "/" + sourcepath.filename().string();


        path destinationpath(pathcreator);
        copy(sourcepath,destinationpath);
        QMessageBox::information(this,"hi",dir);
    } else {
        return;
    }


}

void DropBox::populateServer() {
    // filenames --> QStringList fileNames


    QStringList fileNames;//convert filenames to this

    std::set<string>::iterator it = filenames.begin();
    for ( ; it != filenames.end() ; ++it) {
        std::string its = *it;
        if(its != "") {
            if ( fileowners[its] == this->client->user.userID ) {
                QString qfilenamesi = QString::fromStdString(its);
                fileNames << qfilenamesi;
            }
        }
    } //ASSERT : Converted it.


    QTreeWidgetItem *topLevelItem = NULL;
    foreach (const QString &fileName, fileNames)
    {
        QStringList splitFileName = fileName.split("/");
        if ((splitFileName.size()==1) && (this->ui->serverTreeWidget->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty()))
        {
            QTreeWidgetItem *itm=new QTreeWidgetItem(ui->serverTreeWidget);
            itm->setText(0,splitFileName[0]);

        }


            // add root folder as top level item if treeWidget doesn't already have it
            if (this->ui->serverTreeWidget->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty())
            {
                topLevelItem = new QTreeWidgetItem;
                topLevelItem->setText(0, splitFileName[0]);
                this->ui->serverTreeWidget->addTopLevelItem(topLevelItem);
            }

            QTreeWidgetItem *parentItem = topLevelItem;

            // iterate through non-root directories (file name comes after)
            for (int i = 1; i < splitFileName.size() - 1; ++i)
            {
                // iterate through children of parentItem to see if this directory exists
                bool thisDirectoryExists = false;
                for (int j = 0; j < parentItem->childCount(); ++j)
                {
                    if (splitFileName[i] == parentItem->child(j)->text(0))
                    {
                        thisDirectoryExists = true;
                        parentItem = parentItem->child(j);
                        break;
                    }
                }

                if (!thisDirectoryExists)
                {
                    parentItem = new QTreeWidgetItem(parentItem);
                    parentItem->setText(0, splitFileName[i]);
                }
            }

            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, splitFileName.last());

    }

}

void DropBox::populateShareTree() {
    QStringList fileNames;//convert filenames to this
    std::set<string>::iterator it = filenames.begin();
    for ( ; it != filenames.end() ; ++it) {
        std::string its = *it;
        if(its != "") {
            if ( fileowners[its] != this->client->user.userID ) {
                QString qfilenamesi = QString::fromStdString(its);
                fileNames << qfilenamesi;
            }
        }
    } //ASSERT : Converted it.

    QTreeWidgetItem *topLevelItem = NULL;
    foreach (const QString &fileName, fileNames)
    {
        QStringList splitFileName = fileName.split("/");
        if ((splitFileName.size()==1) && (this->ui->shareTreeWidget->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty()))
        {
            QTreeWidgetItem *itm=new QTreeWidgetItem(ui->shareTreeWidget);
            itm->setText(0,splitFileName[0]);
        }
        // add root folder as top level item if treeWidget doesn't already have it
        else
        {
            if (this->ui->shareTreeWidget->findItems(splitFileName[0], Qt::MatchFixedString).isEmpty())
            {
                topLevelItem = new QTreeWidgetItem;
                topLevelItem->setText(0, splitFileName[0]);
                this->ui->shareTreeWidget->addTopLevelItem(topLevelItem);
            }

            QTreeWidgetItem *parentItem = topLevelItem;

            // iterate through non-root directories (file name comes after)
            for (int i = 1; i < splitFileName.size() - 1; ++i)
            {
                // iterate through children of parentItem to see if this directory exists
                bool thisDirectoryExists = false;
                for (int j = 0; j < parentItem->childCount(); ++j)
                {
                    if (splitFileName[i] == parentItem->child(j)->text(0))
                    {
                        thisDirectoryExists = true;
                        parentItem = parentItem->child(j);
                        break;
                    }
                }
                if (!thisDirectoryExists)
                {
                    parentItem = new QTreeWidgetItem(parentItem);
                    parentItem->setText(0, splitFileName[i]);
                }
            }
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, splitFileName.last());
        }
    }
}


void DropBox::on_clientTreeView_clicked(const QModelIndex &index)
{
    this->distinguisher=3;
    this->ui->serverTreeWidget->clearSelection();
    this->ui->shareTreeWidget->clearSelection();

}


void DropBox::on_textSearch_cursorPositionChanged(int arg1, int arg2)
{
    if (arg2>0)
    {


        this->client->data.other_user.userID = this->ui->textSearch->text().toStdString();
        cout << this->client->data.other_user.userID;
        this->client->handleSearch(); //Ideally should have called event handler with SEARCH , but who cares?
        std::sort(userlist.begin() , userlist.end());
        this->ui->userListWidget->clear();
        for (int i=0;i<userlist.size();i++)
        {
            this->ui->userListWidget->addItem(QString::fromStdString(userlist[i]));
        }


    }
    else
    {
        this->ui->userListWidget->clear();

    }
    this->sharer=0;

}

void DropBox::on_userListWidget_clicked(const QModelIndex &index)
{
    this->sharer=1;

    this->ui->textSearch->setText(index.data().toString());
    this->ui->userListWidget->setCurrentRow(0);
}

#endif

void DropBox::on_sharedListWidget_clicked(const QModelIndex &index)
{
    this->listshare=1;
}
