// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include <string>

#include <yaml-cpp/yaml.h>


namespace flv_parser {


class FlvHeader {
 public:
  FlvHeader();

  size_t ParseData(const std::string &data);

  std::string Type();

  std::string Info();

  YAML::Node Detail();

 private:
  uint8_t signature_[3];
  uint8_t version_;
  uint8_t reserved1_;
  uint8_t audio_flag_;
  uint8_t reserved2_;
  uint8_t video_flag_;
  uint32_t data_offset_;
};


}  // namespace flv_parser

