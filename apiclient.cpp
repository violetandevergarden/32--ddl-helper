#include "apiclient.h"
#include <QDebug>
#include <QDate>

ApiClient::ApiClient(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
}

void ApiClient::setApiConfig(const QString& apiKey, const QString& baseUrl)
{
    m_apiKey = apiKey;
    m_baseUrl = baseUrl;
}

void ApiClient::generateWeeklyReport(const QString& taskData)
{
    if (m_apiKey.isEmpty()) {
        emit errorOccurred("API密钥未设置");
        return;
    }

    QNetworkRequest request;
    request.setUrl(QUrl(m_baseUrl + "/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_apiKey).toUtf8());

    QJsonObject requestBody;
    requestBody["model"] = "gpt-3.5-turbo";
    requestBody["max_tokens"] = 1000;
    requestBody["temperature"] = 0.7;

    QJsonArray messages;
    QJsonObject systemMessage;
    systemMessage["role"] = "system";
    systemMessage["content"] = "你是一个专业的工作助手，请根据用户的任务数据生成一份简洁明了的周报。包含：本周完成任务、未完成任务、任务完成情况分析、下周计划建议。";

    QJsonObject userMessage;
    userMessage["role"] = "user";
    userMessage["content"] = formatTaskDataForPrompt(taskData);

    messages.append(systemMessage);
    messages.append(userMessage);
    requestBody["messages"] = messages;

    QJsonDocument doc(requestBody);
    QByteArray requestData = doc.toJson();

    QNetworkReply* reply = m_networkManager->post(request, requestData);
    connect(reply, &QNetworkReply::finished, this, &ApiClient::onReplyFinished);
}

QString ApiClient::formatTaskDataForPrompt(const QString& taskData)
{
    QDate currentDate = QDate::currentDate();
    QDate weekStart = currentDate.addDays(-currentDate.dayOfWeek() + 1);
    QDate weekEnd = weekStart.addDays(6);
    
    QString prompt = QString("请为我生成 %1 到 %2 的周报。\n\n任务数据：\n%3\n\n"
                           "请分析这些任务的完成情况，并生成一份结构清晰的周报。")
                    .arg(weekStart.toString("yyyy-MM-dd"))
                    .arg(weekEnd.toString("yyyy-MM-dd"))
                    .arg(taskData);
    
    return prompt;
}

void ApiClient::onReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    if (reply->error() == QNetworkReply::NoError) {
        QByteArray responseData = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject responseObj = doc.object();
        QJsonDocument docObject(responseObj);
        QString jsonStringObject = docObject.toJson(QJsonDocument::Compact);
        qDebug()<<jsonStringObject;
        if (responseObj.contains("choices")) {
            QJsonArray choices = responseObj["choices"].toArray();
            if (!choices.isEmpty()) {
                QJsonObject firstChoice = choices[0].toObject();
                QJsonObject message = firstChoice["message"].toObject();
                QString content = message["content"].toString();
                
                emit reportGenerated(content);
            } else {
                emit errorOccurred("API返回数据格式错误");
            }
        } else {
            emit errorOccurred("API返回数据格式错误");
        }
    } else {
        emit errorOccurred(QString("网络错误: %1").arg(reply->errorString()));
    }

    reply->deleteLater();
}
