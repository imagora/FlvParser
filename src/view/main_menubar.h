// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <map>

#include <QMenu>
#include <QMenuBar>

#include "view/about_dialog.h"


namespace flv_parser {


class MainMenuBar : public QMenuBar {
  Q_OBJECT

 public:
  MainMenuBar(QWidget *parent = nullptr);
  ~MainMenuBar();

 private slots:
  void OpenAboutDlg();

 private:
  QMenu *help_menu_;
  AboutDialog *about_dlg_;
};


}  // namespace flv_parser

