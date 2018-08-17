// Copyright (c) 2018 winking324
//


#include "src/view/main_widget.h"
#include <QApplication>
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

void MainWidget::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() != Qt::Key_Up && event->key() != Qt::Key_Down) {
    return;
  }

  if (QApplication::focusWidget() != info_view_) {
    return;
  }

  Show(info_view_->currentIndex().row());
}

void MainWidget::OnPlay() {
  if (url_->text().isEmpty()) return;

  if (play_->text() == "Play") {
    Reset();
    play_->setText("Stop");
    http_client_->HttpRequest(url_->text());
  } else {
    http_client_->HttpAbort();
  }
}

void MainWidget::OnReadyRead(const std::string &data) {
  if (!flv_parser_->ParseData(data)) {
    qCritical() << "parse flv error, close the http connection";
    http_client_->HttpAbort();
  }
}

void MainWidget::OnFinished() {
  play_->setText("Play");
}

void MainWidget::OnFlvPacket(const std::string &type, const std::string &info) {
  QStandardItem *type_item = new QStandardItem(type.c_str());
  QStandardItem *info_item = new QStandardItem(info.c_str());
  type_item->setEditable(false);
  info_item->setEditable(false);
  info_model_->appendRow(QList<QStandardItem *>() << type_item << info_item);
}

void MainWidget::OnSelectPacket(const QModelIndex &index) {
  Show(index.row());
}

void MainWidget::InitWidget() {
  url_ = new QLineEdit(this);
  play_ = new QPushButton("Play", this);
  hex_view_ = new QTextEdit(this);
  info_view_ = new QTreeView(this);
  detail_view_ = new QTreeView(this);
  info_model_ = new QStandardItemModel(this);
  detail_model_ = new QStandardItemModel(this);
  menu_bar_ = new MainMenuBar(this);
  http_client_ = new HttpClient(this);
  flv_parser_ = new FlvParser(this);

  info_view_->setModel(info_model_);
  detail_view_->setModel(detail_model_);

  Reset();

  QGridLayout *layout = new QGridLayout(this);
  layout->addWidget(url_, 0, 0, 1, 2);
  layout->addWidget(play_, 0, 2, 1, 1);

  layout->addWidget(info_view_, 1, 0, 2, 1);
  layout->addWidget(detail_view_, 1, 1, 1, 1);
  layout->addWidget(hex_view_, 2, 1, 1, 1);

  this->setLayout(layout);
}

void MainWidget::InitSlots() {
  connect(play_, SIGNAL(released()), this, SLOT(OnPlay()));
  connect(http_client_, SIGNAL(ReadyRead(const std::string &)), this,
          SLOT(OnReadyRead(const std::string &)));
  connect(http_client_, SIGNAL(Finished()),  this, SLOT(OnFinished()));
  connect(flv_parser_,
          SIGNAL(ParsedPacket(const std::string &, const std::string &)), this,
          SLOT(OnFlvPacket(const std::string &, const std::string &)));
  connect(info_view_, SIGNAL(clicked(const QModelIndex &)), this,
          SLOT(OnSelectPacket(const QModelIndex &)));
}

void MainWidget::Reset() {
  flv_parser_->Reset();

  info_model_->clear();
  detail_model_->clear();
  hex_view_->clear();
  info_model_->setHorizontalHeaderLabels(QStringList() << "Type" << "Info");
  detail_model_->setHorizontalHeaderLabels(QStringList() << "Detail");
}

void MainWidget::Show(int index) {
  detail_model_->clear();
  detail_model_->setHorizontalHeaderLabels(QStringList() << "Detail");
  Json::Value root = flv_parser_->Detail(index);
  ShowDetail(root);
}

void MainWidget::ShowDetail(const Json::Value &root, QStandardItem *root_item) {
  if (!root.isObject()) {
    QStandardItem *value_item = new QStandardItem(root.asString().c_str());
    value_item->setEditable(false);
    if (root_item == nullptr) {
      detail_model_->appendRow(value_item);
    } else {
      root_item->appendRow(value_item);
    }
    return;
  }

  Json::Value::Members members = root.getMemberNames();
  for (auto iter = members.begin(); iter != members.end(); ++iter) {
    QStandardItem *name_item = new QStandardItem(iter->c_str());
    name_item->setEditable(false);
    if (root_item == nullptr) {
      detail_model_->appendRow(name_item);
    } else {
      root_item->appendRow(name_item);
    }

    uint32_t value_type = root[*iter].type();
    if (value_type == Json::objectValue) {
      ShowDetail(root[*iter], name_item);
    } else if (value_type == Json::arrayValue) {
      for (uint32_t i = 0; i < root[*iter].size(); ++i) {
        ShowDetail(root[*iter][i], name_item);
      }
    } else {
      QStandardItem *info_item =
          new QStandardItem(root[*iter].asString().c_str());
      info_item->setEditable(false);

      if (root_item == nullptr) {
        detail_model_->setItem(detail_model_->indexFromItem(name_item).row(), 1,
                               info_item);
      } else {
        root_item->setChild(name_item->index().row(), 1, info_item);
      }
    }
  }
}

}  // namespace flv_parser


