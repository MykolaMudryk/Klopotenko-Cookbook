#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <QObject>
#include <QString>

#include "QtNetwork/qnetworkaccessmanager.h"

class NetworkClient : public QObject {
  Q_OBJECT

 private:
  QNetworkAccessManager *manager;

 public:
  explicit NetworkClient(QObject *parent = nullptr);
  void sendRequest(const QString &endpoint);

 signals:

  void requestFinished(const QByteArray &response);

 private slots:
  void onReplyFinished();
};

#endif  // NETWORK_CLIENT_H
