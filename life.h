#ifndef LIFE_H
#define LIFE_H

#include <QMainWindow>

namespace Ui {
class life;
}

class life : public QMainWindow
{
    Q_OBJECT

public:
    explicit life(QWidget *parent = nullptr);
    ~life();

private:
    Ui::life *ui;
};

#endif // LIFE_H
