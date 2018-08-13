// Copyright (c) 2018 winking324
//


#include "model/flv_body.h"
#include "commons/error_code.h"


namespace flv_parser {


FlvBody::FlvBody() {
}

int FlvBody::ParseData(const std::string &data) {
  return CODE_SUCCESS;
}


}  // namespace flv_parser

