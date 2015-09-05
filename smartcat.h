#ifndef SMARTCAT_H
#define SMARTCAT_H

#include <QWidget>
#include <QMessageBox>
#include <QListWidget>
#include <QTableWidgetItem>
#include <QThread>
#include <QPlainTextEdit>
#include "smartcatbrowser.h"
#include "vkAPI/vkapi.h"

namespace Ui {
class SmartCat;
}

class DataThread : public QThread
{
    Q_OBJECT
public:
    QString id;
    QString startFunction;
    void run();

signals:
    void done();
    void dialogsUpdated();
    void messagesUpdated();
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
    DataThread *th;

};

#endif // SMARTCAT_H
