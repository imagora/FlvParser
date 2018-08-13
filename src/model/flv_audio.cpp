// Copyright (c) 2018 winking324
//


#include "model/flv_audio.h"
#include "commons/error_code.h"


namespace flv_parser {


FlvAudio::FlvAudio() {
}

FlvAudio::~FlvAudio() {
}

int FlvAudio::ParseData(const std::string &data) {
  return CODE_SUCCESS;
}


}  // namespace flv_parser

