#include "smartcatbrowser.h"
#include "ui_smartcatbrowser.h"

SmartCatBrowser::SmartCatBrowser(QWidget *parent) : QWidget(parent), ui(new Ui::SmartCatBrowser)
{
    ui->setupUi(this);
}

SmartCatBrowser::~SmartCatBrowser()
{
    delete ui;
}

void SmartCatBrowser::on_pushButton_clicked()
{
    //ui->browser->load( QUrl("https://youtu.be/0nlJuwO0GDs") );
    //ui->browser->setHtml( "<iframe src=\"http://vk.com/video_ext.php?oid=-38683579&id=171144543&hash=0af5f49e074fa433&hd=1\" width=\"640\" height=\360\"  frameborder=\"0\"></iframe>" );
}
