#include "network_client.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "json_parser.h"

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent), manager(new QNetworkAccessManager(this)) {}

void NetworkClient::sendRequest(const QString &endpoint) {
  QNetworkRequest request((QUrl(endpoint)));

  QNetworkReply *reply = manager->get(request);

  connect(reply, &QNetworkReply::finished, this,
          &NetworkClient::onReplyFinished);
}

void NetworkClient::onReplyFinished() {
  QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

  if (reply->error() == QNetworkReply::NoError) {
    int statusCode =
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "Statuc code on client: " << statusCode;

    if (statusCode == 200) {
      QByteArray response = reply->readAll();

      emit requestFinished(response);
    } else {
      qWarning() << "Server returned an error" << statusCode;
    }

  } else {
    qWarning() << "Network error: " << reply->errorString();
  }

  reply->deleteLater();
}
