#include "reportgenerator.h"
#include <QFontMetrics>
#include <QTextDocument>
#include <QDate>
#include <QDir>
#include <QStandardPaths>

ReportGenerator::ReportGenerator(QObject *parent)
    : QObject(parent)
{
    m_titleFont = QFont("Microsoft YaHei", 18, QFont::Bold);
    m_contentFont = QFont("Microsoft YaHei", 12);
    m_backgroundColor = QColor(248, 249, 250);
}

void ReportGenerator::setImageStyle(const QFont& titleFont, const QFont& contentFont, const QColor& backgroundColor)
{
    m_titleFont = titleFont;
    m_contentFont = contentFont;
    m_backgroundColor = backgroundColor;
}

QPixmap ReportGenerator::generateReportImage(const QString& reportContent, int width, int height)
{
    QPixmap pixmap(width, height);
    pixmap.fill(m_backgroundColor);
    
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    
    int margin = 40;
    int titleHeight = 80;
    
    QRect titleRect(margin, margin, width - 2 * margin, titleHeight);
    
    QDate currentDate = QDate::currentDate();
    QDate weekStart = currentDate.addDays(-currentDate.dayOfWeek() + 1);
    QDate weekEnd = weekStart.addDays(6);
    
    QString title = QString("工作周报 - %1 至 %2")
                   .arg(weekStart.toString("yyyy年MM月dd日"))
                   .arg(weekEnd.toString("yyyy年MM月dd日"));
    
    drawTitle(painter, title, titleRect);
    
    painter.setPen(QPen(QColor(200, 200, 200), 2));
    painter.drawLine(margin, margin + titleHeight + 20, width - margin, margin + titleHeight + 20);
    
    QRect contentRect(margin, margin + titleHeight + 40, 
                     width - 2 * margin, height - margin - titleHeight - 80);
    drawContent(painter, reportContent, contentRect);
    
    painter.setFont(QFont("Microsoft YaHei", 10));
    painter.setPen(QColor(120, 120, 120));
    QString footerText = QString("生成时间：%1").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    painter.drawText(QRect(margin, height - 60, width - 2 * margin, 40), 
                    Qt::AlignRight | Qt::AlignVCenter, footerText);
    
    return pixmap;
}

void ReportGenerator::drawTitle(QPainter& painter, const QString& title, const QRect& rect)
{
    painter.setFont(m_titleFont);
    painter.setPen(QColor(51, 51, 51));

    painter.fillRect(rect, QColor(255, 255, 255));
    painter.setPen(QPen(QColor(230, 230, 230), 1));
    painter.drawRect(rect);

    painter.setPen(QColor(51, 51, 51));
    painter.drawText(rect, Qt::AlignCenter, title);
}

void ReportGenerator::drawContent(QPainter& painter, const QString& content, const QRect& rect)
{
    painter.setFont(m_contentFont);
    painter.setPen(QColor(68, 68, 68));

    painter.fillRect(rect, QColor(255, 255, 255));
    painter.setPen(QPen(QColor(230, 230, 230), 1));
    painter.drawRect(rect);

    QTextDocument doc;
    doc.setDefaultFont(m_contentFont);
    doc.setTextWidth(rect.width() - 40); 

    QStringList lines = content.split('\n');
    QString formattedContent;
    
    for (const QString& line : lines) {
        if (line.startsWith("【") && line.endsWith("】")) {
            formattedContent += QString("<h3 style='color: #2c5aa0; margin-top: 15px; margin-bottom: 8px;'>%1</h3>").arg(line);
        } else if (line.startsWith("- ")) {
            formattedContent += QString("<p style='margin: 5px 0; padding-left: 20px;'>• %1</p>").arg(line.mid(2));
        } else if (line.contains("：") && !line.startsWith("-")) {
            formattedContent += QString("<p style='margin: 8px 0; font-weight: bold; color: #333;'>%1</p>").arg(line);
        } else {
            formattedContent += QString("<p style='margin: 5px 0;'>%1</p>").arg(line);
        }
    }
    
    doc.setHtml(formattedContent);

    painter.save();
    painter.translate(rect.x() + 20, rect.y() + 20);
    doc.drawContents(&painter, QRectF(0, 0, rect.width() - 40, rect.height() - 40));
    painter.restore();
}

bool ReportGenerator::saveReportImage(const QPixmap& image, const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    QDir().mkpath(fileInfo.absolutePath());
    
    return image.save(filePath, "PNG");
}

int ReportGenerator::calculateTextHeight(const QString& text, const QFont& font, int width)
{
    QFontMetrics metrics(font);
    QRect boundingRect = metrics.boundingRect(QRect(0, 0, width, 0), 
                                            Qt::TextWordWrap, text);
    return boundingRect.height();
}