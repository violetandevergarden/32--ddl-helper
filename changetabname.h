#ifndef CHANGETABNAME_H
#define CHANGETABNAME_H

#include <QDialog>

namespace Ui {
class changetabname;
}

class changetabname : public QDialog
{
    Q_OBJECT

public:
    explicit changetabname(QWidget *parent = nullptr);
    ~changetabname();
    void refresh();//刷新

signals:
    void back(QString);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::changetabname *ui;
};

#endif // CHANGETABNAME_H
