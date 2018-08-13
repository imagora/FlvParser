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

 public slots:
  void ReadyRead(const std::string &data);

 private slots:
  void HttpRedirected(const QUrl &url);

  void HttpFinished();

  void HttpReadyRead();

 private:
  void HttpRequest(const QUrl &url);

 private:
  QNetworkAccessManager *net_mgr_;
  QNetworkReply *net_reply_;
};


}  // namespace flv_parser

