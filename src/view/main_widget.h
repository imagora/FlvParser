// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <QWidget>
#include <QTreeView>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QNetworkReply>
#include <QNetworkAccessManager>


namespace flv_parser {


class MainWidget : public QWidget {
  Q_OBJECT

 public:
  MainWidget(QWidget *parent = nullptr);

  virtual ~MainWidget();

 private slots:
  void OnPlay();

 private:
  void InitWidget();

  void InitSlots();

 private:
  QLineEdit *url_;
  QPushButton *play_;
  QTreeView *info_view_;
  QStandardItemModel *info_model_;
};


}  // namespace flv_parser

