#ifndef DELETEMYCLASS_H
#define DELETEMYCLASS_H

#include <QDialog>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"


namespace Ui {
class deletemyclass;
}

class deletemyclass : public QDialog
{
    Q_OBJECT

public:
    explicit deletemyclass(QWidget *parent = nullptr);
    ~deletemyclass();
    void refresh();


private slots:
    void on_buttonBox_accepted();//删除课程


signals:
    void back();


private:
    Ui::deletemyclass *ui;
};

#endif // DELETEMYCLASS_H
