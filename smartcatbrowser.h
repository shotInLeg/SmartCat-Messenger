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

private slots:
    void on_pushButton_clicked();

private:
    Ui::SmartCatBrowser *ui;
};

#endif // SMARTCATBROWSER_H
