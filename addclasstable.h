#ifndef ADDCLASSTABLE_H
#define ADDCLASSTABLE_H

#include <QDialog>
#include <QString>
#include <QDebug>

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

namespace Ui {
class addclasstable;
}

class addclasstable : public QDialog
{
    Q_OBJECT

public:
    explicit addclasstable(QWidget *parent = nullptr);
    ~addclasstable();
    void refresh();

    //零开始
    int row=0;
    int column=0;


private slots:
    void on_buttonBox_accepted();//填入myclass.xlsx课表内容


signals:
    void back();


private:
    Ui::addclasstable *ui;
};

#endif // ADDCLASSTABLE_H
