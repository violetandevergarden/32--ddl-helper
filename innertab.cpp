#include "innertab.h"
#include "ui_innertab.h"

innertab::innertab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::innertab)
{
    ui->setupUi(this);
ui->tabWidget->setTabPosition(QTabWidget::TabPosition::South);
    changetabname_ui=new changetabname();
    deletenotecheck_ui=new deletenotecheck();
    connect(changetabname_ui,&changetabname::back,this,&innertab::change_tab_name);
    connect(deletenotecheck_ui,&deletenotecheck::back,this,&innertab::delete_tab);
}

innertab::~innertab()
{
    delete ui;
}

void innertab::change_tab_name(QString name)
{
    ui->tabWidget->setTabText(choosen_tab,name);

    QXlsx::Document note("note.xlsx");
    note.write(outerindex+2,choosen_tab+3,name);
    note.save();
}

void innertab::delete_tab()
{
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
    //保证紧凑格式
    QXlsx::Document note("note.xlsx");
    for(int i=ui->tabWidget->currentIndex()+4;i<=ui->tabWidget->count()+3;i++){
        note.write(outerindex+2,i-1,note.read(outerindex+2,i));
        note.write(outerindex+2+300,i-1-300,note.read(outerindex+2+300,i+300));
        note.write(outerindex+2+500,i-1+500,note.read(outerindex+2+500,i+500));
    }
    note.write(outerindex+2,ui->tabWidget->count()+3,"");
    note.write(outerindex+2+300,ui->tabWidget->count()+3+300,"");
    note.write(outerindex+2+500,ui->tabWidget->count()+3+500,"");
    note.write(outerindex+2,2,ui->tabWidget->count());
    note.save();
}

void innertab::on_tabWidget_tabBarDoubleClicked(int index)
{
    choosen_tab=index;
    changetabname_ui->show();
}

void innertab::on_addpushButton_clicked()
{
    int flag=0;
    if(ui->texteditcheckBox->checkState()==2){
        innernote* innernote_ui=new innernote();
        ui->tabWidget->addTab(innernote_ui,"空空如也");
        innernote_ui->outerindex=outerindex;
        innernote_ui->innerindex=ui->tabWidget->count()-1;
    }
    else if(ui->markdowncheckBox->checkState()==2){
        innermarkdown* innermarkdown_ui=new innermarkdown();
        ui->tabWidget->addTab(innermarkdown_ui,"空空如也");
        innermarkdown_ui->outerindex=outerindex;
        innermarkdown_ui->innerindex=ui->tabWidget->count()-1;
        flag=1;
    }
    else return;

    QXlsx::Document note("note.xlsx");
    note.write(outerindex+2,ui->tabWidget->count()+2,"空空如也");
    note.write(outerindex+2+500,ui->tabWidget->count()+2+500,flag);
    note.write(outerindex+2,2,ui->tabWidget->count());
    note.save();
}

void innertab::on_deletepushButton_clicked()
{
    deletenotecheck_ui->show();
}

void innertab::initialzation()
{
    QXlsx::Document note("note.xlsx");
    int tab_num=note.read(outerindex+2,2).toInt();
    for(int i=3;i<3+tab_num;i++){
        if(note.read(outerindex+2+500,i+500).toInt()==0){
            innernote* innernote_ui=new innernote();
            innernote_ui->outerindex=outerindex;
            innernote_ui->innerindex=i-3;
            innernote_ui->initialzation();
            ui->tabWidget->addTab(innernote_ui,note.read(outerindex+2,i).toString());
        }
        else{
            innermarkdown* innermarkdown_ui=new innermarkdown();
            innermarkdown_ui->outerindex=outerindex;
            innermarkdown_ui->innerindex=i-3;
            innermarkdown_ui->initialization();
            ui->tabWidget->addTab(innermarkdown_ui,note.read(outerindex+2,i).toString());
        }
    }
    ui->texteditcheckBox->setCheckState(Qt::Checked);
}


void innertab::on_texteditcheckBox_stateChanged(int arg1)
{
    if(arg1==2){
        ui->markdowncheckBox->setCheckState(Qt::Unchecked);
    }
}

void innertab::on_markdowncheckBox_stateChanged(int arg1)
{
    if(arg1==2){
        ui->texteditcheckBox->setCheckState(Qt::Unchecked);
    }
}

