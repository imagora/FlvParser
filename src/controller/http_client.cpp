// Copyright (c) 2018 winking324
//


#include "controller/http_client.h"


namespace flv_parser {


HttpClient::HttpClient(QObject *parent)
  : QObject (parent) {
  net_mgr_ = new QNetworkAccessManager(this);
  net_mgr_->setNetworkAccessible(QNetworkAccessManager::Accessible);
  net_reply_ = nullptr;
}

HttpClient::~HttpClient() {
}

void HttpClient::HttpRedirected(const QUrl &url) {
  qInfo() << "redirected request url: " << url;
  HttpRequest(url);
}

void HttpClient::HttpFinished() {
  if (net_reply_->error() == QNetworkReply::NoError) {
    qInfo() << "http request finished";
    net_reply_->deleteLater();
  } else {
    qCritical() << "http request error: " << net_reply_->error();
  }
}

void HttpClient::HttpReadyRead() {
  std::string read_data = net_reply_->readAll().toStdString();
  qDebug() << "read data size: " << read_data.size();
  emit ReadyRead(read_data);
}

void HttpClient::HttpRequest(const QUrl &url) {
  qInfo() << "request url: " << url;
  if (net_reply_ != nullptr && net_reply_->isRunning()) {
    net_reply_->abort();
  }

  QNetworkRequest net_request(url);
  net_request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
  net_reply_ = net_mgr_->get(net_request);
  connect(net_reply_, SIGNAL(redirected(const QUrl &)), this,
          SLOT(HttpRedirected(const QUrl &)));
  connect(net_reply_, SIGNAL(finished()), this, SLOT(HttpFinished()));
  connect(net_reply_, SIGNAL(readyRead()), this, SLOT(HttpReadyRead()));
}


}  // namespace flv_parser

