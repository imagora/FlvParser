// Copyright (c) 2018 winking324
//


#include "model/flv_tag.h"
#include "commons/error_code.h"


namespace flv_parser {


FlvTag::FlvTag() {
}

int FlvTag::ParseData(const std::string &data) {
  return CODE_SUCCESS;
}


}  // namespace flv_parser

