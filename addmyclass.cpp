#include "addmyclass.h"
#include "ui_addmyclass.h"

addmyclass::addmyclass(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addmyclass)
{
    ui->setupUi(this);

    ui->finalcheckBox->setCheckState(Qt::CheckState(2));
}

addmyclass::~addmyclass()
{
    delete ui;
}

void addmyclass::on_buttonBox_accepted()
{
    QXlsx::Document classes("myclass.xlsx");
    int class_num=0;
    if(!classes.read(1,1).isNull())class_num=classes.read(1,1).toInt();
    classes.write(class_num+9,1,ui->nametextEdit->toPlainText());
    classes.write(class_num+9,2,ui->classmsgtextEdit->toPlainText());
    classes.write(class_num+9,3,(ui->finalcheckBox->checkState()==2?ui->monthspinBox->value():-1));
    classes.write(class_num+9,4,(ui->finalcheckBox->checkState()==2?ui->dayspinBox->value():-1));
    classes.write(class_num+9,5,(ui->finalcheckBox->checkState()==2?ui->hourspinBox->value():-1));
    classes.write(class_num+9,6,(ui->finalcheckBox->checkState()==2?ui->mintuespinBox->value():-1));
    classes.write(1,1,class_num+1);
    classes.save();
    emit back();
}

void addmyclass::refresh()
{
    ui->nametextEdit->setText("");
    ui->classmsgtextEdit->setText("");
    ui->monthspinBox->setValue(0);
    ui->dayspinBox->setValue(0);
    ui->hourspinBox->setValue(0);
    ui->mintuespinBox->setValue(0);
}

void addmyclass::on_finalcheckBox_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1==0){
        ui->finallabel->hide();
        ui->monthlabel->hide();
        ui->daylabel->hide();
        ui->hourlabel->hide();
        ui->mintuelabel->hide();
        ui->monthspinBox->hide();
        ui->dayspinBox->hide();
        ui->hourspinBox->hide();
        ui->mintuespinBox->hide();
    }
    else if(arg1==2){
        ui->finallabel->show();
        ui->monthlabel->show();
        ui->daylabel->show();
        ui->hourlabel->show();
        ui->mintuelabel->show();
        ui->monthspinBox->show();
        ui->dayspinBox->show();
        ui->hourspinBox->show();
        ui->mintuespinBox->show();
    }
}

