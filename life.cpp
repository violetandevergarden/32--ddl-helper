#include "life.h"
#include "ui_life.h"

life::life(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::life)
{
    ui->setupUi(this);
}

life::~life()
{
    delete ui;
}
