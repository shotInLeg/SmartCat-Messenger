#ifndef SMARTCAT_H
#define SMARTCAT_H

#include <QWidget>
#include <QMessageBox>
#include <QListWidget>
#include <QTableWidgetItem>
#include <QThread>
#include <QPlainTextEdit>
#include <exception>
#include <functional>
#include <iostream>
#include "smartcatbrowser.h"
#include "vkAPI/vkapi.h"

namespace Ui
{
    class SmartCat;
    class PollThread;
    class UI;
}

class PollThread : public QThread
{
    Q_OBJECT
private:
    QList< int(*)(QString) > queueFunction;

public:
    void run();
    void addQueue(const int(*)(QString) );

signals:
    void done();
    void dialogsUpdated();
    void messagesUpdated();
};

class BoxMessage : public QWidget
{
    Q_OBJECT

public:
    BoxMessage();
    BoxMessage(QString place, QString text, QString avatar);
    BoxMessage(QString text, QMap<QString, QString> attachments);
};

class SmartCat : public QWidget
{
    Q_OBJECT

public:
    explicit SmartCat(QWidget *parent = 0);
    ~SmartCat();

public:
    QString appID;
    QString scope;
    vkAPI::Dialog currentDialog;

private slots:
    void on_bSend_clicked();
    void on_bAdd_clicked();
    void on_stackedWidget_currentChanged(int currentWidgetIndex);
    void on_listDialogs_currentRowChanged(int currentRow);
    void printDataToDialogList();
    void printDataToMessageList();
    vkAPI::Dialog getCurrnentDialog(int row);
    void loging();

public slots:
    void getToken(QUrl url);
    void changeCurrentWidget();


signals:
    void authSuccess();

protected:
    Ui::SmartCat *ui;
    PollThread *th;
    vkAPI::VKontakte *vk;

};

#endif // SMARTCAT_H
