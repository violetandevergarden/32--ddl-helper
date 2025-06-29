#ifndef ESTABLISHQUEST_H
#define ESTABLISHQUEST_H

#include <QDialog>
#include<cstring>
namespace Ui {
class establishquest;
}

class establishquest : public QDialog
{
    Q_OBJECT

public:
    QString title,content,dateString,emer="no";
    explicit establishquest(QWidget *parent = nullptr);
    ~establishquest();

signals:
    void updatetable(QString &a,QString& b,QString &c,QString &d,int u);

private slots:
    void on_buttonBox_accepted();

    void on_calendarWidget_clicked(const QDate &date);

    void on_emerbutton_clicked();

    void on_normalbutton_clicked();

    void on_notemerbutton_clicked();

    void on_finishedpushButton_clicked();

public:
    Ui::establishquest *ui;
public:
    void titleset(QString a);
    int currow=-1;
};

#endif // ESTABLISHQUEST_H
