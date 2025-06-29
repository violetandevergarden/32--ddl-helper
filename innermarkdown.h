#ifndef INNERMARKDOWN_H
#define INNERMARKDOWN_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>

#include "qmarkdowntextedit.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

namespace Ui {
class innermarkdown;
}

class innermarkdown : public QMainWindow
{
    Q_OBJECT

public:
    explicit innermarkdown(QWidget *parent = nullptr);
    ~innermarkdown();
    void initialization();

    int outerindex;
    int innerindex;

private slots:
    void on_savepushButton_clicked();

private:
    Ui::innermarkdown *ui;
};

#endif // INNERMARKDOWN_H
