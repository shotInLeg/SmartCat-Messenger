#include "loginvk.h"
#include "ui_loginvk.h"

using namespace vkAPI;

LoginVK::LoginVK(QWidget *parent) : QDialog(parent), ui(new Ui::LoginVK)
{
    ui->setupUi(this);

    connect( ui->vkLogin, SIGNAL(urlChanged(QUrl)), this, SLOT( getToken(QUrl) ) );
    connect( this, SIGNAL( authSuccess() ), this, SLOT(close()) );

    VKontakte::autenthication("4796858","notify,friends,photos,messages,groups",ui->vkLogin);
}

LoginVK::~LoginVK()
{
    delete ui;
}

void LoginVK::getToken(QUrl url)
{
    int result = VKontakte::getAccessToken(url);
    if(result == 0)
    {
        User user = VKontakte::currentUser();
        QMessageBox::information(this, "Вы вошли как", "Имя: " + user.firstName() + "\nФамилия: " + user.lastName());

        emit authSuccess(); // Удачное получение токена
    }
    else
    {

    }
}
