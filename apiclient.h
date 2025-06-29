#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ApiClient : public QObject
{
    Q_OBJECT

public:
    explicit ApiClient(QObject *parent = nullptr);
    
    void generateWeeklyReport(const QString& taskData);

    void setApiConfig(const QString& apiKey, const QString& baseUrl = "https://api.openai.com/v1");

signals:
    void reportGenerated(const QString& reportContent);
    void errorOccurred(const QString& error);

private slots:
    void onReplyFinished();

private:
    QNetworkAccessManager* m_networkManager;
    QString m_apiKey;
    QString m_baseUrl;
    
    QString formatTaskDataForPrompt(const QString& taskData);
};

#endif // APICLIENT_H