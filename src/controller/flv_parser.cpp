// Copyright (c) 2018 winking324
//


#include "controller/flv_parser.h"
#include "commons/error_code.h"


namespace flv_parser {


FlvParser::FlvParser(QObject *parent)
  : QObject(parent) {
  has_header_ = false;
}

FlvParser::~FlvParser() {
}

size_t FlvParser::ParseData(const std::string &data) {
  if (!has_header_) {
    size_t read_size = flv_header_.ParseData(data);
    if (read_size > 0) {
      has_header_ = true;
      buffer_ = std::string(data, read_size, data.size());
      return read_size;
    } else {
      return 0;
    }
  }

  buffer_ += data;
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

