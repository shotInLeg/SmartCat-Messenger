#ifndef SMARTCATBROWSER_H
#define SMARTCATBROWSER_H

#include <QWidget>

namespace Ui {
class SmartCatBrowser;
}

class SmartCatBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit SmartCatBrowser(QWidget *parent = 0);
    ~SmartCatBrowser();

private:
    Ui::SmartCatBrowser *ui;
};

#endif // SMARTCATBROWSER_H
