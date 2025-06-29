#include "innermarkdown.h"
#include "ui_innermarkdown.h"

innermarkdown::innermarkdown(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::innermarkdown)
{
    ui->setupUi(this);
}

innermarkdown::~innermarkdown()
{
    delete ui;
}

void innermarkdown::on_savepushButton_clicked()
{
    QXlsx::Document note("note.xlsx");
    QString name=note.read(1000,1000).toString()+".html";
    note.write(outerindex+2+300,innerindex+3+300,name);
    note.write(1000,1000,note.read(1000,1000).toInt()+1);
    note.save();
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法创建文件");
        return;
    }
    QTextStream out(&file);
    out << ui->markdownTextEdit->toPlainText();
    file.close();
}

void innermarkdown::initialization()
{
    QXlsx::Document note("note.xlsx");
    QString name=note.read(outerindex+2+300,innerindex+3+300).toString();
    QFile file(name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    QString markdown = in.readAll();
    ui->markdownTextEdit->setText(markdown);
    file.close();
}
