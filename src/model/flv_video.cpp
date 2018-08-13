// Copyright (c) 2018 winking324
//


#include "model/flv_video.h"
#include "commons/error_code.h"


namespace flv_parser {


FlvVideo::FlvVideo() {
}

FlvVideo::~FlvVideo() {
}

int FlvVideo::ParseData(const std::string &data) {
  return CODE_SUCCESS;
}


}  // namespace flv_parser

