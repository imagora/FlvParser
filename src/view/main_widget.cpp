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
  hex_view_->setFontFamily("Monaco");

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
  detail_model_->setHorizontalHeaderLabels(
        QStringList() << "Detail" << "Value");
}

void MainWidget::Show(int index) {
  detail_model_->clear();
  detail_model_->setHorizontalHeaderLabels(
        QStringList() << "Detail" << "Value");
  YAML::Node root = flv_parser_->Detail(index);
  ShowDetail(root);
  std::string data = flv_parser_->Data(index);
  ShowData(data);
}

void MainWidget::ShowDetail(const YAML::Node &root, QStandardItem *root_item) {
  if (!root.IsMap()) {
    QStandardItem *value_item =
        new QStandardItem(root.as<std::string>().c_str());
    value_item->setEditable(false);
    if (root_item == nullptr) {
      detail_model_->appendRow(value_item);
    } else {
      root_item->appendRow(value_item);
    }
    return;
  }

  for (auto iter = root.begin(); iter != root.end(); ++iter) {
    QStandardItem *name_item =
        new QStandardItem(iter->first.as<std::string>().c_str());
    name_item->setEditable(false);
    if (root_item == nullptr) {
      detail_model_->appendRow(name_item);
    } else {
      root_item->appendRow(name_item);
    }

    if (iter->second.IsMap()) {
      ShowDetail(iter->second, name_item);
    } else if (iter->second.IsSequence()) {
      for (auto seq_iter = iter->second.begin(); seq_iter != iter->second.end(); ++seq_iter) {
        ShowDetail(*seq_iter, name_item);
      }
    } else {
      QStandardItem *info_item =
          new QStandardItem(iter->second.as<std::string>().c_str());
      info_item->setEditable(false);

      if (root_item == nullptr) {
        detail_model_->setItem(detail_model_->indexFromItem(name_item).row(), 1,
                               info_item);
      } else {
        root_item->setChild(name_item->index().row(), 1, info_item);
      }
    }
  }
  detail_view_->expandAll();
}

void MainWidget::ShowData(const std::string &data) {
  QByteArray bytes = QByteArray::fromStdString(data);
  int address_size =
      QString("%1").arg(bytes.size() + 0, 4, 16, QChar('0')).size();

  QString result;
  for (int i= 0; i < bytes.size(); i += 16) {
    QString adrStr = QString("%1").arg(0 + i, address_size, 16, QChar('0'));
    QString hexStr;
    QString ascStr;
    for (int j=0; j<16; j++) {
      if ((i + j) < bytes.size()) {
        hexStr.append(" ").append(bytes.mid(i+j, 1).toHex());
        ascStr.append(AsciiChar(bytes, i+j));
      }
    }
    result += adrStr + " " + QString("%1").arg(hexStr, -48) +
        "  " + QString("%1").arg(ascStr, -17) + "\n";
  }

  hex_view_->clear();
  hex_view_->setText(result);
}

QChar MainWidget::AsciiChar(const QByteArray &data, int index) {
  char ch = data[index];
  if ((ch < 0x20) || (ch > 0x7e)) ch = '.';
  return QChar(ch);
}

}  // namespace flv_parser


