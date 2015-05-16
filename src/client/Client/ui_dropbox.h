/********************************************************************************
** Form generated from reading UI file 'dropbox.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DROPBOX_H
#define UI_DROPBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DropBox
{
public:
    QWidget *centralwidget;
    QTreeView *clientTreeView;
    QPushButton *btnSync;
    QPushButton *btnDownload;
    QPushButton *btnRemove;
    QPushButton *btnShare;
    QPushButton *btnUnshare;
    QPushButton *btnUpload;
    QPushButton *btnMake;
    QPushButton *btnLogout;
    QPushButton *btnDelete;
    QPushButton *btnExit;
    QLineEdit *textSearch;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboRevert;
    QPushButton *btnConfirmRevert;
    QTreeWidget *serverTreeWidget;
    QTreeWidget *shareTreeWidget;
    QPushButton *btnMove;
    QListWidget *userListWidget;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *lblUser;
    QListWidget *sharedListWidget;
    QLabel *label_5;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QFrame *line_4;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DropBox)
    {
        if (DropBox->objectName().isEmpty())
            DropBox->setObjectName(QStringLiteral("DropBox"));
        DropBox->resize(1900, 1080);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(48, 203, 237, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        DropBox->setPalette(palette);
        centralwidget = new QWidget(DropBox);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        clientTreeView = new QTreeView(centralwidget);
        clientTreeView->setObjectName(QStringLiteral("clientTreeView"));
        clientTreeView->setGeometry(QRect(600, 180, 401, 431));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush2(QColor(0, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        QBrush brush3(QColor(0, 255, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush3);
        QBrush brush4(QColor(159, 158, 158, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        QBrush brush5(QColor(240, 240, 240, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush5);
        clientTreeView->setPalette(palette1);
        btnSync = new QPushButton(centralwidget);
        btnSync->setObjectName(QStringLiteral("btnSync"));
        btnSync->setGeometry(QRect(300, 650, 181, 27));
        QPalette palette2;
        QBrush brush6(QColor(170, 0, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush6);
        QBrush brush7(QColor(0, 255, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush7);
        QBrush brush8(QColor(170, 85, 255, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush8);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush);
        btnSync->setPalette(palette2);
        btnDownload = new QPushButton(centralwidget);
        btnDownload->setObjectName(QStringLiteral("btnDownload"));
        btnDownload->setGeometry(QRect(80, 650, 181, 27));
        btnRemove = new QPushButton(centralwidget);
        btnRemove->setObjectName(QStringLiteral("btnRemove"));
        btnRemove->setGeometry(QRect(300, 690, 181, 27));
        btnShare = new QPushButton(centralwidget);
        btnShare->setObjectName(QStringLiteral("btnShare"));
        btnShare->setGeometry(QRect(80, 690, 181, 27));
        btnUnshare = new QPushButton(centralwidget);
        btnUnshare->setObjectName(QStringLiteral("btnUnshare"));
        btnUnshare->setGeometry(QRect(300, 730, 181, 27));
        btnUpload = new QPushButton(centralwidget);
        btnUpload->setObjectName(QStringLiteral("btnUpload"));
        btnUpload->setGeometry(QRect(602, 650, 181, 27));
        btnMake = new QPushButton(centralwidget);
        btnMake->setObjectName(QStringLiteral("btnMake"));
        btnMake->setGeometry(QRect(602, 690, 181, 27));
        btnLogout = new QPushButton(centralwidget);
        btnLogout->setObjectName(QStringLiteral("btnLogout"));
        btnLogout->setGeometry(QRect(602, 730, 181, 27));
        btnDelete = new QPushButton(centralwidget);
        btnDelete->setObjectName(QStringLiteral("btnDelete"));
        btnDelete->setGeometry(QRect(840, 690, 161, 27));
        btnExit = new QPushButton(centralwidget);
        btnExit->setObjectName(QStringLiteral("btnExit"));
        btnExit->setGeometry(QRect(840, 730, 161, 27));
        textSearch = new QLineEdit(centralwidget);
        textSearch->setObjectName(QStringLiteral("textSearch"));
        textSearch->setGeometry(QRect(1510, 180, 341, 27));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(78, 140, 181, 21));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(600, 130, 241, 31));
        label_2->setFont(font);
        label_2->setTextFormat(Qt::AutoText);
        comboRevert = new QComboBox(centralwidget);
        comboRevert->setObjectName(QStringLiteral("comboRevert"));
        comboRevert->setGeometry(QRect(80, 770, 401, 27));
        btnConfirmRevert = new QPushButton(centralwidget);
        btnConfirmRevert->setObjectName(QStringLiteral("btnConfirmRevert"));
        btnConfirmRevert->setGeometry(QRect(80, 730, 181, 27));
        serverTreeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        serverTreeWidget->setHeaderItem(__qtreewidgetitem);
        serverTreeWidget->setObjectName(QStringLiteral("serverTreeWidget"));
        serverTreeWidget->setGeometry(QRect(78, 180, 401, 431));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush);
        serverTreeWidget->setPalette(palette3);
        shareTreeWidget = new QTreeWidget(centralwidget);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        shareTreeWidget->setHeaderItem(__qtreewidgetitem1);
        shareTreeWidget->setObjectName(QStringLiteral("shareTreeWidget"));
        shareTreeWidget->setGeometry(QRect(1120, 180, 321, 431));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        shareTreeWidget->setPalette(palette4);
        btnMove = new QPushButton(centralwidget);
        btnMove->setObjectName(QStringLiteral("btnMove"));
        btnMove->setGeometry(QRect(840, 650, 161, 27));
        userListWidget = new QListWidget(centralwidget);
        userListWidget->setObjectName(QStringLiteral("userListWidget"));
        userListWidget->setGeometry(QRect(1510, 230, 341, 381));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        userListWidget->setPalette(palette5);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1120, 140, 221, 21));
        label_3->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1510, 140, 161, 31));
        label_4->setFont(font);
        lblUser = new QLabel(centralwidget);
        lblUser->setObjectName(QStringLiteral("lblUser"));
        lblUser->setGeometry(QRect(80, 30, 321, 71));
        QFont font1;
        font1.setPointSize(26);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        lblUser->setFont(font1);
        sharedListWidget = new QListWidget(centralwidget);
        sharedListWidget->setObjectName(QStringLiteral("sharedListWidget"));
        sharedListWidget->setGeometry(QRect(1510, 760, 341, 211));
        QPalette palette6;
        palette6.setBrush(QPalette::Active, QPalette::Text, brush);
        palette6.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette6.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette6.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette6.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette6.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        sharedListWidget->setPalette(palette6);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(1510, 710, 191, 41));
        label_5->setFont(font);
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(1050, 0, 20, 1061));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(1470, 0, 20, 1061));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(1477, 670, 391, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(530, 0, 20, 1061));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        DropBox->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(DropBox);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        DropBox->setStatusBar(statusbar);

        retranslateUi(DropBox);

        QMetaObject::connectSlotsByName(DropBox);
    } // setupUi

    void retranslateUi(QMainWindow *DropBox)
    {
        DropBox->setWindowTitle(QApplication::translate("DropBox", "myDropBox", 0));
        btnSync->setText(QApplication::translate("DropBox", "Sync", 0));
        btnDownload->setText(QApplication::translate("DropBox", "Download", 0));
        btnRemove->setText(QApplication::translate("DropBox", "Remove", 0));
        btnShare->setText(QApplication::translate("DropBox", "Share", 0));
        btnUnshare->setText(QApplication::translate("DropBox", "Unshare", 0));
        btnUpload->setText(QApplication::translate("DropBox", "Upload", 0));
        btnMake->setText(QApplication::translate("DropBox", "MakeDir", 0));
        btnLogout->setText(QApplication::translate("DropBox", "LogOut", 0));
        btnDelete->setText(QApplication::translate("DropBox", "Delete", 0));
        btnExit->setText(QApplication::translate("DropBox", "Exit", 0));
        label->setText(QApplication::translate("DropBox", "Server Files", 0));
        label_2->setText(QApplication::translate("DropBox", "Client Files", 0));
        comboRevert->clear();
        comboRevert->insertItems(0, QStringList()
         << QApplication::translate("DropBox", "Version 1", 0)
        );
        btnConfirmRevert->setText(QApplication::translate("DropBox", "Revert!", 0));
        btnMove->setText(QApplication::translate("DropBox", "Move", 0));
        label_3->setText(QApplication::translate("DropBox", "Shared Files", 0));
        label_4->setText(QApplication::translate("DropBox", "Search", 0));
        lblUser->setText(QApplication::translate("DropBox", "TextLabel", 0));
        label_5->setText(QApplication::translate("DropBox", "Shared With", 0));
    } // retranslateUi

};

namespace Ui {
    class DropBox: public Ui_DropBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DROPBOX_H
