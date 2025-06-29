#include "myclass.h"
#include "ui_myclass.h"

myclass::myclass(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::myclass)
{
    ui->setupUi(this);


    //初始化
    QXlsx::Document classes("myclass.xlsx");
    for(int i=2;i<=8;i++){
        for(int j=1;j<=12;j++){
            QString name="";
            if(!classes.read(i,j).isNull())name=classes.read(i,j).toString();
            QTableWidgetItem* item = new QTableWidgetItem(name);
            ui->classtableWidget->setItem(i-2,j-1,item);
        }
    }
    int class_num=classes.read(1,1).toInt();
    for(int i=9;i<class_num+9;i++){
        QListWidgetItem *item1 = new QListWidgetItem(classes.read(i,1).toString());
        ui->classlistWidget->addItem(item1);
        if(classes.read(i,3)==-1)continue;
        QString final=classes.read(i,1).toString()+"        "+
                        classes.read(i,3).toString()+"月"+
                        classes.read(i,4).toString()+"日"+
                        classes.read(i,5).toString()+"点"+
                        classes.read(i,6).toString()+"分";
        QListWidgetItem *item2 = new QListWidgetItem(final);
        ui->finallistWidget->addItem(item2);
    }

    addmyclass_ui=new addmyclass();
    deletemyclass_ui=new deletemyclass();
    addclasstable_ui=new addclasstable();
    connect(addclasstable_ui,&addclasstable::back,this,&myclass::set_classtable);
    connect(addmyclass_ui,&addmyclass::back,this,&myclass::set_final_message);
    connect(addmyclass_ui,&addmyclass::back,this,&myclass::show_class);
    connect(deletemyclass_ui,&deletemyclass::back,this,&myclass::refresh);
}

myclass::~myclass()
{
    delete ui;
}

void myclass::on_classtableWidget_cellClicked(int row, int column)
{
    choosen_row=row;
    choosen_column=column;
    addclasstable_ui->row=row;
    addclasstable_ui->column=column;
    addclasstable_ui->refresh();
    addclasstable_ui->show();
}

void myclass::on_addpushButton_clicked()
{
    addmyclass_ui->refresh();
    addmyclass_ui->show();
}

void myclass::on_deletepushButton_clicked()
{
    deletemyclass_ui->refresh();
    deletemyclass_ui->show();
}

void myclass::set_classtable()
{
    QXlsx::Document classes("myclass.xlsx");
    QTableWidgetItem* item = new QTableWidgetItem(classes.read(choosen_row+2,choosen_column+1).toString());
    ui->classtableWidget->setItem(choosen_row,choosen_column,item);
}

void myclass::set_final_message()
{
    QXlsx::Document classes("myclass.xlsx");
    int class_num=classes.read(1,1).toInt();
    if(classes.read(class_num+8,3)!=-1){
        QString final=classes.read(class_num+8,1).toString()+"        "+
                classes.read(class_num+8,3).toString()+"月"+
                classes.read(class_num+8,4).toString()+"日"+
                classes.read(class_num+8,5).toString()+"点"+
                classes.read(class_num+8,6).toString()+"分";
        QListWidgetItem *item = new QListWidgetItem(final);
        ui->finallistWidget->addItem(item);
    }
}

void myclass::show_class()
{
    QXlsx::Document classes("myclass.xlsx");
    int class_num=classes.read(1,1).toInt();
    QString name=classes.read(class_num+8,1).toString();
    ui->classlistWidget->addItem(name);
}

void myclass::refresh()
{
    ui->classlistWidget->clear();
    ui->finallistWidget->clear();
    QXlsx::Document classes("myclass.xlsx");
    int class_num=classes.read(1,1).toInt();
    for(int i=9;i<class_num+9;i++){
        QListWidgetItem *item1 = new QListWidgetItem(classes.read(i,1).toString());
        ui->classlistWidget->addItem(item1);
        if(classes.read(i,3)==-1)continue;
        QString final=classes.read(i,1).toString()+"        "+
                        classes.read(i,3).toString()+"月"+
                        classes.read(i,4).toString()+"日"+
                        classes.read(i,5).toString()+"点"+
                        classes.read(i,6).toString()+"分";
        QListWidgetItem *item2 = new QListWidgetItem(final);
        ui->finallistWidget->addItem(item2);
    }
}
void myclass::on_classlistWidget_itemDoubleClicked(QListWidgetItem *item)
{
    qDebug()<<"kk";
    emit add(item->text());
}

