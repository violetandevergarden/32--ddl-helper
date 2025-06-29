#ifndef INNERTAB_H
#define INNERTAB_H

#include <QWidget>
#include "innernote.h"
#include "innermarkdown.h"
#include "changetabname.h"
#include "deletenotecheck.h"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

namespace Ui {
class innertab;
}

class innertab : public QWidget
{
    Q_OBJECT

public:
    explicit innertab(QWidget *parent = nullptr);
    ~innertab();
    void add_tab();
    void delete_check();
    void initialzation();

    changetabname* changetabname_ui;
    deletenotecheck* deletenotecheck_ui;
    int choosen_tab=0;
    int outerindex;

private slots:
    void on_tabWidget_tabBarDoubleClicked(int index);
    void on_addpushButton_clicked();
    void on_deletepushButton_clicked();
    void change_tab_name(QString);
    void delete_tab();


    void on_texteditcheckBox_stateChanged(int arg1);

    void on_markdowncheckBox_stateChanged(int arg1);

private:
    Ui::innertab *ui;
};

#endif // INNERTAB_H
