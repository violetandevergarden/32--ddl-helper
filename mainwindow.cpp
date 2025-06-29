#include "mainwindow.h"
#include "ui_establishquest.h"
#include "ui_mainwindow.h"
#include"establishquest.h"
#include<QCloseEvent>
#include<QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    about_ui = new about();
    task_ui=new task();
    class_ui=new myclass();
    QXlsx::Document doc("myquest.xlsx");
    QXlsx::Document cla("myclass.xlsx");
    note_ui=new note();
    life_ui=new life();
    connect(class_ui,&myclass::add,this,&MainWindow::receive_add);
    ui->arrangetableWidget->setColumnWidth(0,267);
    ui->arrangetableWidget->setColumnWidth(1,166);
    ui->arrangetableWidget->setColumnWidth(2,105);
    ui->classtableWidget->setColumnWidth(0,130);
    ui->classtableWidget->setColumnWidth(1,127);
    QDate currentDate = QDate::currentDate();
    int dd = currentDate.dayOfWeek()+1;
    for(int i=1;i<13;i++){
        ui->classtableWidget->setRowHeight(i-1, 43);
        if(!cla.read(dd,i).isNull()){
            QString aa=cla.read(dd,i).toString();
            QString bb="";
            for(int j=9;j<30;j++){
                if(cla.read(j,1).toString()==aa){
                    bb=cla.read(j,2).toString();
                    qDebug()<<bb<<j;
                }
            }
            upclass(aa,bb,i);
        }
    }
    int row=0,col=0,num=0;
    for(int i=1;i<20;i++){
        if(doc.read(i,1).isNull()){
            num=i;
            break;
        }
    }

    for(int i=1;i<num;i++){
        QString aa=doc.read(i,1).toString();
        QString bb=doc.read(i,2).toString();
        QString cc=doc.read(i,3).toString();
        QString dd=doc.read(i,4).toString();
        uptable(aa,bb,cc,dd,-1);
    }

    weekreport_ui=new weekreport();
    m_apiClient = new ApiClient(this);
    m_dataCollector = new DataCollector(this);
    m_reportGenerator = new ReportGenerator(this);
    m_apiClient->setApiConfig("sk-uAV87q6B2l189zsnJI5YlzdObUVrLa9cUaepHrsDwQwSbSFb", "https://api.nuwaapi.com/v1");
    connect(m_apiClient, &ApiClient::reportGenerated, this, &MainWindow::onReportGenerated);
    connect(m_apiClient, &ApiClient::errorOccurred, this, &MainWindow::onApiError);
    connect(ui->weekreportpushButton, &QPushButton::clicked, this, &MainWindow::onGenerateWeeklyReport);
}

MainWindow::~MainWindow()
{
    delete ui;
}
class Due{
public:
    QString aa,bb,cc,dd;
    Due(QString a,QString b,QString c,QString d):aa(a),bb(b),cc(c),dd(d){

    }
};
Due *thing[10];

int i=0;
void MainWindow::on_aboutpushButton_clicked()
{
    about_ui->show();
}


void MainWindow::on_taskpushButton_clicked()
{
    task_ui->show();
}


void MainWindow::on_classpushButton_clicked()
{
    class_ui->show();
}
void MainWindow::on_lifepushButton_clicked()
{
    life_ui->show();
}

