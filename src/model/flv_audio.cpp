// Copyright (c) 2018 winking324
//


#include "model/flv_audio.h"
#include "commons/read_bytes.h"


namespace flv_parser {


FlvAudio::FlvAudio() {
}

FlvAudio::~FlvAudio() {
}

size_t FlvAudio::ParseData(const std::string &data, size_t pos, size_t length) {
  size_t read_pos = pos;
  size_t audio_length = length;
  uint8_t sound_byte = ReadByte(&data[read_pos++]);
  --audio_length;

  format_ = (sound_byte & 0xF0) >> 4;
  rate_ = (sound_byte & 0x0C) >> 2;
  size_ = (sound_byte & 0x02) >> 1;
  type_ = (sound_byte & 0x01);

  if (format_ == AUDIO_FORMAT_AAC) {
    aac_packet_type_ = ReadByte(&data[read_pos++]);
    --audio_length;
  }

  FlvData::ParseData(data, read_pos, audio_length);
  return length;
}


}  // namespace flv_parser

