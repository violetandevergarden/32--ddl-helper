#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include "about.h"
#include "task.h"
#include "myclass.h"
#include "note.h"
#include "life.h"
#include "weekreport.h"
#include"establishquest.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include "apiclient.h"
#include "datacollector.h"
#include "reportgenerator.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    about* about_ui=NULL;
    task* task_ui=NULL;
    myclass* class_ui=NULL;
    note* note_ui=NULL;
    life* life_ui=NULL;
    weekreport* weekreport_ui=NULL;
    establishquest* ee_ui=NULL;

    int currentrow=-1;


private slots:
    void on_aboutpushButton_clicked();
    void uptable(QString &a,QString &b,QString& c,QString &d,int u);
    void on_taskpushButton_clicked();
    void upclass(QString &a,QString &b,int u);
    void on_classpushButton_clicked();

    void on_notepushButton_clicked();

    void on_lifepushButton_clicked();

    void on_weekreportpushButton_clicked();

    void Delete(int i);

    void on_addButton_clicked();

    void on_adjustbutton_clicked();

    void on_deletebutton_clicked();
    void onGenerateWeeklyReport();
    void onReportGenerated(const QString& reportContent);
    void onApiError(const QString& error);
    void receive_add(QString);

    void on_arrangetableWidget_cellClicked(int row, int column);
protected:
    void closeEvent(QCloseEvent *event) override;
    void onMainWindowClose();
private:
    Ui::MainWindow *ui;
    ApiClient* m_apiClient;
    DataCollector* m_dataCollector;
    ReportGenerator* m_reportGenerator;
    QProgressDialog* m_progressDialog;
};
#endif // MAINWINDOW_H
