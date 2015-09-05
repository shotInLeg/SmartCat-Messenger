#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

void DataThread::run()
{

    if( startFunction ==  "loadDialogsList" )
    {
        VKontakte::loadDialogsList();
        emit dialogsUpdated();
    }
    if( startFunction ==  "loadHistory" )
    {
        VKontakte::loadHistory(id);
        emit messagesUpdated();
    }
    emit done();
}