void MainWindow::on_notepushButton_clicked()
{

    note_ui->show();
}
void MainWindow::on_weekreportpushButton_clicked()
{
    weekreport_ui->show();
}
void MainWindow::upclass(QString &a,QString &b,int u){

    QTableWidgetItem *newItem = new QTableWidgetItem(a);
    ui->classtableWidget->setItem(u-1, 0, newItem);
    ui->classtableWidget->item(u-1, 0)->setTextAlignment(Qt::AlignCenter);
    QTableWidgetItem *newItem1 = new QTableWidgetItem(b);
     ui->classtableWidget->setItem(u-1, 1, newItem1);
    ui->classtableWidget->item(u-1, 1)->setTextAlignment(Qt::AlignCenter);
}
void MainWindow::uptable(QString &a,QString &b,QString &c,QString &d,int u){
QXlsx::Document doc("myquest.xlsx");
    QDate currentDate = QDate::currentDate();
    QString ss=currentDate.toString("yyyy-MM-dd");
    if(u==-1){

    ui->arrangetableWidget->insertRow(ui->arrangetableWidget->rowCount());
         int row=ui->arrangetableWidget->rowCount()-1;
    ui->arrangetableWidget->setRowHeight(row, 45);
    doc.write(row+1,1,a);
    doc.write(row+1,2,b);
    doc.write(row+1,3,c);
    doc.write(row+1,4,d);

    QTableWidgetItem *newItem = new QTableWidgetItem(a);
    ui->arrangetableWidget->setItem(row, 0, newItem);
    ui->arrangetableWidget->item(row, 0)->setTextAlignment(Qt::AlignCenter);


    QTableWidgetItem *newItem2 = new QTableWidgetItem(b);
    ui->arrangetableWidget->setItem(row, 1, newItem2);
    ui->arrangetableWidget->item(row, 1)->setTextAlignment(Qt::AlignCenter);

    QTableWidgetItem *newItem3 = new QTableWidgetItem(c);

    if(ss>b){newItem3 = new QTableWidgetItem("已完成");

    }
    ui->arrangetableWidget->setItem(row, 2, newItem3);
    ui->arrangetableWidget->item(row, 2)->setTextAlignment(Qt::AlignCenter);
    doc.save();
    if(c=="紧急"){
        QColor red(255,157,151);
        QTableWidgetItem* item = ui->arrangetableWidget->item(row, 0); // 获取单元格项
        item->setBackground(red); // 设置背景色为红色
        item = ui->arrangetableWidget->item(row, 1); // 获取单元格项
        item->setBackground(red); // 设置背景色为红色
        item = ui->arrangetableWidget->item(row, 2); // 获取单元格项
        item->setBackground(red); // 设置背景色为红色

    }
    else if(c=="一般"){
        QColor yellow(255,227,132);
        QTableWidgetItem* item = ui->arrangetableWidget->item(ui->arrangetableWidget->rowCount()-1, 0); // 获取单元格项
        item->setBackground(yellow); // 设置背景色为黄色
        item = ui->arrangetableWidget->item(ui->arrangetableWidget->rowCount()-1, 1); // 获取单元格项
        item->setBackground(yellow); // 设置背景色为黄色
        item = ui->arrangetableWidget->item(ui->arrangetableWidget->rowCount()-1, 2); // 获取单元格项
        item->setBackground(yellow); // 设置背景色为黄色
    }
    else{
        QColor green(224,246,216);
        QTableWidgetItem* item = ui->arrangetableWidget->item(ui->arrangetableWidget->rowCount()-1, 0); // 获取单元格项
        item->setBackground(green); // 设置背景色为绿色
        item = ui->arrangetableWidget->item(ui->arrangetableWidget->rowCount()-1, 1); // 获取单元格项
        item->setBackground(green); // 设置背景色为绿色
        item = ui->arrangetableWidget->item(ui->arrangetableWidget->rowCount()-1, 2); // 获取单元格项
        item->setBackground(green); // 设置背景色为绿色
    }
    }
    else{

        doc.write(u+1,1,a);
        doc.write(u+1,2,b);
        doc.write(u+1,3,c);
        doc.write(u+1,4,d);
        ui->arrangetableWidget->setRowHeight(u, 45);
        QTableWidgetItem *newItem = new QTableWidgetItem(a);
        ui->arrangetableWidget->setItem(u, 0, newItem);
        ui->arrangetableWidget->item(u, 0)->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(b);
        ui->arrangetableWidget->setItem(u, 1, newItem2);
        ui->arrangetableWidget->item(u, 1)->setTextAlignment(Qt::AlignCenter);
        QTableWidgetItem *newItem3 = new QTableWidgetItem(c);
        if(ss>b)newItem3 = new QTableWidgetItem("已完成");
        ui->arrangetableWidget->setItem(u, 2, newItem3);
        ui->arrangetableWidget->item(u, 2)->setTextAlignment(Qt::AlignCenter);
        doc.save();
        if(c=="紧急"){
            QColor red(255,157,151);
            QTableWidgetItem* item = ui->arrangetableWidget->item(u, 0); // 获取单元格项
            item->setBackground(red); // 设置背景色为红色
            item = ui->arrangetableWidget->item(u, 1); // 获取单元格项
            item->setBackground(red); // 设置背景色为红色
            item = ui->arrangetableWidget->item(u, 2); // 获取单元格项
            item->setBackground(red); // 设置背景色为红色

        }
        else if(c=="一般"){
            QColor yello(255,227,132);
            QTableWidgetItem* item = ui->arrangetableWidget->item(u, 0); // 获取单元格项
            item->setBackground(yello); // 设置背景色为黄色
            item = ui->arrangetableWidget->item(u, 1); // 获取单元格项
            item->setBackground(yello); // 设置背景色为黄色
            item = ui->arrangetableWidget->item(u, 2); // 获取单元格项
            item->setBackground(yello); // 设置背景色为黄色
        }
        else{
            QColor green(224,246,216);
            QTableWidgetItem* item = ui->arrangetableWidget->item(u, 0); // 获取单元格项
            item->setBackground(green); // 设置背景色为绿色
            item = ui->arrangetableWidget->item(u, 1); // 获取单元格项
            item->setBackground(green); // 设置背景色为绿色
            item = ui->arrangetableWidget->item(u, 2); // 获取单元格项
            item->setBackground(green); // 设置背景色为绿色
        }
    }

}

