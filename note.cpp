#include "note.h"
#include "ui_note.h"

note::note(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::note)
{
    ui->setupUi(this);
    //初始化
    QXlsx::Document note("note.xlsx");
    int tab_num=note.read(1,1).toInt();
    for(int i=0;i<tab_num;i++){
        innertab* tab=new innertab();
        tab->outerindex=i;
        tab->initialzation();
        ui->outertabWidget->addTab(tab,note.read(i+2,1).toString());
    }
    if(note.read(1000,1000).isNull()){
        note.write(1000,1000,0);
        qDebug()<<"有写入\n";
    }

    changetabname_ui=new changetabname();
    deletenotecheck_ui=new deletenotecheck();
    connect(changetabname_ui,&changetabname::back,this,&note::change_tab_name);
    connect(deletenotecheck_ui,&deletenotecheck::back,this,&note::delete_tab);
}

note::~note()
{
    delete ui;
}

void note::on_outertabWidget_tabBarDoubleClicked(int index)
{
    choosen_tab=index;
    changetabname_ui->refresh();
    changetabname_ui->show();
}

void note::change_tab_name(QString name)
{
    ui->outertabWidget->setTabText(choosen_tab,name);

    QXlsx::Document note("note.xlsx");
    note.write(choosen_tab+2,1,name);
    note.save();
}

void note::on_addoutertabpushButton_clicked()
{
    innertab *tab = new innertab();
    ui->outertabWidget->addTab(tab,"空空如也");
    tab->outerindex=ui->outertabWidget->count()-1;

    QXlsx::Document note("note.xlsx");
    note.write(ui->outertabWidget->count()+1,1,"空空如也");
    note.write(ui->outertabWidget->count()+1,2,0);
    note.write(1,1,ui->outertabWidget->count());
    note.save();
}

void note::on_deleteoutertabpushButton_clicked()
{
    deletenotecheck_ui->show();
}

void note::delete_tab()
{
    ui->outertabWidget->removeTab(ui->outertabWidget->currentIndex());
    //保证紧凑
    QXlsx::Document note("note.xlsx");
    for(int i=ui->outertabWidget->currentIndex()+3;i<=ui->outertabWidget->count()+2;i++){
        note.write(i-1,1,note.read(i,1));
        note.write(i-1,2,note.read(i,2));
        for(int j=3;j<3+note.read(i-1,2).toInt();j++){
            note.write(i-1,j,note.read(i,j));
            note.write(i-1+300,j+300,note.read(i+300,j+300));
            note.write(i-1+500,j+500,note.read(i+500,j+500));
        }
    }
    note.write(ui->outertabWidget->count()+2,1,"");
    for(int i=3;i<3+note.read(ui->outertabWidget->count()+2,2).toInt();i++){
        note.write(ui->outertabWidget->count()+2,i,"");
        note.write(ui->outertabWidget->count()+2+300,i+300,"");
        note.write(ui->outertabWidget->count()+2+500,i+500,"");
    }
    note.write(ui->outertabWidget->count()+2,2,"");
    note.write(ui->outertabWidget->count()+2+300,2+300,"");
    note.write(ui->outertabWidget->count()+2+500,2+500,"");
    note.write(1,1,ui->outertabWidget->count());
    note.save();
}

void note::auto_add_tab(QString name)
{
    for(int i=0;i<ui->outertabWidget->count();i++){
        if(ui->outertabWidget->tabText(i)==name){
            ui->outertabWidget->setCurrentIndex(i);
            return;
        }
    }
    innertab *tab = new innertab();
    ui->outertabWidget->addTab(tab,name);
    tab->outerindex=ui->outertabWidget->count()-1;

    QXlsx::Document note("note.xlsx");
    note.write(ui->outertabWidget->count()+1,1,name);
    note.write(ui->outertabWidget->count()+1,2,0);
    note.write(1,1,ui->outertabWidget->count());
    note.save();
}

