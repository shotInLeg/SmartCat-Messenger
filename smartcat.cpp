#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

SmartCat::SmartCat(QWidget *parent) : QWidget(parent), ui(new Ui::SmartCat)
{
    ui->setupUi(this);
    th = new DataThread();
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
    else
    {
        th->startFunction = "loadDialogsList";
        connect( th, SIGNAL( dialogsUpdated() ), this, SLOT( printDataToDialogList() ) );
        th->start();
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






