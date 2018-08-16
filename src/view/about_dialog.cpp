// Copyright (c) 2018 winking324
//


#include "view/about_dialog.h"

#include <QIcon>
#include <QLabel>
#include <QGridLayout>

#include "commons/definations.h"


namespace flv_parser {

AboutDialog::AboutDialog(QWidget *parent)
  : QDialog(parent) {
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowIcon(QIcon(":/icon.png"));
  setWindowTitle("About");
  setMinimumSize(400, 200);
  setMaximumSize(400, 200);

  QGridLayout *layout = new QGridLayout(this);
  QLabel *icon_label = new QLabel(this);
  icon_label->setPixmap(QPixmap(":/icon.png"));
  layout->addWidget(icon_label, 0, 0, 1, 1);

  QLabel *about_label = new QLabel(tr("Flv parser"),
                                   this);

  QLabel *version_label = new QLabel(tr("Version: ") + tr(BUILD_VERSION) +
                                     tr("\nBuilt: ") + tr(BUILD_DATETIME) +
                                     tr("\nCopyright (c) 2018 winking324"),
                                     this);

  layout->addWidget(about_label, 0, 1, 1, 1);
  layout->addWidget(version_label, 1, 1, 1, 1);
  setLayout(layout);
}

}  // namespace flv_parser
