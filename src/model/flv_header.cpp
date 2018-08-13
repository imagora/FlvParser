// Copyright (c) 2018 winking324
//


#include "model/flv_header.h"
#include "commons/error_code.h"


namespace flv_parser {


FlvHeader::FlvHeader() {
}

int FlvHeader::ParseData(const std::string &data) {
  return CODE_SUCCESS;
}


}  // namespace flv_parser

