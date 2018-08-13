// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <QWidget>
#include <QTreeView>
#include <QLineEdit>
#include <QPushButton>


namespace flv_parser {


class MainWidget : public QWidget {
  Q_OBJECT

 public:
  MainWidget(QWidget *parent = nullptr);
  ~MainWidget();

 private:
  QLineEdit *url_;
  QPushButton *play_;
  QTreeView *info_;
};


}  // namespace flv_parser

