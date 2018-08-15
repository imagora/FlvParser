// Copyright (c) 2018 winking324
//


#include "controller/flv_parser.h"

#include <QDebug>


namespace flv_parser {


FlvParser::FlvParser(QObject *parent)
  : QObject(parent) {
  has_header_ = false;
}

FlvParser::~FlvParser() {
}

bool FlvParser::ParseData(const std::string &data) {
  if (!has_header_) {
    size_t read_size = flv_header_.ParseData(data);
    if (read_size > 0) {
      has_header_ = true;
      buffer_ = std::string(data, read_size, data.size());
    } else {
      return false;
    }
  } else {
    buffer_ += data;
  }

  size_t body_size = 0;
  qInfo() << "read flv body buffer size: " << buffer_.size();
  while ((body_size = ParseBody()) > 0) {
    qInfo() << "read flv body size: " << body_size
            << ", buffer size: " << buffer_.size();
  }
  return true;
}

void FlvParser::Reset() {
  buffer_.clear();
  has_header_ = false;
}

size_t FlvParser::ParseBody() {
  FlvBody body;
  size_t read_size = body.ParseData(buffer_);
  if (read_size > 0) {
    flv_bodys_.push_back(body);
    buffer_.erase(0, read_size);
    return read_size;
  }
  return 0;
}


}  // namespace flv_parser

