// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <QNetworkReply>
#include <QNetworkAccessManager>


namespace flv_parser {


class HttpClient : public QObject {
  Q_OBJECT

 public:
  HttpClient(QObject *parent = nullptr);

  virtual ~HttpClient();

  void HttpRequest(const QUrl &url);

  void HttpAbort();

 signals:
  void ReadyRead(const std::string &data);

  void Finished();

 private slots:
  void HttpFinished();

  void HttpReadyRead();

 private:
  QNetworkAccessManager *net_mgr_;
  QNetworkReply *net_reply_;
};


}  // namespace flv_parser

