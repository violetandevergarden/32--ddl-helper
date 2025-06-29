#ifndef INNERNOTE_H
#define INNERNOTE_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QLayout>
#include <QInputDialog>
#include <QPlainTextEdit>
#include <QMessageBox>
#include "changetabname.h"

#include "qmarkdowntextedit.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

namespace Ui {
class innernote;
}

class innernote : public QWidget
{
    Q_OBJECT

public:
    explicit innernote(QWidget *parent = nullptr);
    ~innernote();
    void initialzation();//初始化
    //void save_picture(QTextDocument*, const QString &);//保存照片

    int outerindex;
    int innerindex;

private slots:
    void on_picturepushButton_clicked();//插入图片
    void on_savepushButton_clicked();//保存

private:
    Ui::innernote *ui;
};

#endif // INNERNOTE_H
