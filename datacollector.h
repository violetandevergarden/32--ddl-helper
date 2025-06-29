#ifndef DATACOLLECTOR_H
#define DATACOLLECTOR_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QJsonObject>
#include <QJsonArray>
#include "xlsxdocument.h" // QXlsx库

struct TaskInfo {
    QString title;
    QString deadline;
    QString priority;
    QString content;
    bool isCompleted;
    QDate createDate;
};

class DataCollector : public QObject
{
    Q_OBJECT

public:
    explicit DataCollector(QObject *parent = nullptr);
    
    // 收集本周任务数据
    QString collectWeeklyData();
    
    // 收集指定日期范围的任务数据
    QString collectDataByDateRange(const QDate& startDate, const QDate& endDate);
    
    // 从Excel文件读取所有任务
    QList<TaskInfo> loadAllTasks();
    
    // 设置Excel文件路径
    void setExcelFilePath(const QString& filePath);

private:
    QString m_excelFilePath;
    
    // 解析任务数据为可读文本
    QString formatTasksToText(const QList<TaskInfo>& tasks);
    
    // 判断任务是否在指定日期范围内
    bool isTaskInDateRange(const TaskInfo& task, const QDate& startDate, const QDate& endDate);
    
    // 判断任务是否已完成（基于当前日期和截止日期）
    bool isTaskCompleted(const QString& deadline);
};

#endif // DATACOLLECTOR_H