#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

SmartCat::SmartCat(QWidget *parent) : QWidget(parent), ui(new Ui::SmartCat), vk(new VKontakte)
{
    ui->setupUi(this);
    th = new PollThread();
    ui->listWidget->hide();

    appID = "4796858";
    scope = "notify,friends,photos,messages,groups";

    connect( ui->AuthBrowser, SIGNAL(urlChanged(QUrl)), this, SLOT( getToken(QUrl) ) );
    connect( this, SIGNAL( authSuccess() ), this, SLOT( changeCurrentWidget() ) );

    if ( !( vk->checkAccessToken() ) )
    {
        qDebug() << 9;
        ui->stackedWidget->setCurrentWidget( ui->Auth );
        qDebug() << 10;
        vk->autenthication( appID, scope, ui->AuthBrowser );
        qDebug() << 11;
    }
    else
    {
       printDataToDialogList();
    }
}
SmartCat::~SmartCat()
{
    delete ui;
}

void SmartCat::changeCurrentWidget()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void SmartCat::on_stackedWidget_currentChanged(int currentWidgetIndex)
{
    if( currentWidgetIndex == 0 ) //Settings
    {
    }
    if( currentWidgetIndex == 1 ) //Main
    {
    }
    if( currentWidgetIndex == 2 ) //Auth
    {
    }
}

void SmartCat::loging()
{
    qDebug() << "UIT Stop";
}








