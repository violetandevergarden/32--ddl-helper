#ifndef MYCLASS_H
#define MYCLASS_H

#include <QMainWindow>
#include <QString>
#include <QListWidgetItem>
#include "addmyclass.h"
#include "deletemyclass.h"
#include "addclasstable.h"

#include "deletemyclass.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

namespace Ui {
class myclass;
}

class myclass : public QMainWindow
{
    Q_OBJECT

public:
    explicit myclass(QWidget *parent = nullptr);
    ~myclass();

/*
课程信息用myclass.xlsx储存
格式如下：
（1，1）：课程总数
（2，1）~（8，12）课表，只储存课程名
（9，1）~（？，1）课程信息：按列 1：名称  2：信息  3：期末月份  4：日  5：时  6：分
紧凑排列，无空行！
若课程的期末时间全为-1，代表没有期末
*/
    addmyclass* addmyclass_ui;
    deletemyclass* deletemyclass_ui;
    addclasstable* addclasstable_ui;

    //零开始
    int choosen_row = 0;
    int choosen_column = 0;


private slots:  
    void on_classtableWidget_cellClicked(int row, int column);//转入输入页面
    void on_addpushButton_clicked();//转入输入页面
    void on_deletepushButton_clicked();//转入删除页面
    void set_classtable();//写进课表ui
    void set_final_message();//写进期末ui
    void show_class();//写进课程列表
    void refresh();
    void on_classlistWidget_itemDoubleClicked(QListWidgetItem *item);//双击转入note页面，并自动添加//双击转入note页面，并自动添加


signals:
    void add(QString);


private:
    Ui::myclass *ui;
};

#endif // MYCLASS_H
