#include "changetabname.h"
#include "ui_changetabname.h"

changetabname::changetabname(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::changetabname)
{
    ui->setupUi(this);
}

changetabname::~changetabname()
{
    delete ui;
}

void changetabname::on_buttonBox_accepted()
{
    emit back(ui->tabnametextEdit->toPlainText());
}

void changetabname::refresh()
{
    ui->tabnametextEdit->setText("空空如也");
}

