// Copyright (c) 2018 winking324
//


#include "src/view/main_widget.h"
#include <QGridLayout>
#include <QTimer>


namespace flv_parser {


MainWidget::MainWidget(QWidget *parent)
  : QWidget(parent) {
  InitWidget();
  InitSlots();
}

MainWidget::~MainWidget() {
}

void MainWidget::OnPlay() {
//  HttpRequest(url_->text());
}

void MainWidget::InitWidget() {
  url_ = new QLineEdit(this);
  play_ = new QPushButton("Play", this);
  info_view_ = new QTreeView(this);
  info_model_ = new QStandardItemModel(info_view_);

  info_view_->setModel(info_model_);
  info_model_->setHorizontalHeaderLabels(QStringList() << "Type" << "Info");

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(url_, 0, 0);
  layout->addWidget(play_, 0, 1);
  layout->addWidget(info_view_, 1, 0);

  this->setLayout(layout);
}

void MainWidget::InitSlots() {
  connect(play_, SIGNAL(released()), this, SLOT(OnPlay()));
}

}  // namespace flv_parser


