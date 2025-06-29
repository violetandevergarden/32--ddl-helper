#include "datacollector.h"
#include <QDebug>

DataCollector::DataCollector(QObject *parent)
    : QObject(parent)
    , m_excelFilePath("myquest.xlsx")
{
}

void DataCollector::setExcelFilePath(const QString& filePath)
{
    m_excelFilePath = filePath;
}

QString DataCollector::collectWeeklyData()
{
    QDate currentDate = QDate::currentDate();
    QDate weekStart = currentDate.addDays(-currentDate.dayOfWeek() + 1);
    QDate weekEnd = weekStart.addDays(6);
    
    return collectDataByDateRange(weekStart, weekEnd);
}

QString DataCollector::collectDataByDateRange(const QDate& startDate, const QDate& endDate)
{
    QList<TaskInfo> allTasks = loadAllTasks();
    QList<TaskInfo> relevantTasks;
    
    // 筛选指定日期范围内的任务
    for (const TaskInfo& task : allTasks) {
        if (isTaskInDateRange(task, startDate, endDate)) {
            relevantTasks.append(task);
        }
    }
    
    return formatTasksToText(relevantTasks);
}

QList<TaskInfo> DataCollector::loadAllTasks()
{
    QList<TaskInfo> tasks;
    QXlsx::Document doc(m_excelFilePath);
    
    // 找到有效数据的行数
    int maxRow = 1;
    for (int i = 1; i <= 100; i++) {
        if (doc.read(i, 1).isNull()) {
            maxRow = i;
            break;
        }
    }
    
    // 读取所有任务数据
    for (int i = 1; i < maxRow; i++) {
        TaskInfo task;
        task.title = doc.read(i, 1).toString();
        task.deadline = doc.read(i, 2).toString();
        task.priority = doc.read(i, 3).toString();
        task.content = doc.read(i, 4).toString();
        
        // 根据截止日期判断是否完成
        task.isCompleted = isTaskCompleted(task.deadline);
        
        // 假设创建日期是截止日期前7天（这里可以根据实际情况调整）
        QDate deadlineDate = QDate::fromString(task.deadline, "yyyy-MM-dd");
        task.createDate = deadlineDate.addDays(-7);
        
        if (!task.title.isEmpty()) {
            tasks.append(task);
        }
    }
    
    return tasks;
}

QString DataCollector::formatTasksToText(const QList<TaskInfo>& tasks)
{
    QString result;
    result += QString("数据统计时间：%1\n").arg(QDate::currentDate().toString("yyyy-MM-dd"));
    result += QString("任务总数：%1\n\n").arg(tasks.size());
    
    // 分类统计
    int completedCount = 0;
    int urgentCount = 0;
    int normalCount = 0;
    int lowCount = 0;
    
    QString completedTasks = "【已完成任务】\n";
    QString pendingTasks = "【未完成任务】\n";
    
    for (const TaskInfo& task : tasks) {
        QString taskInfo = QString("- %1 (截止:%2, 优先级:%3)\n")
                          .arg(task.title)
                          .arg(task.deadline)
                          .arg(task.priority);
        
        if (task.isCompleted) {
            completedCount++;
            completedTasks += taskInfo;
        } else {
            pendingTasks += taskInfo;
        }
        
        // 统计优先级
        if (task.priority == "紧急") urgentCount++;
        else if (task.priority == "一般") normalCount++;
        else lowCount++;
    }
    
    result += QString("完成任务数：%1\n").arg(completedCount);
    result += QString("未完成任务数：%1\n").arg(tasks.size() - completedCount);
    result += QString("紧急任务数：%1\n").arg(urgentCount);
    result += QString("一般任务数：%1\n").arg(normalCount);
    result += QString("低优先级任务数：%1\n\n").arg(lowCount);
    
    result += completedTasks + "\n";
    result += pendingTasks;
    
    return result;
}

bool DataCollector::isTaskInDateRange(const TaskInfo& task, const QDate& startDate, const QDate& endDate)
{
    QDate taskDeadline = QDate::fromString(task.deadline, "yyyy-MM-dd");
    QDate taskCreateDate = task.createDate;
    
    // 如果任务的截止日期或创建日期在指定范围内，就包含这个任务
    return (taskDeadline >= startDate && taskDeadline <= endDate) ||
           (taskCreateDate >= startDate && taskCreateDate <= endDate);
}

bool DataCollector::isTaskCompleted(const QString& deadline)
{
    QDate currentDate = QDate::currentDate();
    QDate deadlineDate = QDate::fromString(deadline, "yyyy-MM-dd");
    
    // 如果当前日期超过截止日期，认为任务已完成
    return currentDate > deadlineDate;
}