// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include "model/flv_data.h"


namespace flv_parser {


class FlvAudio : public FlvData {
 public:
  FlvAudio();

  virtual ~FlvAudio();

  virtual int ParseData(const std::string &data) override;

 private:
  uint8_t format_;
  uint8_t rate_;
  uint8_t size_;
  uint8_t type_;
  uint8_t aac_packet_type_;
};


}  // namespace flv_parser

