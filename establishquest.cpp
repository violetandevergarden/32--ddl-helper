#include "establishquest.h"
#include "ui_establishquest.h"
#include <cstdlib>
#include <ctime>
#include"mainwindow.h"
establishquest::establishquest(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::establishquest)
{
    ui->setupUi(this);
    ui->emerbutton->setCheckable(true);
    ui->normalbutton->setCheckable(true);
    ui->notemerbutton->setCheckable(true);
    ui->finishedpushButton->setCheckable(true);
    srand(time(0));
    int rannum=rand();
    qDebug()<<rannum;
    if(rannum%5==0){
        ui->label->setStyleSheet("border-image: url(:/icon/qing.png);");
            ui->label_2->setStyleSheet("border-image: url(:/icon/tie.png);");
    }
    else if(rannum%5==1){
        ui->label->setStyleSheet("border-image: url(:/icon/san.png);");
        ui->label_2->setStyleSheet("border-image: url(:/icon/wan.png);");
    }
    else if(rannum%5==2){
        ui->label->setStyleSheet("border-image: url(:/icon/han.png);");
        ui->label_2->setStyleSheet("border-image: url(:/icon/yu.png);");
    }
    else if(rannum%5==3){
        ui->label->setStyleSheet("border-image: url(:/icon/mian.png);");
        ui->label_2->setStyleSheet("border-image: url(:/icon/nan.png);");
    }
    else if(rannum%5==4){
        ui->label->setStyleSheet("border-image: url(:/icon/geng.png);");
        ui->label_2->setStyleSheet("border-image: url(:/icon/du.png);");
    }
}

establishquest::~establishquest()
{
    delete ui;
}


int ii=0;
void establishquest::on_buttonBox_accepted()
{
    title=ui->titletext->toPlainText();
    content=ui->contenttext->toPlainText();

    if(emer=="n"){

    }
    else{
        emit updatetable(title,dateString,emer,content,currow);


    }
}


void establishquest::on_calendarWidget_clicked(const QDate &date)
{
    dateString = date.toString("yyyy-MM-dd");
}


void establishquest::on_emerbutton_clicked()
{
    ui->normalbutton->setChecked(false);
    ui->notemerbutton->setChecked(false);
    ui->finishedpushButton->setChecked(false);
    emer="紧急";

}


void establishquest::on_normalbutton_clicked()
{
    ui->emerbutton->setChecked(false);
    ui->notemerbutton->setChecked(false);
    ui->finishedpushButton->setChecked(false);
    emer="一般";


}


void establishquest::on_notemerbutton_clicked()
{
    ui->emerbutton->setChecked(false);
    ui->normalbutton->setChecked(false);
    ui->finishedpushButton->setChecked(false);
    emer="不紧急";
}
void establishquest::titleset(QString a){
    ui->titletext->setText(a);
}

void establishquest::on_finishedpushButton_clicked()
{
    ui->emerbutton->setChecked(false);
    ui->normalbutton->setChecked(false);
    ui->notemerbutton->setChecked(false);
    emer="已完成";
}

