#include "innernote.h"
#include "ui_innernote.h"

innernote::innernote(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::innernote)
{
    ui->setupUi(this);
}


innernote::~innernote()
{
    delete ui;
}


void innernote::on_picturepushButton_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "选择图片", QDir::homePath(), "图片文件 (*.png *.jpg *.jpeg *.bmp *.gif)");
    if (imagePath.isEmpty()) {
        return;
    }
    QImage image(imagePath);
    if (image.isNull()) {
        QMessageBox::warning(this, "错误", "无法加载图片文件！");
        return;
    }
    //固定大小，待改进
    const int maxWidth = 400;
    const int maxHeight = 300;
    if (image.width() > maxWidth || image.height() > maxHeight) {
        image = image.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio);
    }
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.insertImage(image);
    cursor.insertText("\n");
}


void innernote::on_savepushButton_clicked()
{
    QXlsx::Document note("note.xlsx");
    QString name=note.read(1000,1000).toString()+".html";
    note.write(outerindex+2+300,innerindex+3+300,name);
    note.write(1000,1000,note.read(1000,1000).toInt()+1);
    note.save();
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法创建文件");
        return;
    }
    QTextStream out(&file);
    out << ui->textEdit->toHtml();
    file.close();
    //QInputDialog::getText(nullptr, "输入框标题","请输入文本:", QLineEdit::Normal, "默认文本", &ok)
    //QXlsx::Document note("note.xlsx");
    //note.write(outerindex+2+300,innerindex+3+300,name);
    //note.save();
    /*QString fileName =QString::number(outerindex)+"-"+QString::number(innerindex)+".html";
    if(fileName.isEmpty()) return;

    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->textEdit->toHtml();
        file.close();

        QFileInfo fi(fileName);
        QString imageDir = fi.absolutePath() + "/images";
        QDir().mkpath(imageDir);

        save_picture(ui->textEdit->document(), imageDir);
    }*/
}

void innernote::initialzation()
{
    QXlsx::Document note("note.xlsx");
    QString name=note.read(outerindex+2+300,innerindex+3+300).toString();
    QFile file(name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream in(&file);
    QString htmlContent = in.readAll();
    ui->textEdit->setHtml(htmlContent);
    file.close();
    /*QString fileName = QString::number(outerindex)+"-"+QString::number(innerindex)+".html";
    if(fileName.isEmpty()) return;

    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextDocument *doc = ui->textEdit->document();
        QFileInfo fi(fileName);

        // 设置基础路径以便加载相对路径资源
        doc->setBaseUrl(QUrl::fromLocalFile(fi.absolutePath() + "/"));

        ui->textEdit->setHtml(file.readAll());
        file.close();
    }*/
}

/*void innernote::save_picture(QTextDocument *doc, const QString &targetDir)
{
    // 确保目标目录存在
    QDir().mkpath(targetDir);

    for (QTextBlock block = doc->begin(); block != doc->end(); block = block.next()) {
        for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
            QTextFragment fragment = it.fragment();
            if (fragment.isValid() && fragment.charFormat().isImageFormat()) {
                QTextImageFormat format = fragment.charFormat().toImageFormat();
                QString imagePath = format.name();

                // 只处理本地文件系统路径（排除资源文件和Base64）
                if (QFile::exists(imagePath) &&
                    !imagePath.startsWith(":/") &&
                    !imagePath.startsWith("data:")) {

                    QFileInfo fi(imagePath);
                    QString newPath = targetDir + "/" + fi.fileName();
                    if (!QFile::exists(newPath)) {
                        QFile::copy(imagePath, newPath);
                    }
                }
            }
        }
    }
}*/

