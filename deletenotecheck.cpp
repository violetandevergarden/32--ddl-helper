#include "deletenotecheck.h"
#include "ui_deletenotecheck.h"

deletenotecheck::deletenotecheck(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::deletenotecheck)
{
    ui->setupUi(this);
}

deletenotecheck::~deletenotecheck()
{
    delete ui;
}

void deletenotecheck::on_buttonBox_accepted()
{
    emit back();
}

