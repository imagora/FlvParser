// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <QWidget>
#include <QTreeView>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>
#include <QPushButton>
#include <QStandardItemModel>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include "view/main_menubar.h"
#include "controller/http_client.h"
#include "controller/flv_parser.h"


namespace flv_parser {


class MainWidget : public QWidget {
  Q_OBJECT

 public:
  MainWidget(QWidget *parent = nullptr);

  virtual ~MainWidget();

 protected:
  void keyReleaseEvent(QKeyEvent *event) override;

 private slots:
  void OnPlay();

  void OnReadyRead(const std::string &data);

  void OnFinished();

  void OnFlvPacket(const std::string &type, const std::string &info);

  void OnSelectPacket(const QModelIndex &index);

 private:
  void InitWidget();

  void InitSlots();

  void Reset();

  void Show(int index);

  void ShowDetail(const YAML::Node &root, QStandardItem *root_item = nullptr);

  void ShowData(const std::string &data);

  QChar AsciiChar(const QByteArray &data, int index);

 private:
  QLineEdit *url_;
  QPushButton *play_;
  QTextEdit *hex_view_;
  QTreeView *info_view_;
  QTreeView *detail_view_;
  QStandardItemModel *info_model_;
  QStandardItemModel *detail_model_;

  MainMenuBar *menu_bar_;

  HttpClient *http_client_;
  FlvParser *flv_parser_;
};


}  // namespace flv_parser

