#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

SmartCat::SmartCat(QWidget *parent) : QWidget(parent), ui(new Ui::SmartCat)
{
    ui->setupUi(this);
    ui->listWidget->hide();

    appID = "4796858";
    scope = "notify,friends,photos,messages,groups";

    connect( ui->AuthBrowser, SIGNAL(urlChanged(QUrl)), this, SLOT( getToken(QUrl) ) );
    connect( this, SIGNAL( authSuccess() ), this, SLOT( changeCurrentWidget() ) );

    if ( !VKontakte::checkAccessToken() )
    {
        ui->stackedWidget->setCurrentWidget( ui->Auth );
        VKontakte::autenthication( appID, scope, ui->AuthBrowser );
    }
}

SmartCat::~SmartCat()
{
    delete ui;
}

void SmartCat::getToken(QUrl url)
{
    if( VKontakte::getAccessToken(url) == 0 )
    {
        User user = VKontakte::currentUser();
        QMessageBox::information(this, "Вы вошли как", "Имя: " + user.firstName() + "\nФамилия: " + user.lastName());

        emit authSuccess(); // Удачное получение токена
    }
}

void SmartCat::changeCurrentWidget()
{
    ui->stackedWidget->setCurrentWidget( ui->MainWidget );
}


void SmartCat::on_bSend_clicked()
{


    //SmartCatBrowser *browser1 = new SmartCatBrowser();
    //browser1->showFullScreen();
}

void SmartCat::on_bAdd_clicked()
{
    ui->listWidget->show();
}


