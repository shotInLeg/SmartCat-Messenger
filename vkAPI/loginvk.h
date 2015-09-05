#ifndef LOGINVK_H
#define LOGINVK_H

#include <QDialog>
#include <QMessageBox>

#include "vkapi.h"

namespace Ui {
class LoginVK;
}

class LoginVK : public QDialog
{
    Q_OBJECT

public:
    explicit LoginVK(QWidget *parent = 0);
    ~LoginVK();

private:
    Ui::LoginVK *ui;

public slots:
    void getToken(QUrl url);

signals:
    void authSuccess();
};

#endif // LOGINVK_H
