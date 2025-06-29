#include "weekreport.h"
#include "ui_weekreport.h"

weekreport::weekreport(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::weekreport)
{
    ui->setupUi(this);
}

weekreport::~weekreport()
{
    delete ui;
}
