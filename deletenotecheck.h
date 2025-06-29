#ifndef DELETENOTECHECK_H
#define DELETENOTECHECK_H

#include <QDialog>

namespace Ui {
class deletenotecheck;
}

class deletenotecheck : public QDialog
{
    Q_OBJECT

public:
    explicit deletenotecheck(QWidget *parent = nullptr);
    ~deletenotecheck();

private slots:
    void on_buttonBox_accepted();

signals:
    void back();

private:
    Ui::deletenotecheck *ui;
};

#endif // DELETENOTECHECK_H
