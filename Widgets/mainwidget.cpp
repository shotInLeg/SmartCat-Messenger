#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

void SmartCat::printDataToDialogList()
{
    qDebug() << "printDialog";


    vk->loadDialogsList();

    qDebug() << "end";
    ui->listDialogs->clear();

    for(QMap<int,Dialog>::iterator itr = vk->chats.end()-1; itr != vk->chats.begin()+1; itr--)
    {
        Dialog dialog;
        dialog = itr.value();
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon( QIcon( dialog.avatar() ) );
        item->setText(dialog.title() + "\n   " + dialog.body());

        ui->listDialogs->addItem(item);
    }
}

void SmartCat::printDataToMessageList()
{
    qDebug() << "printMessages title=" << currentDialog.title();


    vk->loadHistory( currentDialog.id() );
    ui->lNameDialog->setText( currentDialog.title() );

    User selfUser = vk->currentUser();
    ui->listMessages->clear();

    for(QMap<int, Message>::iterator itr = vk->history.end()-1; itr != vk->history.begin(); itr--)
    {
        Message message = itr.value();
        QListWidgetItem *item_mess = new QListWidgetItem();
        QTextEdit *textBox = new QTextEdit();
        if(message.from().id() == selfUser.id())
        {
            item_mess->setIcon( QIcon( selfUser.avatar50px() ) );
            item_mess->setSizeHint(QSize(0,65));
            textBox->setText( message.text() );
            textBox->setStyleSheet("background: rgb(0,0,0); color: rgb(255,255,255);");
        }
        else
        {
            item_mess->setIcon( QIcon( message.from().avatar50px() ) );
            item_mess->setSizeHint(QSize(0,65));
            textBox->setText( message.text() );
            textBox->setStyleSheet("background: rgb(255,255,255); color: rgb(0,0,0);");
        }

        ui->listMessages->addItem( item_mess );
        ui->listMessages->setItemWidget(item_mess,textBox);
    }
}

Dialog SmartCat::getCurrnentDialog(int row)
{
   QMap<int, Dialog>::iterator chat = vk->chats.end() - (row + 1);
   currentDialog = chat.value();
   return currentDialog;
}

void SmartCat::on_listDialogs_currentRowChanged(int currentRow)
{
    getCurrnentDialog( currentRow );
    printDataToMessageList();
}

void SmartCat::on_bSend_clicked()
{
   vk->sendMessage( currentDialog.id(), ui->textMessage->text() );
   ui->textMessage->setText("");
   printDataToMessageList();
   printDataToDialogList();
}

void SmartCat::on_bAdd_clicked()
{
    //ui->listWidget->show();
}
