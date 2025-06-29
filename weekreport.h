#ifndef WEEKREPORT_H
#define WEEKREPORT_H

#include <QMainWindow>

namespace Ui {
class weekreport;
}

class weekreport : public QMainWindow
{
    Q_OBJECT

public:
    explicit weekreport(QWidget *parent = nullptr);
    ~weekreport();

private:
    Ui::weekreport *ui;
};

#endif // WEEKREPORT_H
