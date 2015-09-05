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
