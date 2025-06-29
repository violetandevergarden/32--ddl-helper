#include "deletemyclass.h"
#include "ui_deletemyclass.h"

deletemyclass::deletemyclass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::deletemyclass)
{
    ui->setupUi(this);
}

deletemyclass::~deletemyclass()
{
    delete ui;
}

void deletemyclass::refresh()
{
    QXlsx::Document classes("myclass.xlsx");
    int class_num=classes.read(1,1).toInt();
    ui->classcomboBox->clear();
    for(int i=9;i<class_num+9;i++){
        ui->classcomboBox->addItem(classes.read(i,1).toString());
    }
    if(class_num==0)ui->classcomboBox->addItem("没课还想删？");
}

void deletemyclass::on_buttonBox_accepted()
{
    QXlsx::Document classes("myclass.xlsx");
    int class_num=classes.read(1,1).toInt();
    //需要保证结构紧凑
    int index=ui->classcomboBox->currentIndex()+9;
    for(int i=index+1;i<class_num+9;i++){
        for(int j=1;j<=6;j++){
            classes.write(i-1,j,classes.read(i,j));
        }
    }
    for(int i=1;i<=6;i++){
        classes.write(class_num+8,i,"");
    }
    classes.write(1,1,class_num-1);
    classes.save();
    emit back();
}
