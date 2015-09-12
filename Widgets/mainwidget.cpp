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
        item_mess->setSizeHint(QSize(0,200));
        QString place = "";
        QString avatar = "";

        /*QTextEdit *textBox = new QTextEdit();
        textBox->setReadOnly(true);
        if(message.from().id() == selfUser.id())
        {
            item_mess->setIcon( QIcon( selfUser.avatar50px() ) );
            item_mess->setSizeHint(QSize(0,65));
            textBox->setText( message.text() );
            textBox->setStyleSheet("height: auto; border-radius: 20px; background: rgb(34,107,179); color: rgb(255,255,255); margin: 7px; padding: 10px;");
        }
        else
        {
            item_mess->setIcon( QIcon( message.from().avatar50px() ) );
            item_mess->setSizeHint(QSize(0,65));
            textBox->setText( message.text() );
            textBox->setStyleSheet("height: auto; border-radius: 20px; background: rgb(255,255,255); color: rgb(0,0,0); margin: 7px; padding: 10px;");
        }
        */
        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout();
        QVBoxLayout *vlayout = new QVBoxLayout();

        QTextEdit *textEdit = new QTextEdit( message.text() );
        QLabel *photo = new QLabel();
        QLabel *label = new QLabel();

        if( message.from().id() != selfUser.id() )
        {
            QPixmap pix( message.from().avatar50px() );
            label->setPixmap( pix );
            label->setStyleSheet("width: 25px; height: 25px; border-radius: 25px;");
            textEdit->setStyleSheet("border-radius: 20px; background: rgb(216,216,216); color: rgb(0,0,0); margin: 7px; padding: 10px;");

            layout->addWidget( label );

            if( message.attachment() != "" )
            {
                qDebug() << "!=";
                //if( message.typeAttachment() == "photo")
                //{
                    qDebug() << message.typeAttachment();

                    QPixmap pix_photo( message.attachment() );
                    photo->setPixmap( pix_photo );

                    if(message.text() != "") vlayout->addWidget( textEdit );
                    vlayout->addWidget( photo );

                    layout->addLayout( vlayout );
                //}
                //else
                //{
                //    layout->addWidget( textEdit );
                //}
            }
            else
            {
                layout->addWidget( textEdit );
            }

        }
        if( message.from().id() == selfUser.id() )
        {
            QPixmap pix( selfUser.avatar50px() );
            label->setPixmap( pix );
            label->setStyleSheet("width: 25px; height: 25px; border-radius: 25px;");
            textEdit->setStyleSheet("border-radius: 20px; background: rgb(34,107,179); color: rgb(255,255,255); margin: 7px; padding: 10px;");

            if( message.attachment() != "" )
            {
                qDebug() << "!=";
                //if( message.typeAttachment() == "photo")
                //{
                    qDebug() << message.typeAttachment();

                    QPixmap pix_photo( message.attachment() );
                    photo->setPixmap( pix_photo );

                    if(message.text() != "") vlayout->addWidget( textEdit );
                    vlayout->addWidget( photo );

                    layout->addLayout( vlayout );
                //}
                //else
                //{
                //    layout->addWidget( textEdit );
                //}
            }
            else
            {
                layout->addWidget( textEdit );
            }
            layout->addWidget( label );
        }

        widget->setLayout(layout);

        ui->listMessages->addItem( item_mess );
        ui->listMessages->setItemWidget(item_mess, widget );
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