void MainWindow::on_addButton_clicked()
{
    ee_ui=new establishquest();
    connect(ee_ui,&establishquest::updatetable,this,&MainWindow::uptable);
    ee_ui->show();
}


void MainWindow::on_adjustbutton_clicked()
{QXlsx::Document doc("myquest.xlsx");
    ee_ui=new establishquest();
    ee_ui->currow=currentrow;
    connect(ee_ui,&establishquest::updatetable,this,&MainWindow::uptable);
    ee_ui->ui->titletext->setText(doc.read(currentrow+1,1).toString());
    ee_ui->ui->contenttext->setText(doc.read(currentrow+1,4).toString());
    ee_ui->show();
}

void MainWindow::Delete(int index){
    if(index==-1){}
    else{
    QXlsx::Document doc("myquest.xlsx");
    int num=0;
    for(int i=1;i<20;i++){
        if(doc.read(i,1).isNull()){
            num=i;
            break;
        }
    }
    qDebug()<<currentrow;
    for(int j=index+1;j<num-1;j++){
        doc.write(j,1,doc.read(j+1,1).toString());
        doc.write(j,2,doc.read(j+1,2).toString());
        doc.write(j,3,doc.read(j+1,3).toString());
        doc.write(j,4,doc.read(j+1,4).toString());

    }
    QVariant q=QVariant();
    doc.write(num-1,1,q);
    doc.write(num-1,2,q);
    doc.write(num-1,3,q);
    doc.write(num-1,4,q);
    ui->arrangetableWidget->setRowCount(0);
    for(int i=1;i<num-1;i++){
        QString aa=doc.read(i,1).toString();
        QString bb=doc.read(i,2).toString();
        QString cc=doc.read(i,3).toString();
        QString dd=doc.read(i,4).toString();
        uptable(aa,bb,cc,dd,-1);}
      doc.save();
    }

}
void MainWindow::on_deletebutton_clicked()
{
    Delete(currentrow);
    currentrow=-1;
}

void MainWindow::on_arrangetableWidget_cellClicked(int row, int column)
{
    currentrow=row;

}
void MainWindow::closeEvent(QCloseEvent *event)
{

    onMainWindowClose();


}
void MainWindow::onMainWindowClose(){

}
void MainWindow::receive_add(QString name)
{
    note_ui->show();
    note_ui->auto_add_tab(name);
}
void MainWindow::onGenerateWeeklyReport()
{
    m_progressDialog = new QProgressDialog("正在生成周报，请稍候...", "取消", 0, 0, this);
    m_progressDialog->setWindowModality(Qt::WindowModal);
    m_progressDialog->show();
    QString weeklyData = m_dataCollector->collectWeeklyData();
    
    if (weeklyData.isEmpty()) {
        m_progressDialog->hide();
        QMessageBox::information(this, "提示", "本周暂无任务数据");
        return;
    }

    m_apiClient->generateWeeklyReport(weeklyData);
}


void MainWindow::onReportGenerated(const QString& reportContent)
{
    m_progressDialog->hide();
    QPixmap reportImage = m_reportGenerator->generateReportImage(reportContent);
    QString fileName = QString("周报_%1.png").arg(QDate::currentDate().toString("yyyy-MM-dd"));
    QString filePath = QFileDialog::getSaveFileName(this, "保存周报图片", fileName, "PNG文件 (*.png)");
    
    if (!filePath.isEmpty()) {
        if (m_reportGenerator->saveReportImage(reportImage, filePath)) {
            QMessageBox::information(this, "成功", QString("周报已保存到：%1").arg(filePath));
        } else {
            QMessageBox::warning(this, "错误", "保存周报图片失败");
        }
    }
}

void MainWindow::onApiError(const QString& error)
{
    m_progressDialog->hide();
    QMessageBox::warning(this, "生成周报失败", QString("错误信息：%1").arg(error));
}



