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
    void on_pushButton_2_clicked();

private:
    Ui::SmartCat *ui;
};

#endif // SMARTCAT_H
