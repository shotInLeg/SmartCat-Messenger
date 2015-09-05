#include "smartcat.h"
#include "ui_smartcat.h"

using namespace vkAPI;

void SmartCat::printDataToDialogList()
{
    qDebug() << "printDialog";
    ui->listDialogs->clear();

    for(QMap<int,Dialog>::iterator itr = VKontakte::chats.end()-1; itr != VKontakte::chats.begin()+1; itr--)
    {
        Dialog dialog;
        dialog = itr.value();
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon( QIcon( dialog.avatar() ) );
        item->setText(dialog.title() + "\n   " + dialog.body());

        ui->listDialogs->addItem(item);
    }
}

Dialog SmartCat::getCurrnentDialog(int row)
{
    qDebug() << "Row: " << row;
    QMap<int, Dialog>::iterator chat = VKontakte::chats.end() - (row + 1);
    currentDialog = chat.value();
    return currentDialog;
}

void SmartCat::printDataToMessageList()
{
    qDebug() << "printMessages";

    ui->lNameDialog->setText( currentDialog.title() );



    User selfUser = VKontakte::currentUser();
    ui->listMessages->clear();

    for(QMap<int, Message>::iterator itr = VKontakte::history.end()-1; itr != VKontakte::history.begin(); itr--)
    {
        Message message = itr.value();
        QListWidgetItem *item_mess = new QListWidgetItem();
        QTextEdit *textBox = new QTextEdit();
        if(message.fromId() == selfUser.id())
        {
            item_mess->setIcon( QIcon( selfUser.avatar50px() ) );
            item_mess->setSizeHint(QSize(0,65));
            textBox->setText( message.text() );
            textBox->setStyleSheet("background: rgb(0,0,0); color: rgb(255,255,255);");
        }
        else
        {
            item_mess->setIcon( QIcon( message.fromAvatar() ) );
            item_mess->setSizeHint(QSize(0,65));
            textBox->setText( message.text() );
            textBox->setStyleSheet("background: rgb(255,255,255); color: rgb(0,0,0);");
        }

        ui->listMessages->addItem( item_mess );
        ui->listMessages->setItemWidget(item_mess,textBox);
    }
}

void SmartCat::on_listDialogs_currentRowChanged(int currentRow)
{
    getCurrnentDialog( currentRow );
    th->startFunction = "loadHistory";
    th->id = currentDialog.id();
    connect( th, SIGNAL( messagesUpdated() ), this, SLOT( printDataToMessageList() ) );
    th->start();
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
