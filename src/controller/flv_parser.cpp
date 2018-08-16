// Copyright (c) 2018 winking324
//


#include "controller/flv_parser.h"

#include <QDebug>


namespace flv_parser {


FlvParser::FlvParser(QObject *parent)
  : QObject(parent) {
  Reset();
}

FlvParser::~FlvParser() {
}

bool FlvParser::ParseData(const std::string &data) {
  buffer_ += data;

  if (!has_header_) {
    size_t header_size = ParseHeader();
    if (header_size > 0) {
      buffer_.erase(0, header_size);
    } else {
      return false;
    }
  }

  size_t body_size = 0;
  while ((body_size = ParseBody()) > 0) {
    buffer_.erase(0, body_size);
  }
  return true;
}

void FlvParser::Reset() {
  buffer_.clear();
  has_header_ = false;
}

Json::Value FlvParser::Detail(int index) {
  if (index == 0) {
    return flv_header_.Detail();
  }
  return Json::Value();
}

std::string FlvParser::Data(int index) {
  if (index == 0) {
    return "";
  }
  return "";
}

size_t FlvParser::ParseHeader() {
  size_t read_size = flv_header_.ParseData(buffer_);
  if (read_size > 0) {
    has_header_ = true;
    emit ParsedPacket(flv_header_.Type(), flv_header_.Info());
  }
  return read_size;
}

size_t FlvParser::ParseBody() {
  FlvBody body;
  size_t read_size = body.ParseData(buffer_);
  if (read_size > 0) {
    flv_bodys_.push_back(body);
    emit ParsedPacket(body.Type(), body.Info());
  }
  return read_size;
}


}  // namespace flv_parser

