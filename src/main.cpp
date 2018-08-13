// Copyright (c) 2018 winking324
//


#include "src/view/main_widget.h"
#include <QApplication>


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  flv_parser::MainWidget w;
  w.show();

  return a.exec();
}
