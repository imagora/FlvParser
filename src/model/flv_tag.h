// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include <memory>
#include "model/flv_data.h"


namespace flv_parser {


enum TagType {
  AUDIO_TAG = 8,
  VIDEO_TAG = 9,
  SCRIPT_TAG = 18
};


class FlvTag {
 public:
  FlvTag();

  size_t ParseData(const std::string &data, size_t pos);

  std::string Type();

  std::string Info();

 private:
  size_t ParseAudio(const std::string &data, size_t pos);

  size_t ParseVideo(const std::string &data, size_t pos);

  size_t ParseScript(const std::string &data, size_t pos);

 private:
  uint8_t reserved_;
  uint8_t filter_;
  uint8_t type_;
  uint32_t size_;
  uint32_t timestamp_;
  uint8_t timestamp_extended_;
  uint32_t stream_id_;
  std::shared_ptr<FlvData> data_;
};


}  // namespace flv_parser

