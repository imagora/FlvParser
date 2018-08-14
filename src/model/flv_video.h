// Copyright (c) 2018 winking324
//


#pragma once  // NOLINT(build/header_guard)


#include <inttypes.h>
#include "model/flv_data.h"


namespace flv_parser {


enum VideoFrameType {
  VIDEO_KEY_FRAME = 1,  // for AVC, a seekable frame
  VIDEO_INTER_FRAME = 2,  // for AVC, a non-seekable frame
  VIDEO_DISPOSABLE_INTER_FRAME = 3,  // H.263 only
  VIDEO_GENERATED_KEY_FRAME = 4,  // reserved for server use only
  VIDEO_INFO_AND_COMMAND_FRAME = 5,
};


enum VideoCodecId {
  VIDEO_CODEC_SORENSON_H263 = 2,
  VIDEO_CODEC_SCREEN = 3,
  VIDEO_CODEC_ON2_VP6 = 4,
  VIDEO_CODEC_ON2_VP6_WITH_ALPHA_CHANNEL = 5,
  VIDEO_CODEC_SCREEN_V2 = 6,
  VIDEO_CODEC_AVC = 7,
};


enum AVCPacketType {
  AVC_SEQUENCE_HEADER = 0,
  AVC_NALU = 1,
  AVC_END_OF_SEQUENCE = 2,
};


class FlvVideo : public FlvData {
 public:
  FlvVideo();

  virtual ~FlvVideo();

  virtual size_t ParseData(const std::string &data, size_t pos,
                           size_t length) override;

 private:
  uint8_t frame_type_;
  uint8_t codec_id_;
  uint8_t avc_packet_type_;
  uint32_t composition_time_;
};


}  // namespace flv_parser

