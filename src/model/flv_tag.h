// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include <memory>
#include "model/flv_data.h"


namespace flv_parser {


class FlvTag {
 public:
  FlvTag();

  int ParseData(const std::string &data);

 private:
  uint8_t reserved_;
  uint8_t filter_;
  uint8_t type_;
  uint32_t size_;
  uint32_t timestamp_;
  uint8_t timestamp_extended_;
  uint32_t stream_id_;
  std::unique_ptr<FlvData> data_;
};


}  // namespace flv_parser

