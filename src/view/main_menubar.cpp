// Copyright (c) 2018 winking324
//


#include "view/main_menubar.h"
#include <QMenu>


namespace flv_parser {


MenuBar::MenuBar(QWidget *parent/* = nullptr*/)
  : QMenuBar(parent) {
  help_menu_ = new QMenu("Help", this);
  help_menu_->addAction("Help", this, SLOT(OpenAboutDlg()));
  help_menu_->addAction("About", this, SLOT(OpenAboutDlg()));
  addMenu(help_menu_);
}

MenuBar::~MenuBar() {
}

void MenuBar::OpenAboutDlg() {
  about_dlg_ = new AboutDialog(this);
  about_dlg_->show();
}


}  // namespace flv_parser

