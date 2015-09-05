#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

void SmartCat::getToken(QUrl url)
{
    if( VKontakte::getAccessToken(url) == 0 )
    {
        User user = VKontakte::currentUser();
        QMessageBox::information(this, "Вы вошли как", "Имя: " + user.firstName() + "\nФамилия: " + user.lastName());

        emit authSuccess(); // Удачное получение токена
    }
}
