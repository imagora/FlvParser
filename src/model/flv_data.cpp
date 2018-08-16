// Copyright (c) 2018 winking324
//


#include "model/flv_data.h"


namespace flv_parser {


FlvData::FlvData() {
}

FlvData::~FlvData() {
}

size_t FlvData::ParseData(const std::string &data, size_t pos, size_t length) {
  data_ = std::string(data, pos, length);
  return length;
}

std::string FlvData::Info() {
  return "";
}


}  // namespace flv_parser

