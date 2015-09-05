#ifndef SMARTCAT_H
#define SMARTCAT_H

#include <QWidget>

namespace Ui {
class SmartCat;
}

class SmartCat : public QWidget
{
    Q_OBJECT

public:
    explicit SmartCat(QWidget *parent = 0);
    ~SmartCat();

private slots:
    void on_bSend_clicked();

    void on_bAdd_clicked();

private:
    Ui::SmartCat *ui;
};

#endif // SMARTCAT_H
