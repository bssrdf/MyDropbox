#ifndef DROPBOX_H
#define DROPBOX_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QtCore>
#include <QtGui>
#include <vector>
#include <QDirModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QFileSystemModel>

class Client;

#include "../../common/instructions.h"
#include "../../common/communications.h" //Defines socket.
#include <unordered_map>
#include <set>
#include <vector>

namespace Ui {
class DropBox;
}

class DropBox : public QMainWindow
{
    Q_OBJECT
    void AddRoot(QString Name, const std::vector<QString> childName);
    void AddChild(QTreeWidgetItem *parent,QString Name);
    
public:
    explicit DropBox(QWidget *parent = 0);
    DropBox(Client* _client , Socket& _csock , std::string sharefile);
    ~DropBox();

    std::unordered_map< std::string , int > fileversions;
    std::set< std::string > filenames;
    std::unordered_map< std::string , std::string > fileowners;
    std::vector<std::string> userlist;

    void updateServerFiles();

    void AddItem( QString fname );
    void AddItemShare(QString fn , QString owner);
    Client* client;
    std::set<std::string>  names; //Contains shared files given a file.
private slots:
    void on_btnMake_clicked();
    void on_btnDelete_clicked();
    void on_btnUnshare_clicked();
    void on_btnConfirmRevert_clicked();
    //void on_btnSearch_clicked();
    void on_btnUpload_clicked();
    void on_btnSync_clicked();
    void on_btnLogout_clicked();
    void on_btnExit_clicked();
    void on_btnDownload_clicked();
    void on_btnRemove_clicked();
    void on_btnShare_clicked();
    void on_shareTreeWidget_clicked(const QModelIndex &index);
    void on_serverTreeWidget_clicked(const QModelIndex &index);
    void on_textSearch_selectionChanged();
    void on_btnMove_clicked();
    void on_clientTreeView_clicked(const QModelIndex &index);
    void on_textSearch_cursorPositionChanged(int arg1, int arg2);
    void on_userListWidget_clicked(const QModelIndex &index);

    void on_sharedListWidget_clicked(const QModelIndex &index);

private:
    Socket csock;
    Ui::DropBox *ui;
    QFileSystemModel *model;
    QFileSystemModel *dirmodel;
    int distinguisher;
    int sharer;
    int clicked;
    int listshare;
    void populateServer();
    void populateShareTree();
};

#include "client.h" //Safe because forward declarations and header guards.
#endif // DROPBOX_H


