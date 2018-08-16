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
  if (url_->text().isEmpty()) return;

  if (play_->text() == "Play") {
    play_->setText("Stop");
    info_model_->clear();
    info_model_->setHorizontalHeaderLabels(QStringList() << "Type" << "Info");
    http_client_->HttpRequest(url_->text());
  } else {
    http_client_->HttpAbort();
  }
}

void MainWidget::ReadyRead(const std::string &data) {
  if (!flv_parser_->ParseData(data)) {
    qCritical() << "parse flv error, close the http connection";
    http_client_->HttpAbort();
  }
}

void MainWidget::Finished() {
  play_->setText("Play");
  flv_parser_->Reset();
}

void MainWidget::OnFlvPacket(const std::string &type, const std::string &info) {
  info_model_->appendRow(QList<QStandardItem *>()
                         << new QStandardItem(type.c_str())
                         << new QStandardItem(info.c_str()));
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

  http_client_ = new HttpClient(this);
  flv_parser_ = new FlvParser(this);
  menu_bar_ = new MainMenuBar(this);
}

void MainWidget::InitSlots() {
  connect(play_, SIGNAL(released()), this, SLOT(OnPlay()));
  connect(http_client_, SIGNAL(ReadyRead(const std::string &)), this,
          SLOT(ReadyRead(const std::string &)));
  connect(http_client_, SIGNAL(Finished()),  this, SLOT(Finished()));
  connect(flv_parser_,
          SIGNAL(ParsedPacket(const std::string &, const std::string &)), this,
          SLOT(OnFlvPacket(const std::string &, const std::string &)));
}

}  // namespace flv_parser


