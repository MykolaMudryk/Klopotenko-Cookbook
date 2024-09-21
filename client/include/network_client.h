#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QObject>
#include <QString>
#include <QWebSocket>

class NetworkClient : public QObject {
  Q_OBJECT

 private:
  QWebSocket *websocket;

 public:
  explicit NetworkClient(QObject *parent = nullptr);
  void connectToServer();
  void sendMessage(const QString &message);

 signals:
  void requestFinished(const QByteArray &response);
  void errorOccurred(const QString &errorString);

 private slots:
  void onConnected();
  void onTextMessageReceived(const QString &message);
  void onError(QAbstractSocket::SocketError error);
};

#endif  // NETWORK_CLIENT_H
