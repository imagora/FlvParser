// Copyright (c) 2018 winking324
//


#include "controller/http_client.h"


namespace flv_parser {


HttpClient::HttpClient(QObject *parent)
  : QObject (parent) {
  net_mgr_ = new QNetworkAccessManager(this);
  net_reply_ = nullptr;
}

HttpClient::~HttpClient() {
}

void HttpClient::HttpRequest(const QUrl &url) {
  qInfo() << "http request url: " << url;
  if (net_reply_ != nullptr) {
    qInfo() << "http requesting url: " << net_reply_->url();
    return;
  }

  net_reply_ = net_mgr_->get(QNetworkRequest(url));
  connect(net_reply_, SIGNAL(finished()), this, SLOT(HttpFinished()));
  connect(net_reply_, SIGNAL(readyRead()), this, SLOT(HttpReadyRead()));
}

void HttpClient::HttpAbort() {
  if (net_reply_ != nullptr) {
    net_reply_->abort();
  }
}

void HttpClient::HttpFinished() {
  qInfo() << "http request " << net_reply_->url() << " finished";

  const QVariant redirection =
      net_reply_->attribute(QNetworkRequest::RedirectionTargetAttribute);
  net_reply_->deleteLater();
  net_reply_ = nullptr;

  if (!redirection.isNull()) {
    HttpRequest(redirection.toUrl());
    return;
  }

  emit Finished();
}



void HttpClient::HttpReadyRead() {
  std::string read_data = net_reply_->readAll().toStdString();

  emit ReadyRead(read_data);
}


}  // namespace flv_parser

