// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <list>
#include <string>
#include <QObject>
#include "model/flv_header.h"
#include "model/flv_body.h"


namespace flv_parser {


class FlvParser : public QObject {
  Q_OBJECT

  typedef std::list<FlvBody> FlvBodys;
 public:
  FlvParser(QObject *parent = nullptr);

  ~FlvParser();

  bool ParseData(const std::string &data);

  void Reset();

  Json::Value Detail(int index);

  std::string Data(int index);

 signals:
  void ParsedPacket(const std::string &type, const std::string &info);

 private:
  size_t ParseHeader();

  size_t ParseBody();

 private:
  bool has_header_;
  std::string buffer_;

  FlvHeader flv_header_;
  FlvBodys flv_bodys_;
};


}  // namespace flv_parser

