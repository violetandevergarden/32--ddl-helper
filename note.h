#ifndef NOTE_H
#define NOTE_H

#include <QMainWindow>
#include "changetabname.h"
#include "innertab.h"
#include "deletenotecheck.h"


#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"


namespace Ui {
class note;
}

class note : public QMainWindow
{
    Q_OBJECT

/*
采用嵌套类，顺序为outerwidget->innertab->innernote
双击tab可以改名
"+"在末尾添加tab，"-"删除当前tab
sum_tab意为当前tabwidget的总tab数
innernote会记录来自于哪个tab，在保存时会用html记录内容，html名称储存在note.xlsx
outerindex和innerindex均从0开始
目前支持文字和图片，或markdown模式
*/
/*
tab的数量和名字存在note.xlsx中
（1,1）为outerwidget的tab数
（2,1）~（？，1）依次为outerwidget的各个tab名
（2,2）~（？，2）依次为innertab的tab数
（2,3）~（？，？）为各个innertab的tab名
（302,303）~（？，？）为保存的html名称
（502,503）~（？，？）为普通textedit和markdown，0为textedit，1为markdown
（1000,1000）为一个不减的数字，用于起名
紧凑格式，无空行
*/
public:
    explicit note(QWidget *parent = nullptr);
    ~note();
    void auto_add_tab(QString);//从class页面转来

    changetabname* changetabname_ui;
    deletenotecheck* deletenotecheck_ui;
    int choosen_tab=0;

private slots:
    void on_outertabWidget_tabBarDoubleClicked(int index);
    void on_addoutertabpushButton_clicked();
    void on_deleteoutertabpushButton_clicked();
    void change_tab_name(QString);
    void delete_tab();

private:
    Ui::note *ui;
};

#endif // NOTE_H
