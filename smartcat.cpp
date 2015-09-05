#include "smartcat.h"
#include "ui_smartcat.h"

SmartCat::SmartCat(QWidget *parent) : QWidget(parent), ui(new Ui::SmartCat)
{
    ui->setupUi(this);
    ui->listWidget->hide();
}

SmartCat::~SmartCat()
{
    delete ui;
}

void SmartCat::on_bSend_clicked()
{
    ui->stackedWidget->setCurrentWidget( ui->Auth );
    QString appID = "4796858";
    QString scope = "friends";
    QUrl uri = "https://oauth.vk.com/authorize?client_id=" + appID + "&scope=" + scope + " &redirect_uri=https://oauth.vk.com/blank.html&display=popup&response_type=token";
    ui->AuthBrowser->load(uri);
}

void SmartCat::on_bAdd_clicked()
{
    ui->listWidget->show();
}
