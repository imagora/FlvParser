// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include "model/flv_data.h"


namespace flv_parser {


class FlvVideo : public FlvData {
 public:
  FlvVideo();

  virtual ~FlvVideo();

  virtual int ParseData(const std::string &data) override;

 private:
  uint8_t frame_type_;
  uint8_t codec_id_;
  uint8_t avc_packet_type_;
  uint32_t composition_time_;
};


}  // namespace flv_parser

