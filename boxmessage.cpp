#include "smartcat.h"
#include "ui_smartcat.h"

BoxMessage::BoxMessage(QString place, QString text, QString avatar)
{
    QTextEdit *textEdit = new QTextEdit();
    textEdit->setText(text);

    if( place == "left" )
        textEdit->setStyleSheet("background: rgb(255,255,255); color: rgb(0,0,0);");
    if( place == "right")
        textEdit->setStyleSheet("background: rgb(0,0,0); color: rgb(255,255,255);");

    QLabel *label = new QLabel();
    QPixmap pix( avatar );
    label->setPixmap( pix );

    QHBoxLayout *layout = new QHBoxLayout;

    if( place == "left")
    {
        layout->addWidget(label);
        layout->addWidget(textEdit);
    }
    if( place == "right" )
    {
        layout->addWidget(textEdit);
        layout->addWidget(label);
    }
    this->setLayout(layout);
}

