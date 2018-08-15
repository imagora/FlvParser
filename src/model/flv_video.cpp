// Copyright (c) 2018 winking324
//


#include "model/flv_video.h"
#include "commons/read_bytes.h"


namespace flv_parser {


FlvVideo::FlvVideo() {
}

FlvVideo::~FlvVideo() {
}

size_t FlvVideo::ParseData(const std::string &data, size_t pos, size_t length) {
  size_t read_pos = pos;
  uint8_t video_byte = ReadByte(&data[read_pos++]);

  frame_type_ = (video_byte & 0xF0) >> 4;
  codec_id_ = (video_byte & 0x0F);

  if (codec_id_ == VIDEO_CODEC_AVC) {
    avc_packet_type_ = ReadByte(&data[read_pos++]);
    composition_time_ = Read3Bytes(&data[read_pos]);
    read_pos += 3;
  }

  FlvData::ParseData(data, read_pos, length - read_pos + pos);
  return length;
}


}  // namespace flv_parser

