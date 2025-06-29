#include "addclasstable.h"
#include "ui_addclasstable.h"

addclasstable::addclasstable(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addclasstable)
{
    ui->setupUi(this);

}

addclasstable::~addclasstable()
{
    delete ui;
}

void addclasstable::refresh()
{
    QXlsx::Document classes("myclass.xlsx");
    int class_num=classes.read(1,1).toInt();
    ui->classcomboBox->clear();
    ui->classcomboBox->addItem("半日闲");
    for(int i=9;i<class_num+9;i++){
        ui->classcomboBox->addItem(classes.read(i,1).toString());
    }
}

void addclasstable::on_buttonBox_accepted()
{
    QXlsx::Document classes("myclass.xlsx");
    QString name=ui->classcomboBox->currentText();
    qDebug()<<name;
    classes.write(row+2,column+1,name);
    classes.save();
    emit back();
}

