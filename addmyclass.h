#ifndef ADDMYCLASS_H
#define ADDMYCLASS_H

#include <QDialog>
#include <QString>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

namespace Ui {
class addmyclass;
}

class addmyclass : public QDialog
{
    Q_OBJECT

public:
    explicit addmyclass(QWidget *parent = nullptr);
    ~addmyclass();
    void refresh();//刷新界面


private slots:
    void on_buttonBox_accepted();//写入myclass.xlsx
    void on_finalcheckBox_checkStateChanged(const Qt::CheckState &arg1);//是否有期末考试


signals:
    void back();


private:
    Ui::addmyclass *ui;
};

#endif // ADDMYCLASS_H
