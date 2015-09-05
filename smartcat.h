#ifndef SMARTCAT_H
#define SMARTCAT_H

#include <QWidget>
#include <QMessageBox>
#include "smartcatbrowser.h"
#include "vkAPI/vkapi.h"

namespace Ui {
class SmartCat;
}

class SmartCat : public QWidget
{
    Q_OBJECT

public:
    explicit SmartCat(QWidget *parent = 0);
    ~SmartCat();
    QString appID;
    QString scope;

private slots:
    void on_bSend_clicked();
    void on_bAdd_clicked();

public slots:
    void getToken(QUrl url);
    void changeCurrentWidget();

signals:
    void authSuccess();

private:
    Ui::SmartCat *ui;
};

#endif // SMARTCAT_H
