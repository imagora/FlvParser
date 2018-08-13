// Copyright (c) 2018 winking324
//


#include "src/view/main_widget.h"
#include <QGridLayout>


namespace flv_parser {


MainWidget::MainWidget(QWidget *parent)
  : QWidget(parent) {
  url_ = new QLineEdit(this);
  play_ = new QPushButton("Play", this);
  info_ = new QTreeView(this);

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(url_, 0, 0);
  layout->addWidget(play_, 0, 1);
  layout->addWidget(info_, 1, 0);

  this->setLayout(layout);
}

MainWidget::~MainWidget() {
}


}  // namespace flv_parser


