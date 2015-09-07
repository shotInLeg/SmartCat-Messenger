#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

void SmartCat::getToken(QUrl url)
{
    if( vk->getAccessToken(url) == 0 )
    {
        User me = vk->currentUser();
        QMessageBox::information(this, "Вы вошли как", "Имя: " + me.firstName() + "\nФамилия: " + me.lastName());

        emit authSuccess(); // Удачное получение токена
    }
}
