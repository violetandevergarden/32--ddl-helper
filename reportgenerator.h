#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QTextDocument>
#include <QTextOption>

class ReportGenerator : public QObject
{
    Q_OBJECT

public:
    explicit ReportGenerator(QObject *parent = nullptr);
    
    QPixmap generateReportImage(const QString& reportContent, int width = 800, int height = 1200);

    bool saveReportImage(const QPixmap& image, const QString& filePath);
    
    void setImageStyle(const QFont& titleFont, const QFont& contentFont, const QColor& backgroundColor);

private:
    QFont m_titleFont;
    QFont m_contentFont;
    QColor m_backgroundColor;
    
    void drawTitle(QPainter& painter, const QString& title, const QRect& rect);

    void drawContent(QPainter& painter, const QString& content, const QRect& rect);

    int calculateTextHeight(const QString& text, const QFont& font, int width);
    
    QString formatDateToChinese(const QDate& date);
};

#endif // REPORTGENERATOR_H